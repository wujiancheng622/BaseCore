#include <iostream>
#include <stdio.h>
#include <map>
#include <vector>
#include <sstream> 
#include <time.h>
#include <boost/random.hpp>
#include "CULeaderElectionBean.h"
#include "ThreadCoreBase.h"
#include "DataType.pb.h"
#include "ModuleType.pb.h"
#include "LeaderBroadcastBean.pb.h"
#include "BMSHeartBean.pb.h"
#include "ResponseRpcBean.pb.h"
#include "RequestVoteRpcBean.pb.h"
#include "ParamMessageBean.pb.h"
#include "LeaderCommand.h"
#include "LeaderInfoNoticeCMD.h"
#include "ParamListBean.pb.h"
#include "LeaderElectionCMD.h"



using namespace com::arges::file::proto;


extern std::string GetParamMessage(int model,int type,int srcModel,std::string content,std::string brokerUrl="",std::string destUrl="",int code=1,std::string doman="1",std::string sessionId="1");


//��ȡһ���������������������Χ��beginMillisec��endMilisec֮�� 
int CULeaderElectionBean::GetMilliSec(int interval,int multiValue)
{
	using namespace boost;
	long seed=0;
	struct timespec time1 = {0, 0};   
	clock_gettime(CLOCK_MONOTONIC, &time1);        
	int mod=((time1.tv_nsec%30)+1)*10;
	seed=(m_randomValue*mod)/1000;
	mt19937 rng(seed);

	random::uniform_int_distribution<> ui(20,256);
	long randomValue=ui(rng);
	int value=randomValue;
	return seed+125;
}


CULeaderElectionBean::CULeaderElectionBean():CUMQClient(/*BMSLEADER*/4,NULL)
	,m_bmsHeartTimer(this)
	,m_leaderBroadcast(this)
{
	m_spCountCurWinVoteTimer.reset(new BaseCore::Clock::Timer(this));
	m_spCandidateTimer.reset(new BaseCore::Clock::Timer(this));
	m_spCountCurWinVoteTimer->SetHandle(1);
	m_bmsHeartTimer.SetHandle(2);
	m_leaderBroadcast.SetHandle(3);
	m_spCandidateTimer->SetHandle(4);

	m_curTerm=0;
	m_curRole=FOLLOWER;
	m_bFinfishCurTremVote=false;
	m_nCurTremWinVote=0;
	m_pMutex=new BaseCore::Threads::Mutex;

	m_bConnectWithLeader=false;

	m_leaderBroadcast.Start(100);
	int heartTime=GetMilliSec()*4;
	printf("\n  heartTime:%d  GetBMSHeartTimeOutMilSec:%d  \n",heartTime,m_modelHeartTimeOutMilSec);
	m_bmsHeartTimer.Start(200);
	
}

CULeaderElectionBean::~CULeaderElectionBean()
{
	if (m_pMutex)
	{
		delete m_pMutex;
		m_pMutex=NULL;
	}

	DestroyLeaderOutMsgConsumer();
}

void CULeaderElectionBean::OnMessage(int type, std::string message )
{
	BaseCore::Threads::MutexGuard mutexLock((*m_pMutex)());
	switch (type)
	{
	case  REQ_LEADER_TO_FOLLOWER_BROADCAST:
		DealWithLeaderBroadCast(message);
		break;
	case  REQ_REQUESTVOTE_RPC:
		VoteToOther(message);
		break;
	case  REQ_RESPONEVOTE_RPC://����BMS���͹�����ѡƱ
		GetOtherBMSVote(message);
		break;
	case REQ_BMS_TO_LEADER_HEART:
		DealWithBMSHeart(message);
		break;
	default:
		break;	
	}
	return ;
}

int CULeaderElectionBean::StartService( void )
{
	
	MQUrl urlTmp;
	urlTmp.m_brokeUrl=m_mqBrokeUrl;
	urlTmp.m_bUseTopic=true;
	urlTmp.m_destUrl=TOPIC_Colony;//BMS��Ⱥʹ�õĹ㲥��·
	AddProducer(urlTmp);
	AddConsumer(urlTmp);
	urlTmp.m_bUseTopic=false;
	urlTmp.m_destUrl=QUEUE_Leader;//��leader������Ϣ��������
	AddProducer(urlTmp);
	CUMQClient::StartService();

	CreateLeaderOutMsgConsumer();


	printf("CULeaderElectionBean::StartService\n");

	//�ȴ�GetMilliSec()����ж��Ƿ��Ѿ���LEADER����,���û�������ѡ�ٲ���
	BaseCore::Threads::ThreadCoreBase::Sleep(GetMilliSec()*4);
	{
		timespec time;
		clock_gettime(CLOCK_REALTIME, &time);
		m_lastHeartTime=time.tv_sec*1000+time.tv_nsec/1000000;
		BaseCore::Threads::MutexGuard mutexLock((*m_pMutex)());
		printf("CULeaderElectionBean::StartService  m_bConnectWithLeader:%d \n",m_bConnectWithLeader);
		if (!m_bConnectWithLeader)//û����LEADER�������ӣ�����ѡ�ٲ���
		{
			printf("CULeaderElectionBean::StartService  UpdateCurTerm\n");
			UpdateCurTerm();
		}
	}

}

