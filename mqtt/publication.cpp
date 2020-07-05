#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <unistd.h>
#include "MQTTClient.h"
#define ADDRESS     "tcp://192.168.17.143:1883"
#define CLIENTID    "ExampleClientPub"
#define TOPIC       "MQTT_Examples"
#define PAYLOAD     "Hello World! i am wjc this is new data"
#define QOS         2
#define TIMEOUT     10000L
volatile MQTTClient_deliveryToken deliveredtoken;

MQTTClient client;
MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
MQTTClient_message pubmsg = MQTTClient_message_initializer;
MQTTClient_deliveryToken token;
int rc=0;

void delivered(void *context, MQTTClient_deliveryToken dt)
{
    printf("Message with token value %d delivery confirmed\n", dt);
    deliveredtoken = dt;
}
int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message)
{
    int i;
    char* payloadptr;
    printf("Message arrived\n");
    printf("     topic: %s\n", topicName);
    printf("   message: ");
    payloadptr = (char *)(message->payload);
    for(i=0; i<message->payloadlen; i++)
    {
        putchar(*payloadptr++);
    }
    putchar('\n');
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return 1;
}
void connlost(void *context, char *cause)
{
    printf("\n lalalal   Connection ss context:%s lost\n",context);
    printf("     cause: %s\n", cause);
    while((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d start to try again\n", rc);
        sleep(3);
    }
    printf("reconnect success\n");

    pubmsg.payload = (void*)PAYLOAD;
    pubmsg.payloadlen = strlen(PAYLOAD);
    pubmsg.qos = QOS;
    pubmsg.retained = 0;
    deliveredtoken = 0;
    while(true){
        sleep(1000);
        MQTTClient_publishMessage(client, TOPIC, &pubmsg, &token);
        printf("in connlost Waiting for publication of %s\n topic %s for client with ClientID: %s\n",PAYLOAD, TOPIC, CLIENTID);
        while(deliveredtoken != token);
    }
}
int main(int argc, char* argv[])
{
    MQTTClient_create(&client, ADDRESS, CLIENTID,
        MQTTCLIENT_PERSISTENCE_NONE, NULL);
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    MQTTClient_setCallbacks(client, (void*)ADDRESS, connlost, msgarrvd, delivered);


    while((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d start to try again\n", rc);
        sleep(3);
    }
    printf("connect success\n");
    pubmsg.payload = (void*)PAYLOAD;
    pubmsg.payloadlen = strlen(PAYLOAD);
    pubmsg.qos = QOS;
    pubmsg.retained = 0;
    deliveredtoken = 0;
    while(true){
        sleep(1);
        MQTTClient_publishMessage(client, TOPIC, &pubmsg, &token);
        printf("in main Waiting for publication of %s\n topic %s for client with ClientID: %s\n",PAYLOAD, TOPIC, CLIENTID);
        while(deliveredtoken != token);
    }
    MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);
    return rc;
}
