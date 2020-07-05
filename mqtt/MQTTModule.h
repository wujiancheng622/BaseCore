#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <queue>
#include "MQTTClient.h"
#include "ThreadCoreBase.h"

//MQTT数据收发类，既可以收数据也可以发数据，不过每个实例要么当发送者，要么当接收者，不能同时当发送者又当接收者
class MQTTModule:public BaseCore::Threads::ThreadCoreBase{
public:
	MQTTModule();
	enum QOS{
		QOS0 =0,  //至多一次
		QOS1 =1, //至少一次
		QOS2 =2 //有且只有一次
	};
	enum InstanceType{
		PUBLICATION =0,
		SUBSCRIPTION =1
	};
	void init(const char* address,const char *topic,InstanceType type,const char *clientId, QOS qos=QOS1,int timeOut=10000);
    bool getMessage(std::vector<string> &outPutData);
    bool sendData(const std::string & sendContent);
    bool isConnected() { return m_connectSucc;}
private:
	void Run();
	static void delivered(void *context, MQTTClient_deliveryToken dt);
	static int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message);
	static void connlost(void *context, char *cause);
	std::string m_address;
	std::string m_topic;
	std::string m_clientId;
	QOS m_qos;
	MQTTClient m_client;
	MQTTClient_connectOptions m_conn_opts;
	MQTTClient_message m_pubmsg;
	MQTTClient_deliveryToken m_token;
	volatile MQTTClient_deliveryToken m_deliveredtoken;
	int m_timeOut;//
	volatile bool m_connectSucc;
	InstanceType m_type;
	std::queue<std::string > m_readDataQueue;
	BaseCore::Threads::Mutex m_mutex;
};
