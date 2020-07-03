#ifndef CUBMSLEADERELECTIONBEAN_H_
#define CUBMSLEADERELECTIONBEAN_H_


#include <time.h>
#include <map>
#include <vector>
#include <unistd.h>
#include <boost/shared_ptr.hpp>
#include "CUMQClient.h"
#include "Timer.h"




namespace com
{
	namespace arges
	{
		namespace file
		{
			namespace proto
			{
				class BMSHeart;
			}
		}
	}
}



class CULeaderElectionBean:public CUMQClient,public BaseCore::Clock::TimerListener
{
	friend class BMSHeartTimeOutCMD;
	friend class CountCurTermWinVoteCMD;
	friend class RequestVoteFromOtherBMSCMD;
public:
	CULeaderElectionBean();//

	virtual ~CULeaderElectionBean();

	//是否与Leader已经建立连接，如果自身就是Leader则也返回true
	bool ConnectedWithLeader();

	virtual void OnMessage(int type,std::string message);

	int StartService(void);
	void StopService(void);


protected:

	void SetQUEUE_Leader(std::string queue_leader);
	void SetTOPIC_Colony(std::string topic_colony);

	void SetUUID(std::string uuid);

	void SetRandomValue(int randomValue);

	void SetMqBrokeUrl( std::string mqBrokeUrl);

	void SetIP(std::string ip);

	void SetLeaderListenPort(int leaderListenPort);

	void SetModelNumbers(int modelNumbers);

	void SetModelHeartTimeOutMilSec(int modelHeartTimeOutMilSec);


	void OnTimeOut(int hHandle);

	enum ROLE
	{
		LEADER,
		FOLLOWER,
		CANDIDATE
	};

	int OnReceiveCommand(CommandBase *pMsg);

	//转变成Leader
	void TransformToLeader();

	virtual void OnTransformToLeader();

	//message包含其他模块发送过来的请求投票信息
	void VoteToOther(std::string message);

	//获取其他模块发送过来的投票 message包含其他模块发送过来的投票
	void GetOtherBMSVote(std::string message);

	void DealWithLeaderBroadCast(std::string message);

	virtual void OnDealWithLeaderBroadCast();

	void DealWithBMSHeart(std::string message);


	virtual void OnDealWithBMSHeart(com::arges::file::proto::BMSHeart &bmsHeart);

	/** 增加当前周期数并开启一个计时器 
	 * return void:
	 */
	void UpdateCurTerm(int AddTermValue=1);

	virtual void OnUpdateCurTerm();

	//向其他BMS发送获取投票请求	
	void RequestVoteFromOtherBMS();

	//统计当前竞选Leader周期的得票数
	int CountCurTermWinVote();

	void LeaderBroadcast();

	virtual void OnLeaderBroadcast();

	/** 核对周期数，如果周期数等于当前BMS的周期数则返回0,否则返回-1 
	 * @param[in] term: 比较的周期数
	 * return int: 如果周期数等于当前BMS的周期数则返回0，否则返回-1
	 */
	int CheckTerm(int term);


	int GetMilliSec(int interval=100,int multiValue=1);

	///////////////////
	void CreateLeaderOutMsgConsumer();
	void EnableLeaderOutMsgConsumer();
	void DisableLeaderOutMsgConsumer();
	void DestroyLeaderOutMsgConsumer();

protected:
	int m_curTerm;//当前选举周期数目
	std::string m_strBMSUUID;//当前BMS的唯一标识符
	int m_randomValue;//计算m_strBMSUUID的每个元素的ASCII值的和，用户求随机值

	boost::shared_ptr<BaseCore::Clock::Timer> m_spCountCurWinVoteTimer;  //用于统计当前周期的的票数
	BaseCore::Clock::Timer m_bmsHeartTimer;  //用于BMS和Leader之间维护心跳的定时器
	BaseCore::Clock::Timer m_leaderBroadcast;//用于Leader广播
	boost::shared_ptr<BaseCore::Clock::Timer> m_spCandidateTimer;//用于从Follow状态切换到candidate状态

	long m_lastHeartTime;  //当当前BMS不是Leader的时候该值表示最近一次收到Leader的广播数据包
	int  m_curRole;//当前BMS的角色，初始角色是Follower
	bool m_bConnectWithLeader;//是否与Leader已经建立连接
	
	bool m_bFinfishCurTremVote;//每个选举周期只有一次投票机会，将该票投递出去是设置真，否则为假
	int m_nCurTremWinVote;//当前选举周期获得的投票数目
	BaseCore::Threads::Mutex *m_pMutex;

	std::string m_mqBrokeUrl;
	std::string m_ip;
	int m_leaderListenPort;
	int m_modelNumbers;
	int m_modelHeartTimeOutMilSec;


	std::string QUEUE_Leader;
	std::string TOPIC_Colony;
};




#endif //CUBMSLEADERELECTIONBEAN_H_