void CULeaderElectionBean::StopService( void )
{
	
}

void CULeaderElectionBean::OnTimeOut(int hHandle)
{
	BaseCore::Threads::MutexGuard mutexLock((*m_pMutex)());
	if (hHandle==m_bmsHeartTimer.GetHandle())
	{
		BMSHeartTimeOutCMD *pCommand=new BMSHeartTimeOutCMD;
		PushCommand(pCommand);
	}else if (hHandle==m_leaderBroadcast.GetHandle())
	{
		LeaderBroadcast();
	}else if (hHandle==m_spCandidateTimer->GetHandle())
	{
		printf("CULeaderElectionBean::OnTimeOut m_spCandidateTimer  m_bFinfishCurTremVote::%d m_nCurTremWinVote:%d   cmd size:%d  \n",m_bFinfishCurTremVote,m_nCurTremWinVote,GetCommandNums());
		RequestVoteFromOtherBMSCMD *pCommand=new RequestVoteFromOtherBMSCMD;
		PushCommand(pCommand);
	}else if (hHandle==m_spCountCurWinVoteTimer->GetHandle())
	{
		printf("\CULeaderElectionBean::OnTimeOut m_spCountCurWinVoteTimer cmd size:%d  \n",GetCommandNums());
		CountCurTermWinVoteCMD *pCommand=new CountCurTermWinVoteCMD;
		PushCommand(pCommand);
	}
}

void CULeaderElectionBean::TransformToLeader()
{
	//ת���LEADER��ʼ������BMS����Leader��������
	printf("CULeaderElectionBean::TransformToLeader\n");
	m_curRole=LEADER;
	m_bConnectWithLeader=true;
	EnableLeaderOutMsgConsumer();

	OnTransformToLeader();
}

void CULeaderElectionBean::VoteToOther(std::string message)
{

	RequestVoteRpc reqVoteRpc;
	reqVoteRpc.ParseFromString(message);

	if(0==CheckTerm(atoi(reqVoteRpc.term().c_str())))
	{
		if(m_bFinfishCurTremVote||(!reqVoteRpc.srcidentifier().compare(m_strBMSUUID)))//��ǰƱ��û��Ͷ��ȥ������ѡƱ�Ĳ�������
		{
			return;
		}
		m_bFinfishCurTremVote=true;

		ResponseVoteRpc respVoteRpc;
		respVoteRpc.set_srcidentifier(m_strBMSUUID);
		respVoteRpc.set_desidentifier(reqVoteRpc.srcidentifier());
		std::ostringstream ostreamTerm;
		ostreamTerm<< m_curTerm;
		respVoteRpc.set_term(ostreamTerm.str());
		std::string content;
		respVoteRpc.SerializeToString(&content);
		std::string strMessage=GetParamMessage(C_BMS_SERVER,REQ_RESPONEVOTE_RPC,C_BMS_SERVER,content);

		SendMessage(strMessage,std::string(TOPIC_Colony),m_mqBrokeUrl);

	}

}

void CULeaderElectionBean::GetOtherBMSVote( std::string message )
{
	ResponseVoteRpc respVoteRpc;
	respVoteRpc.ParseFromString(message);

	if (0==CheckTerm(atoi(respVoteRpc.term().c_str())))
	{
		if (m_curRole==LEADER)
		{
			return;
		}

		if (m_bConnectWithLeader)//Leader�Ѿ���ѡ�ٳ�����
		{
			return;
		}

		int ret=respVoteRpc.desidentifier().compare(m_strBMSUUID);

		if (0==ret)
		{
			++m_nCurTremWinVote;
			printf("GetOtherBMSVote  get :%s vote  term:%s   m_nCurTremWinVote:%d \n",respVoteRpc.srcidentifier().c_str(),respVoteRpc.term().c_str(),m_nCurTremWinVote);
			/*
				�жϵ�ǰ��õ�ͶƱ�Ƿ��Ѿ���������
			*/
			if (m_nCurTremWinVote>=(m_modelNumbers/2+1))//���ͶƱ�����룬���л���LEADER����ֹ��ǰͶƱ
			{
				if (m_curRole!=LEADER)//��ǰ�Ѿ���ó���������ͶƱ������ת���ɫΪLeader
				{
					TransformToLeader();
				}
			}
		}
		
	}

}

