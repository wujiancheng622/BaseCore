#include <cstdio>
#include "LeaderElectionCMD.h"
#include "CULeaderElectionBean.h"



BMSHeartTimeOutCMD::BMSHeartTimeOutCMD()
{

}

BMSHeartTimeOutCMD::~BMSHeartTimeOutCMD()
{

}

void BMSHeartTimeOutCMD::Execute( void )
{
	timespec time;
	clock_gettime(CLOCK_REALTIME, &time);

	
	long curTmp=time.tv_sec*1000+time.tv_nsec/1000000;
	long timeSub=curTmp-m_pInvoker->m_lastHeartTime;

	printf("\n  BMSHeartTimeOutCMD timeSub:%d  BMSHeartTimeOutMilSec:%d \n",timeSub,m_pInvoker->m_modelHeartTimeOutMilSec);

	if (m_pInvoker->m_curRole!=CULeaderElectionBean::LEADER&&timeSub>m_pInvoker->m_modelHeartTimeOutMilSec/*200*/)//说明当前BMS与Leader连接超时
	{
		if (m_pInvoker->m_bConnectWithLeader/*m_bInElectionLeader*/)
		{
			m_pInvoker->m_bConnectWithLeader=false;

			printf("\n leader heart time out\n");
			m_pInvoker->UpdateCurTerm();
		}
	}
	

}


RequestVoteFromOtherBMSCMD::RequestVoteFromOtherBMSCMD()
{

}

RequestVoteFromOtherBMSCMD::~RequestVoteFromOtherBMSCMD()
{

}

void RequestVoteFromOtherBMSCMD::Execute( void )
{
	//printf("\n  RequestVoteFromOtherBMSCMD::Execute \n");
	m_pInvoker->RequestVoteFromOtherBMS();
	//BaseCore::Threads::ThreadCoreBase::Sleep(m_pInvoker->GetMilliSec(100,1)/4);	
}

CountCurTermWinVoteCMD::CountCurTermWinVoteCMD()
{

}

CountCurTermWinVoteCMD::~CountCurTermWinVoteCMD()
{

}

void CountCurTermWinVoteCMD::Execute( void )
{
	//printf("\n  CountCurTermWinVoteCMD::Execute \n");
	int ret=m_pInvoker->CountCurTermWinVote();

	if (ret!=0)//没有成为Leader,结束当前周期开启下一轮周期
	{
		//printf("\n  COUNT_CURTERM_WIN_VOTE \n");
		m_pInvoker->UpdateCurTerm();
	}
	//BaseCore::Threads::ThreadCoreBase::Sleep(m_pInvoker->GetMilliSec(100,1)/4);	
}
