#include "CUMQClient.h"
#include "CommonSendCmdThread.h"
#include "ActivemqAPI.h"




CUMQClient::~CUMQClient()
{
	DelAllProducer();
	DelAllConsumer();
}

CUMQClient::CUMQClient(int cuType,CMsgTarget *pDispatcher)
{
	m_pDispatcher=pDispatcher;
	m_iCuType=cuType;
	m_bStarted=false;

}


int CUMQClient::SendMessage(std::string message,std::string destUrl,std::string brokeUrl)
{
	if (m_bStarted)
	{
		MQProducerVec::iterator it=m_producerVec.begin();
		MQProducerVec::iterator end=m_producerVec.end();
		while(it!=end)
		{
			const MQUrl &urlTmp=it->first;
			//printf("urlTmp.destUrl:%s  urlTmp.brokeUrl:%s \n",urlTmp.m_destUrl.c_str(),urlTmp.m_brokeUrl.c_str());
			if (urlTmp.m_destUrl==destUrl&&urlTmp.m_brokeUrl==brokeUrl)
			{
				//printf("push success  urlTmp.m_destUrl:%s \n",urlTmp.m_destUrl.c_str());
				CommonSendCmdThread::Instance()->PushMQCmd(MQCmd(it->second,message));
				return 0;
			}
			++it;
		}
		return -1;
	}


}



int CUMQClient::AddProducer( const MQUrl &producerUrl)
{

	printf("CUMQClient::AddProducer :%s  %s\n",producerUrl.m_brokeUrl.c_str(),producerUrl.m_destUrl.c_str());

	MQProducerVec::iterator it=m_producerVec.begin();
	MQProducerVec::iterator end=m_producerVec.end();
	while(it!=end)
	{
		const MQUrl &urlTmp=it->first;
		if (urlTmp==producerUrl)//已经存在
		{
			return -1;
		}
		++it;
	}
	
	m_producerVec.push_back(std::pair<MQUrl,ActivemqProducer*>(producerUrl,NULL));

	printf("\n CUMQClient::AddProducer push succeed   m_producerVec size:%d  \n",m_producerVec.size());

	return 0;

}

int CUMQClient::DelProducer( const MQUrl &producerUrl )
{

	printf("\n CUMQClient::DelProducer \n");

	MQProducerVec::iterator it=m_producerVec.begin();
	MQProducerVec::iterator end=m_producerVec.end();
	while(it!=end)
	{
		const MQUrl &urlTmp=it->first;
		if (urlTmp==producerUrl)//已经存在
		{
			if (it->second)
			{
				_CloseActivemqProducer(it->second);
			}
			m_producerVec.erase(it);
			return 0;
		}
		++it;
	}

	return -1;

}

int CUMQClient::AddConsumer( const MQUrl &consumerUrl)
{

	MQConsumerVec::iterator it=m_consumerVec.begin();
	MQConsumerVec::iterator end=m_consumerVec.end();
	while(it!=end)
	{
		const MQUrl &urlTmp=it->first;
		if (urlTmp==consumerUrl)//已经存在
		{
			return -1;
		}
		++it;
	}
	m_consumerVec.push_back(std::pair<MQUrl,ActivemqConsumer*>(consumerUrl,NULL));

	return 0;

}

int CUMQClient::DelConsumer( const MQUrl &consumerUrl )
{
	MQConsumerVec::iterator it=m_consumerVec.begin();
	MQConsumerVec::iterator end=m_consumerVec.end();
	while(it!=end)
	{
		const MQUrl &urlTmp=it->first;
		if (urlTmp==consumerUrl)//已经存在
		{
			if (it->second)
			{
				_CloseActivemqConsumer(it->second);
			}
			m_consumerVec.erase(it);
			return 0;
		}
		++it;
	}

	return -1;
}