void CULeaderElectionBean::DealWithLeaderBroadCast( std::string message)
{
	com::arges::file::proto::LeaderBroadcast leaderBroadcast;
	leaderBroadcast.ParseFromString(message);

	if (0==CheckTerm(atoi(leaderBroadcast.term().c_str())))
	{
		if (m_curRole!=LEADER)
		{
			//�������һ���յ�Leader����Ϣ
			timespec time;
			clock_gettime(CLOCK_REALTIME, &time);
			m_lastHeartTime=time.tv_sec*1000+time.tv_nsec/1000000;
			m_curRole=FOLLOWER;
			DisableLeaderOutMsgConsumer();
			m_bConnectWithLeader=true;
			printf("leader(identifier:%s term:%s)  cur BMS(identifier:%s term:%d  m_curRole:%d) \n",leaderBroadcast.identifier().c_str(),leaderBroadcast.term().c_str(),m_strBMSUUID.c_str(),m_curTerm,m_curRole);
		}
		OnDealWithLeaderBroadCast();
	}
}

void CULeaderElectionBean::UpdateCurTerm(int AddTermValue)
{
	m_curRole=FOLLOWER;
	m_curTerm+=AddTermValue;

	DisableLeaderOutMsgConsumer();

	OnUpdateCurTerm();

	m_nCurTremWinVote=0;
	m_bFinfishCurTremVote=false;
	m_bConnectWithLeader=false;
	m_spCandidateTimer->Start(GetMilliSec(),1);

}

void CULeaderElectionBean::RequestVoteFromOtherBMS()
{

	if (!m_bFinfishCurTremVote)//��ǰ���ڵ�Ʊ��û��Ͷ��ȥ����Ͷ���Լ�
	{
		m_bFinfishCurTremVote=true;
		m_nCurTremWinVote++;
	}

	/*
	������BMS����RequestVote RPC����
	*/
	if (m_bConnectWithLeader)//����Ѿ���Leader��ѡ�ٳ����˾�û��Ҫ���½���ѡ��
	{
		return;
	}

	m_curRole=CANDIDATE;
	DisableLeaderOutMsgConsumer();
	std::string content;
	RequestVoteRpc reqVoteRpc;
	std::ostringstream ostreamTerm;
	ostreamTerm<< m_curTerm;
	reqVoteRpc.set_term(ostreamTerm.str());
	reqVoteRpc.set_srcidentifier(m_strBMSUUID);
	reqVoteRpc.SerializeToString(&content);
	std::string strMessage=GetParamMessage(C_BMS_SERVER,REQ_REQUESTVOTE_RPC,C_BMS_SERVER,content);
	SendMessage(strMessage,std::string(TOPIC_Colony),m_mqBrokeUrl);

	m_spCountCurWinVoteTimer->Start(GetMilliSec(),1);
}

int CULeaderElectionBean::CountCurTermWinVote()
{

	if (m_bConnectWithLeader)
	{
		printf(" m_bConnectWithLeader:%d \n",m_bConnectWithLeader);
		return 0;
	}

	/*
	�鿴Ŀǰ��õ�ѡƱ�Ƿ��Ѿ�������������������������˳�ѡ�ٹ���������ǰ״̬�л���LEADER��
	������������ѡ����������������һ¥��ѡ��
	*/
	printf("CountCurTermWinVote m_nCurTremWinVote:%d  total BMS num:%d  m_curRole:%d\n",m_nCurTremWinVote,m_modelNumbers,m_curRole);

	if (m_nCurTremWinVote>=(m_modelNumbers/2+1))//���ͶƱ�����룬���л���LEADER����ֹ��ǰͶƱ
	{
		if (m_curRole!=LEADER)
		{
			TransformToLeader();
		}
	}else{//�����ָ����ʱ����û�л�ó���һ���Ʊ�������ͶƱ��������������һ��ͶƱ
		return -1;
	}
	return 0;
}

