#include "MQTTModule.h"

MQTTModule::MQTTModule():m_conn_opts(){
    m_client=nullptr;
    m_conn_opts=MQTTClient_connectOptions_initializer;
    m_pubmsg=MQTTClient_message_initializer;
    m_token=0;
    m_deliveredtoken=0;
    m_qos=QOS1;
    m_timeOut=10000;
    m_connectSucc=false;
}

void MQTTModule::init(const char* address,const char *topic,InstanceType type,const char *clientId, QOS qos,int timeOut){
    m_address=address;
    m_topic=topic;
    m_clientId=clientId;
    m_qos=qos;
    m_timeOut=timeOut;
    m_connectSucc=false;
    MQTTClient_create(&m_client, m_address.c_str(), m_clientId.c_str(),MQTTCLIENT_PERSISTENCE_NONE, NULL);
    m_conn_opts.keepAliveInterval = 20;
    m_conn_opts.cleansession = 1;
    MQTTClient_setCallbacks(m_client, this, connlost, msgarrvd, delivered);
    m_type=type;

}

void MQTTModule::Run()
{
        ThreadCoreBase::Sleep(3000);    // 这种更好用 
        if(!m_connectSucc && !m_address.empty()){
            if( MQTTClient_connect(m_client, &m_conn_opts) == MQTTCLIENT_SUCCESS)
            {
                printf("now start to connect:%s module type:%d success \n",m_address.c_str(),m_type);
                m_connectSucc=true;
                if(m_type == SUBSCRIPTION){
                    MQTTClient_subscribe(m_client, m_topic.c_str(), m_qos);
                    printf(" listen  success \n");
                }
            }else{
                printf("now start to connect:%s module type:%d failed \n",m_address.c_str(),m_type);
            }
        }
}


bool MQTTModule::sendData(const std::string & sendContent){
    if(m_type != PUBLICATION){
        return false;
    }
    if(m_connectSucc){
        m_pubmsg.payload = (void *)sendContent.c_str();
        m_pubmsg.payloadlen = sendContent.length();
        m_pubmsg.qos = m_qos;
        m_pubmsg.retained = 0;
        m_deliveredtoken = 0;
        int ret=MQTTClient_publishMessage(m_client, m_topic.c_str(), &m_pubmsg, &m_token);
        printf(" send ret:%d \n",ret);
        return true;	
    }else{
        printf(" send failed for connect failed \n");
    }
    return false;
}


void MQTTModule::delivered(void *context, MQTTClient_deliveryToken dt)
{
    printf("Message with token value %d delivery confirmed\n", dt);
    MQTTModule *ptr=static_cast<MQTTModule*>(context);
    ptr->m_deliveredtoken = dt;
}

bool MQTTModule::getMessage(std::vector<string> &outPutData)
{
    BaseCore::Threads::MutexGuard mutexGuard(m_mutex());
    
    if(!m_readDataQueue.empty()){
        while (!m_readDataQueue.empty())
        {
            outPutData.push_back(m_readDataQueue.front());
            m_readDataQueue.pop();
        }
        return true;
    }
    return false;
}
int MQTTModule::msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message)
{
    MQTTModule *ptr=static_cast<MQTTModule*>(context);
    BaseCore::Threads::MutexGuard mutexGuard(ptr->m_mutex());
    char*payloadptr = (char *)(message->payload);
    std::string data;
    for(int i=0; i<message->payloadlen; i++)
    {
        data.push_back(*payloadptr++);
    }
    ptr->m_readDataQueue.push(data);
    printf("Message arrived  topic: %s data:%s \n", topicName,data.c_str());
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return 1;
}
    void MQTTModule::connlost(void *context, char *cause)
{
    printf("\nConnection lost ");
    MQTTModule *ptr=static_cast<MQTTModule*>(context);
    ptr->m_connectSucc=false;
}




