#ifndef MQCLIENTDEFINE_H_
#define MQCLIENTDEFINE_H_


#include <queue>
#include <utility>
#include <string>
#include <map>
#include <vector>


class ActivemqProducer;
class ActivemqConsumer;

typedef std::pair<ActivemqProducer *,std::string>  MQCmd;

typedef std::pair<std::pair<int,int>,std::string > MQMessage;  // <<type,srcmodel>,content>  注意这里srcmodel不一定标识数据的发送方，
//srcmodel是要是用来区分由哪个模块(比如CUDISBean，CULeaderBean，CUBServerBean等)来处理这个消息的。




class MQUrl
{
public:
	std::string m_brokeUrl;
	std::string m_destUrl;
	int m_bUseTopic;
	int m_bClientAck;
	MQUrl();
	MQUrl(std::string dest,std::string broke,bool bUseTopic=false,bool bClientAck=false);	
	bool operator == (const MQUrl &other) const;
};


typedef std::pair<MQUrl,ActivemqProducer *> MQProducer;
typedef std::pair<MQUrl,ActivemqConsumer *> MQConsumer;

typedef std::vector<MQProducer> MQProducerVec;
typedef std::vector<MQConsumer> MQConsumerVec;



typedef	std::deque<MQCmd>		MQCmdDeque;

typedef std::deque<MQMessage>   MQMesDeque;


#endif //MQCLIENTDEFINE_H_