void CUMQClient::DelAllProducer()
{
	printf("\n CUMQClient::DelAllProducer \n");

	MQProducerVec::iterator it=m_producerVec.begin();
	MQProducerVec::iterator end=m_producerVec.end();
	while(it!=end)
	{
		if (it->second)
		{
			_CloseActivemqProducer(it->second);
		}
	}
	m_producerVec.clear();
}

void CUMQClient::DelAllConsumer()
{
	MQConsumerVec::iterator it=m_consumerVec.begin();
	MQConsumerVec::iterator end=m_consumerVec.end();
	while(it!=end)
	{
		if (it->second)
		{
			_CloseActivemqConsumer(it->second);
		}
	}
	m_consumerVec.clear();
}

int CUMQClient::StartService( void )
{
	//printf("CUMQClient::StartService m_producerVec size:%d  m_consumerVec:%d \n",m_producerVec.size(),m_consumerVec.size());
	if (!m_bStarted)
	{
		Start();
		EnableAllProducer();
		EnableAllConsumer();
		m_bStarted=true;
	}

}

void CUMQClient::StopService( void )
{
	if (m_bStarted)
	{
		printf("CUMQClient::StopService start\n");
		CommonSendCmdThread::Instance()->Stop();
		CommonSendCmdThread::Instance()->ClearAllCmd();
		Stop();
		DisableAllProducer();
		DisableAllConsumer();
		m_bStarted=false;
		printf("CUMQClient::StopService success\n");
	}

}

ActivemqProducer * CUMQClient::EnableProducer( const MQUrl &producerUrl )
{
	MQProducerVec::iterator it=m_producerVec.begin();
	MQProducerVec::iterator end=m_producerVec.end();
	while(it!=end)
	{
		const MQUrl &urlTmp=it->first;
		if (urlTmp==producerUrl)//存在
		{
			if (!(it->second))
			{
				printf("CUMQClient::EnableProducer urlTmp.m_brokeUrl:%s  urlTmp.m_destUrl:%s  \n",urlTmp.m_brokeUrl.c_str(),urlTmp.m_destUrl.c_str());
				it->second=_CreateActivemqProducer(urlTmp.m_brokeUrl,urlTmp.m_destUrl,urlTmp.m_bUseTopic,urlTmp.m_bClientAck);//192.168.3.136
				return it->second;
			}
			return 0;
		}
		++it;
	}
	return NULL;
}

ActivemqConsumer * CUMQClient::EnableConsumer( const MQUrl &consumerUrl )
{
	MQConsumerVec::iterator it=m_consumerVec.begin();
	MQConsumerVec::iterator end=m_consumerVec.end();
	while(it!=end)
	{
		const MQUrl &urlTmp=it->first;
		if (urlTmp==consumerUrl)//存在
		{
			if (!(it->second))
			{
				printf("CUMQClient::EnableConsumer urlTmp.m_brokeUrl:%s  urlTmp.m_destUrl:%s  \n",urlTmp.m_brokeUrl.c_str(),urlTmp.m_destUrl.c_str());
				it->second=_CreateActivemqConsumer(urlTmp.m_brokeUrl,urlTmp.m_destUrl,urlTmp.m_bUseTopic,urlTmp.m_bClientAck);
			}
			return it->second;
		}
		++it;
	}
	return NULL;
}

int CUMQClient::DisableProducer( const MQUrl &producerUrl )
{
	MQProducerVec::iterator it=m_producerVec.begin();
	MQProducerVec::iterator end=m_producerVec.end();
	while(it!=end)
	{
		const MQUrl &urlTmp=it->first;
		if (urlTmp==producerUrl)//存在
		{
			if (it->second)
			{
				_CloseActivemqProducer(it->second);
				it->second=NULL;
			}
			return 0;
		}
		++it;
	}
	return -1;
}

