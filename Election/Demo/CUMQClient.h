#ifndef CUMQCLIENT_H_
#define CUMQCLIENT_H_


#include "MQClientDefine.h"
#include "MsgTarget.h"




class CUMQClient:public CMsgTarget
{
public:
	CUMQClient(int cuType,CMsgTarget *pDispatcher);
	virtual ~CUMQClient();

	void SetMSGDispatcher(CMsgTarget *pDispatcher);

	int AddProducer(const MQUrl &producerUrl); 
	int AddConsumer(const MQUrl &consumerUrl); 

	int DelProducer(const MQUrl &producerUrl);
	int DelConsumer(const MQUrl &consumerUrl);
	void DelAllProducer();
	void DelAllConsumer();

	ActivemqProducer * EnableProducer(const MQUrl &producerUrl); 
	ActivemqConsumer * EnableConsumer(const MQUrl &consumerUrl); 
	int DisableProducer(const MQUrl &producerUrl); 
	int DisableConsumer(const MQUrl &consumerUrl); 
	int EnableAllProducer();
	int EnableAllConsumer();
	int DisableAllProducer();
	int DisableAllConsumer();
	                                                                                           

	virtual int StartService(void);
	virtual void StopService(void);

	int SendMessage(std::string message,std::string destUrl,std::string brokeUrl);


	virtual void OnMessage(int type,std::string message)=0;

protected:
	CMsgTarget *m_pDispatcher;

private:

	int		m_iCuType;				// 客户类型
	MQProducerVec m_producerVec;
	MQConsumerVec m_consumerVec;
	bool m_bStarted;//是否已经启动服务

};



#endif //CUMQCLIENT_H_