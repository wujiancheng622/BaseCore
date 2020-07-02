#include <iostream>
#include <boost/make_shared.hpp>
#include "CommonSendCmdThread.h"
#include "ActivemqAPI.h"



boost::shared_ptr<CommonSendCmdThread> CommonSendCmdThread::m_stInstance;
boost::shared_ptr<BaseCore::Threads::Mutex> CommonSendCmdThread::m_spMutex=make_shared<BaseCore::Threads::Mutex >();


CommonSendCmdThread::CommonSendCmdThread()
{

}

CommonSendCmdThread::~CommonSendCmdThread()
{
	Stop();	
}

void CommonSendCmdThread::Run()
{
	ProcessCmd();
}

void CommonSendCmdThread::ProcessCmd()
{
	bool bHaveCmd=false;
	std::pair<ActivemqProducer *,std::string>  mqCmd;
	{
		BaseCore::Threads::MutexGuard mutexLock((*m_spMutex)());
		if(m_MQCmdDeque.size() > 0)
		{	
			bHaveCmd=true;
			mqCmd=m_MQCmdDeque.front();
			m_MQCmdDeque.pop_front();
		}
	}
	if (bHaveCmd)
	{
		_SendBytesMessage(mqCmd.first,mqCmd.second,0,1,100000);	
	}

}

void CommonSendCmdThread::PushMQCmd( MQCmd cmd )
{
	BaseCore::Threads::MutexGuard mutexLock((*m_spMutex)());
	if (Is_Started())
	{
		m_MQCmdDeque.push_back(cmd);
	}
}

CommonSendCmdThread * CommonSendCmdThread::Instance()
{
	BaseCore::Threads::MutexGuard mutexLock((*m_spMutex)());
	if (m_stInstance==NULL)
	{
		m_stInstance.reset(new CommonSendCmdThread);
		m_stInstance->Start();
	}
	return m_stInstance.get();
}

void CommonSendCmdThread::ClearAllCmd()
{
	BaseCore::Threads::MutexGuard mutexLock((*m_spMutex)());
	m_MQCmdDeque.clear();
}