void CULeaderElectionBean::LeaderBroadcast()
{
	if (LEADER!=m_curRole)
	{
		return;
	}

	printf("LeaderBroadcast identifier:%s   cur trem:%d  \n",m_strBMSUUID.c_str(),m_curTerm);

	std::string content;
	com::arges::file::proto::LeaderBroadcast leaderBroadcast;
	std::ostringstream ostreamTerm;
	ostreamTerm<<m_curTerm;
	leaderBroadcast.set_term(ostreamTerm.str());
	leaderBroadcast.set_identifier(m_strBMSUUID);
	leaderBroadcast.SerializeToString(&content);
	std::string strMessage=GetParamMessage(C_BMS_SERVER,REQ_LEADER_TO_FOLLOWER_BROADCAST,C_BMS_SERVER,content);
	SendMessage(strMessage,std::string(TOPIC_Colony),m_mqBrokeUrl);

	OnLeaderBroadcast();

	LeaderInfoNoticeCMD *pCommand=new LeaderInfoNoticeCMD;
	pCommand->SetID(m_strBMSUUID);
	pCommand->SetPort(m_leaderListenPort);
	pCommand->SetIP(m_ip);
	PushCommand(pCommand);

}

int CULeaderElectionBean::CheckTerm( int term )
{
	if (term<m_curTerm)
	{
		return -1;
	}else if (term>m_curTerm)
	{
		UpdateCurTerm(term-m_curTerm);
		return -1;
	}
	return 0;
}

void CULeaderElectionBean::CreateLeaderOutMsgConsumer()
{
	AddConsumer(MQUrl(QUEUE_Leader,m_mqBrokeUrl,false));
}

void CULeaderElectionBean::EnableLeaderOutMsgConsumer()
{
	EnableConsumer(MQUrl(QUEUE_Leader,m_mqBrokeUrl));
	printf("CULeaderElectionBean::EnableLeaderOutMsgConsumer\n");
}

void CULeaderElectionBean::DisableLeaderOutMsgConsumer()
{
	DisableConsumer(MQUrl(QUEUE_Leader,m_mqBrokeUrl));
}

void CULeaderElectionBean::DestroyLeaderOutMsgConsumer()
{
	DelConsumer(MQUrl(QUEUE_Leader,m_mqBrokeUrl));
}

void CULeaderElectionBean::DealWithBMSHeart( std::string message )
{
	BMSHeart bmsHeart;
	bmsHeart.ParseFromString(message);

	if (0==CheckTerm(atoi(bmsHeart.term().c_str())))
	{
		if (m_curRole!=LEADER)
		{
			return ;
		}
		OnDealWithBMSHeart(bmsHeart);
	}
}


bool CULeaderElectionBean::ConnectedWithLeader()
{
	return m_bConnectWithLeader;
}



int CULeaderElectionBean::OnReceiveCommand( CommandBase *pMsg )
{
	if (LeaderCommand::IsCommandValid(pMsg))
	{
		pMsg->Execute(this);
	}
	if (pMsg)
	{
		delete pMsg;
		pMsg=NULL;
	}
	return 0;
}

void CULeaderElectionBean::SetUUID( std::string uuid )
{
	m_strBMSUUID=uuid;
}

void CULeaderElectionBean::SetRandomValue( int randomValue )
{
	m_randomValue=randomValue;
}

void CULeaderElectionBean::SetMqBrokeUrl( std::string mqBrokeUrl )
{
	m_mqBrokeUrl=mqBrokeUrl;
}

void CULeaderElectionBean::SetIP( std::string ip )
{
	m_ip=ip;
}

void CULeaderElectionBean::SetLeaderListenPort( int leaderListenPort )
{
	m_leaderListenPort=leaderListenPort;
}

void CULeaderElectionBean::SetModelNumbers( int modelNumbers )
{
	m_modelNumbers=modelNumbers;
}

void CULeaderElectionBean::SetModelHeartTimeOutMilSec( int modelHeartTimeOutMilSec )
{
	m_modelHeartTimeOutMilSec=modelHeartTimeOutMilSec;
}

void CULeaderElectionBean::OnTransformToLeader()
{

}

void CULeaderElectionBean::OnDealWithLeaderBroadCast()
{

}

void CULeaderElectionBean::OnUpdateCurTerm()
{

}

void CULeaderElectionBean::OnLeaderBroadcast()
{

}

void CULeaderElectionBean::OnDealWithBMSHeart(BMSHeart &bmsHeart)
{

}

void CULeaderElectionBean::SetQUEUE_Leader( std::string queue_leader )
{
	QUEUE_Leader=queue_leader;
}

void CULeaderElectionBean::SetTOPIC_Colony( std::string topic_colony )
{
	TOPIC_Colony=topic_colony;
}