int CUMQClient::DisableConsumer( const MQUrl &consumerUrl )
{
	MQConsumerVec::iterator it=m_consumerVec.begin();
	MQConsumerVec::iterator end=m_consumerVec.end();
	while(it!=end)
	{
		const MQUrl &urlTmp=it->first;
		if (urlTmp==consumerUrl)//存在
		{
			if (it->second)
			{
				_CloseActivemqConsumer(it->second);
				it->second=NULL;
			}
			return 0;
		}
		++it;
	}
	return -1;
}

int CUMQClient::EnableAllProducer()
{
	MQProducerVec::iterator itProducer=m_producerVec.begin();
	MQProducerVec::iterator endProducer=m_producerVec.end();
	while(itProducer!=endProducer)
	{
		const MQUrl &urlTmp=itProducer->first;
		if (!(itProducer->second))
		{
			printf("CUMQClient::EnableAllProducer urlTmp.m_brokeUrl:%s  urlTmp.m_destUrl:%s  \n",urlTmp.m_brokeUrl.c_str(),urlTmp.m_destUrl.c_str());
			itProducer->second=_CreateActivemqProducer(urlTmp.m_brokeUrl,urlTmp.m_destUrl,urlTmp.m_bUseTopic,urlTmp.m_bClientAck);//192.168.3.136
		}
		++itProducer;
	}
}

int CUMQClient::EnableAllConsumer()
{
	MQConsumerVec::iterator itConsumer=m_consumerVec.begin();
	MQConsumerVec::iterator endConsumer=m_consumerVec.end();
	while(itConsumer!=endConsumer)
	{
		const MQUrl &urlTmp=itConsumer->first;
		if (!(itConsumer->second))
		{
			printf("CUMQClient::EnableAllConsumer urlTmp.m_brokeUrl:%s  urlTmp.m_destUrl:%s  \n",urlTmp.m_brokeUrl.c_str(),urlTmp.m_destUrl.c_str());
			itConsumer->second=_CreateActivemqConsumer(urlTmp.m_brokeUrl,urlTmp.m_destUrl,urlTmp.m_bUseTopic,urlTmp.m_bClientAck);//192.168.3.136
		}
		++itConsumer;
	}

}

int CUMQClient::DisableAllProducer()
{
	MQProducerVec::iterator itProducer=m_producerVec.begin();
	MQProducerVec::iterator endProducer=m_producerVec.end();
	while(itProducer!=endProducer)
	{
		if (itProducer->second)
		{
			_CloseActivemqProducer(itProducer->second);
		}
		++itProducer;
	}

}

int CUMQClient::DisableAllConsumer()
{
	MQConsumerVec::iterator itConsumer=m_consumerVec.begin();
	MQConsumerVec::iterator endConsumer=m_consumerVec.end();
	while(itConsumer!=endConsumer)
	{
		if (itConsumer->second)
		{
			_CloseActivemqConsumer(itConsumer->second);
		}
		++itConsumer;
	}
}

void CUMQClient::SetMSGDispatcher( CMsgTarget *pDispatcher )
{
	m_pDispatcher=pDispatcher;
}

//ActivemqProducer * CUMQClient::CreateProducer( std::string dest,std::string broke,bool bUseTopic,bool bClientAck)
//{
//	printf("CUMQClient::CreateProducer  dest:%s  broke:%s  bUseTopic:%d   bClientAck:%d\n",dest.c_str(),broke.c_str(),bUseTopic,bClientAck);
//	return _CreateActivemqProducer(broke,dest,bUseTopic,bClientAck);
//}

//ActivemqConsumer * CUMQClient::CreateConsumer( std::string dest,std::string broke,bool bUseTopic,bool bClientAck)
//{
//	return _CreateActivemqConsumer(broke,dest,bUseTopic,bClientAck);
//}

//void CUMQClient::DestroyProducer( ActivemqProducer *pProducer )
//{
//	_CloseActivemqProducer(pProducer);
//}
//
//void CUMQClient::DestroyConsumer( ActivemqConsumer *pConsumer )
//{
//	_CloseActivemqConsumer(pConsumer);
//}

