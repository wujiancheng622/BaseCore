#include <cstdio>
#include "LeaderElectionCMD.h"
#include <boost/shared_ptr.hpp>
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

	if (m_pInvoker->m_curRole!=CULeaderElectionBean::LEADER&&timeSub>m_pInvoker->m_modelHeartTimeOutMilSec/*200*/)//˵����ǰBMS��Leader���ӳ�ʱ
	{
		if (m_pInvoker->m_bConnectWithLeader/*m_bInElectionLeader*/)
		{
			printf("\n  BMSHeartTimeOutCMD timeSub:%ld  BMSHeartTimeOutMilSec:%d \n",timeSub,m_pInvoker->m_modelHeartTimeOutMilSec);

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
	m_pInvoker->RequestVoteFromOtherBMS();
}

CountCurTermWinVoteCMD::CountCurTermWinVoteCMD()
{

}

CountCurTermWinVoteCMD::~CountCurTermWinVoteCMD()
{

}

void CountCurTermWinVoteCMD::Execute( void )
{
	
	int ret=m_pInvoker->CountCurTermWinVote();

	if (ret!=0)//û�г�ΪLeader,������ǰ���ڿ�����һ������
	{
		m_pInvoker->UpdateCurTerm();
	}
}
