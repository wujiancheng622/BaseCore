#ifndef CUBMSLEADERELECTIONBEAN_H_
#define CUBMSLEADERELECTIONBEAN_H_


#include <time.h>
#include <map>
#include <vector>
#include <unistd.h>
#include <boost/shared_ptr.hpp>
#include "CUMQClient.h"
#include "Timer.h"


class CULeaderElectionBean:public CUMQClient,public BaseCore::Clock::TimerListener
{
	friend class BMSHeartTimeOutCMD;
	friend class CountCurTermWinVoteCMD;
	friend class RequestVoteFromOtherBMSCMD;
	friend class ServerNumsChangeCMD;
public:
	CULeaderElectionBean();//

	virtual ~CULeaderElectionBean();

	//是否与Leader已经建立连接，如果自身就是Leader则也返回true
	bool ConnectedWithLeader();

	/** MQ数据接收回调函数 
	 * @param[in] type:数据的类型
	 * @param[in] message：数据内容
	 */
	virtual void OnMessage(int type,std::string message);

	/** 启动服务 
	 */
	int StartService(void);

	/** 关闭服务
	 */
	void StopService(void);


	//在调用StartService函数之前必须调用的几个设置函数
	/** 设置Leader用来接受外界数据的MQ队列名 
	 * @param[in] queue_leader：Leader接受数据的MQ队列名
	 */
	void SetQUEUE_Leader(std::string queue_leader);

	/** 集群选举时使用的广播链路名
	 * @param[in] topic_colony: 集群广播名
	 */
	void SetTOPIC_Colony(std::string topic_colony);

	/** 设置当前服务的唯一标识符 
	 * @param[in] uuid：当前服务的唯一标识符
	 */
	void SetUUID(std::string uuid);

	/** 设置服务使用的MQ 地址 
	 * @param[in] mqBrokeUrl:服务使用的mq地址
	 */
	void SetMqBrokeUrl( std::string mqBrokeUrl);


	/** 设置当前集群中所有服务的个数 
	 * @param[in] modelNumbers:集群服务个数
	 */
	void SetModelNumbers(int modelNumbers);


public:
	//////////////////////////////这几个函数可以不用设置

	/** 设置服务之间心跳超时毫秒 
	 * @param[in] modelHeartTimeOutMilSec: 超时毫秒
	 */
	void SetModelHeartTimeOutMilSec(int modelHeartTimeOutMilSec);

	/** 设置当前服务的ip地址
	 * @param[in]  ip:当前服务的ip地址
	 */
	void SetIP(std::string ip);

	/** 当当前服务成为leader之后需要开启的监听端口 
	 * @param[in] leaderListenPort:leader监听端口
	 */
	void SetLeaderListenPort(int leaderListenPort);

	/** 设置leader在广播的时候发送的广播数据，设置空字符串可以清楚之前的广播数据内容 
	 * @param[in] 
	 */
	void SetBroadcastContent(std::string content);

	/**设置当前服务服务在给leader发送心跳数据时候的心跳包
	 * @param[in] 
	 */
	void SetServerHeartContent(std::string content);
	
	/** 当当前服务是leader的时候调用该函数可以获取所有其他服务的信息,map容器的key是服务id,value是其他服务发给leader的心跳数据，每个服务可以在心跳数据包中包含自身的信息
	 */
	std::map<std::string ,std::string> GetAllServerInfo();

protected:
	
	/** 当前服务在收到leader的广播数据时进行的一些相关工作 
	 * @param[in] content: 回调函数，包含leader发布的广播数据内容
	 */
	virtual void OnDealWithLeaderBroadCast(std::string leaderid,std::string content);

	/** 当当前服务是leader时接收到其他服务发送过来的心跳数据包回调函数
	 */
	virtual void OnDealWithServerHeart(std::string  serverid,std::string  content);

	/**	当重新进行leader选举的时候进行的跟新当前周期操作，每次重新进行leader选举的时候可以将一些初始工作放在这个回调函数中
	 */
	virtual void OnUpdateCurTerm();

	//当当前服务是leader时并进行广播的时候调用的回调函数，可以在该函数内部执行一些leder相关的工作
	virtual void OnLeaderBroadcast();


	/** 当当前服务转变为leader时进行的回调函数，重新实现该虚函数，在该函数中进行转变成leader后要做的一些相关操作
	 */
	virtual void OnTransformToLeader();

	//当收到Consul发送过来的server挂掉通知或者删除某个server后调用这个函数  reduceServerIdVec存放server的ID号
	virtual void OnServerReduce(std::vector<std::string>  reduceServerIdVec);


	virtual void OnServerNumsAdd(int addedServerNums);
protected:

	//////////////////////////////////////////////////内部函数

	/** 定时器回调函数 
	 * @param[in] hHandle：用来指明是哪个定时器产生的
	 */
	void OnTimeOut(int hHandle);

	enum ROLE
	{
		LEADER,
		FOLLOWER,
		CANDIDATE
	};

	/** 命令回调函数 
	 * @param[in] pMsg：具体的命令消息
	 */
	int OnReceiveCommand(CommandBase *pMsg);

	//转变成Leader
	void TransformToLeader();

	//message包含其他模块发送过来的请求投票信息
	void VoteToOther(std::string message);

	//获取其他模块发送过来的投票 message包含其他模块发送过来的投票
	void GetOtherBMSVote(std::string message);

	/** 当前服务收到leader发送过来的广播数据包 
	 * @param[in] message: leader发送过来的广播数据包
	 */
	void DealWithLeaderBroadCast(std::string message);

	/** 当当前服务是leader时，处理其他服务发送过来的心跳数据 
	 * @param[in] message:其他服务发送过来的心跳数据包
	 */
	void DealWithServerHeart(std::string message);

	/** 增加当前周期数并开启一个计时器 
	 * return void:
	 */
	void UpdateCurTerm(int AddTermValue=1);


	//向其他服务发送获取投票请求	
	void RequestVoteFromOtherBMS();

	//统计当前竞选Leader周期的得票数
	int CountCurTermWinVote();


	/** 当当前服务成为leader之后进行广播
	 */
	void LeaderBroadcast();


	/** 核对周期数，如果周期数等于当前服务的周期数则返回0,否则返回-1 
	 * @param[in] term: 比较的周期数
	 * return int: 如果周期数等于当前服务的周期数则返回0，否则返回-1
	 */
	int CheckTerm(int term);


	/** 获取一个随机毫秒数 
	 * @param[in] interval: 间隔范围
	 * @param[in] multiValue: 放大倍数
	 * return int: 返回产生的毫秒数
	 */
	int GetMilliSec(int interval=100,int multiValue=1);

	///////////////////
	/** 创建leader用来接受外界消息的mq队列
	 */
	void CreateLeaderOutMsgConsumer();

	/** 使能leader用来接收外界消息的mq队列
	 */
	void EnableLeaderOutMsgConsumer();

	/** 禁用leader用来接收外界消息的mq队列
	 */
	void DisableLeaderOutMsgConsumer();

	/** 销毁leader用来接收外界消息的mq队列
	 */
	void DestroyLeaderOutMsgConsumer();

protected:
	std::map<std::string ,std::string> m_serverInfo;//当当前服务是leader的时候保存所有服务的信息
	std::string m_broadcastContent;//leader广播数据内容
	std::string m_serverHeartContent;//当前服务给leader发送的心跳数据内容
	int m_curTerm;//当前选举周期数目
	std::string m_strUUID;//唯一标识符
	int m_randomValue;//计算m_strUUID的每个元素的ASCII值的和，用户求随机值
	boost::shared_ptr<BaseCore::Clock::Timer> m_spCountCurWinVoteTimer;  //用于统计当前周期的的票数
	BaseCore::Clock::Timer m_bmsHeartTimer;  //用于当前服务和Leader之间维护心跳的定时器
	BaseCore::Clock::Timer m_leaderBroadcast;//用于Leader广播
	boost::shared_ptr<BaseCore::Clock::Timer> m_spCandidateTimer;//用于从Follow状态切换到candidate状态
	long m_lastHeartTime;  //当服务不是Leader的时候该值表示最近一次收到Leader的广播数据包
	int  m_curRole;//当前服务的角色，初始角色是Follower
	bool m_bConnectWithLeader;//是否与Leader已经建立连接
	bool m_bFinfishCurTremVote;//每个选举周期只有一次投票机会，将该票投递出去是设置真，否则为假
	int m_nCurTremWinVote;//当前选举周期获得的投票数目
	BaseCore::Threads::Mutex *m_pMutex;
	std::string m_mqBrokeUrl;//MQ主机地址
	std::string m_ip;//当前服务的ip地址
	int m_leaderListenPort;//当该服务成为leader后开启的监听端口，可以不用设
	int m_modelNumbers;//当前集群服务总个数
	int m_modelHeartTimeOutMilSec;//服务之间心跳心跳超时毫秒
	std::string QUEUE_Leader;//leader用来接受外界数据的MQ队列名
	std::string TOPIC_Colony;//leader选举时用的广播名
	bool m_bStarted;//是否已经启动服务
};




#endif //CUBMSLEADERELECTIONBEAN_H_