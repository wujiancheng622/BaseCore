#include "MsgTarget.h"
#include <cstdio>
#include "CommandBase.h"


#if defined(WIN32)||defined(WIN64)||defined(WINCE)	
#else
#define NULL 0;
#endif


CMsgTarget::CMsgTarget(void)
{

}


CMsgTarget::~CMsgTarget(void)
{
	ClearAllCmd();
}


void CMsgTarget::Run()
{
	bool bSucceed = false;
	do 
	{
		CommandBase * pCommand = NULL;
		{
			BaseCore::Threads::MutexGuard mutexGuard(m_mtxCommand());
			if(m_deqCommand.empty())
			{
				bSucceed = false;
			}
			else
			{
				pCommand = m_deqCommand.front();
				m_deqCommand.pop_front();
				bSucceed = true;
			}
		}
		if (true == bSucceed)
		{
			OnReceiveCommand(pCommand);
		}
	} while (bSucceed);

}


int CMsgTarget::PushCommand(CommandBase *pCommand)
{
	BaseCore::Threads::MutexGuard mutexGuard(m_mtxCommand());
	if (0==pCommand->GetPriority())
	{
		m_deqCommand.push_back(pCommand);
	}else{
		m_deqCommand.push_front(pCommand);
	}
	return 0;
}

int CMsgTarget::GetCommandNums()
{
	BaseCore::Threads::MutexGuard mutexGuard(m_mtxCommand());
	return m_deqCommand.size();
}

void CMsgTarget::ClearAllCmd()
{
	BaseCore::Threads::MutexGuard mutexGuard(m_mtxCommand());
	std::deque< CommandBase * > ::iterator iter=m_deqCommand.begin();
	while(iter!=m_deqCommand.end())
	{
		CommandBase * pCmd=*iter;
		delete pCmd;
		++iter;
	}
	m_deqCommand.clear();
}
