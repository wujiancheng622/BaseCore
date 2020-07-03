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

	//�Ƿ���Leader�Ѿ��������ӣ�����������Leader��Ҳ����true
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

	//ת���Leader
	void TransformToLeader();

	virtual void OnTransformToLeader();

	//message��������ģ�鷢�͹���������ͶƱ��Ϣ
	void VoteToOther(std::string message);

	//��ȡ����ģ�鷢�͹�����ͶƱ message��������ģ�鷢�͹�����ͶƱ
	void GetOtherBMSVote(std::string message);

	void DealWithLeaderBroadCast(std::string message);

	virtual void OnDealWithLeaderBroadCast();

	void DealWithBMSHeart(std::string message);


	virtual void OnDealWithBMSHeart(com::arges::file::proto::BMSHeart &bmsHeart);

	/** ���ӵ�ǰ������������һ����ʱ�� 
	 * return void:
	 */
	void UpdateCurTerm(int AddTermValue=1);

	virtual void OnUpdateCurTerm();

	//������BMS���ͻ�ȡͶƱ����	
	void RequestVoteFromOtherBMS();

	//ͳ�Ƶ�ǰ��ѡLeader���ڵĵ�Ʊ��
	int CountCurTermWinVote();

	void LeaderBroadcast();

	virtual void OnLeaderBroadcast();

	/** �˶���������������������ڵ�ǰBMS���������򷵻�0,���򷵻�-1 
	 * @param[in] term: �Ƚϵ�������
	 * return int: ������������ڵ�ǰBMS���������򷵻�0�����򷵻�-1
	 */
	int CheckTerm(int term);


	int GetMilliSec(int interval=100,int multiValue=1);

	///////////////////
	void CreateLeaderOutMsgConsumer();
	void EnableLeaderOutMsgConsumer();
	void DisableLeaderOutMsgConsumer();
	void DestroyLeaderOutMsgConsumer();

protected:
	int m_curTerm;//��ǰѡ��������Ŀ
	std::string m_strBMSUUID;//��ǰBMS��Ψһ��ʶ��
	int m_randomValue;//����m_strBMSUUID��ÿ��Ԫ�ص�ASCIIֵ�ĺͣ��û������ֵ

	boost::shared_ptr<BaseCore::Clock::Timer> m_spCountCurWinVoteTimer;  //����ͳ�Ƶ�ǰ���ڵĵ�Ʊ��
	BaseCore::Clock::Timer m_bmsHeartTimer;  //����BMS��Leader֮��ά�������Ķ�ʱ��
	BaseCore::Clock::Timer m_leaderBroadcast;//����Leader�㲥
	boost::shared_ptr<BaseCore::Clock::Timer> m_spCandidateTimer;//���ڴ�Follow״̬�л���candidate״̬

	long m_lastHeartTime;  //����ǰBMS����Leader��ʱ���ֵ��ʾ���һ���յ�Leader�Ĺ㲥���ݰ�
	int  m_curRole;//��ǰBMS�Ľ�ɫ����ʼ��ɫ��Follower
	bool m_bConnectWithLeader;//�Ƿ���Leader�Ѿ���������
	
	bool m_bFinfishCurTremVote;//ÿ��ѡ������ֻ��һ��ͶƱ���ᣬ����ƱͶ�ݳ�ȥ�������棬����Ϊ��
	int m_nCurTremWinVote;//��ǰѡ�����ڻ�õ�ͶƱ��Ŀ
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