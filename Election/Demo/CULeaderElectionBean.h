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

	//�Ƿ���Leader�Ѿ��������ӣ�����������Leader��Ҳ����true
	bool ConnectedWithLeader();

	/** MQ���ݽ��ջص����� 
	 * @param[in] type:���ݵ�����
	 * @param[in] message����������
	 */
	virtual void OnMessage(int type,std::string message);

	/** �������� 
	 */
	int StartService(void);

	/** �رշ���
	 */
	void StopService(void);


	//�ڵ���StartService����֮ǰ������õļ������ú���
	/** ����Leader��������������ݵ�MQ������ 
	 * @param[in] queue_leader��Leader�������ݵ�MQ������
	 */
	void SetQUEUE_Leader(std::string queue_leader);

	/** ��Ⱥѡ��ʱʹ�õĹ㲥��·��
	 * @param[in] topic_colony: ��Ⱥ�㲥��
	 */
	void SetTOPIC_Colony(std::string topic_colony);

	/** ���õ�ǰ�����Ψһ��ʶ�� 
	 * @param[in] uuid����ǰ�����Ψһ��ʶ��
	 */
	void SetUUID(std::string uuid);

	/** ���÷���ʹ�õ�MQ ��ַ 
	 * @param[in] mqBrokeUrl:����ʹ�õ�mq��ַ
	 */
	void SetMqBrokeUrl( std::string mqBrokeUrl);


	/** ���õ�ǰ��Ⱥ�����з���ĸ��� 
	 * @param[in] modelNumbers:��Ⱥ�������
	 */
	void SetModelNumbers(int modelNumbers);


public:
	//////////////////////////////�⼸���������Բ�������

	/** ���÷���֮��������ʱ���� 
	 * @param[in] modelHeartTimeOutMilSec: ��ʱ����
	 */
	void SetModelHeartTimeOutMilSec(int modelHeartTimeOutMilSec);

	/** ���õ�ǰ�����ip��ַ
	 * @param[in]  ip:��ǰ�����ip��ַ
	 */
	void SetIP(std::string ip);

	/** ����ǰ�����Ϊleader֮����Ҫ�����ļ����˿� 
	 * @param[in] leaderListenPort:leader�����˿�
	 */
	void SetLeaderListenPort(int leaderListenPort);

	/** ����leader�ڹ㲥��ʱ���͵Ĺ㲥���ݣ����ÿ��ַ����������֮ǰ�Ĺ㲥�������� 
	 * @param[in] 
	 */
	void SetBroadcastContent(std::string content);

	/**���õ�ǰ��������ڸ�leader������������ʱ���������
	 * @param[in] 
	 */
	void SetServerHeartContent(std::string content);
	
	/** ����ǰ������leader��ʱ����øú������Ի�ȡ���������������Ϣ,map������key�Ƿ���id,value���������񷢸�leader���������ݣ�ÿ������������������ݰ��а����������Ϣ
	 */
	std::map<std::string ,std::string> GetAllServerInfo();

protected:
	
	/** ��ǰ�������յ�leader�Ĺ㲥����ʱ���е�һЩ��ع��� 
	 * @param[in] content: �ص�����������leader�����Ĺ㲥��������
	 */
	virtual void OnDealWithLeaderBroadCast(std::string leaderid,std::string content);

	/** ����ǰ������leaderʱ���յ����������͹������������ݰ��ص�����
	 */
	virtual void OnDealWithServerHeart(std::string  serverid,std::string  content);

	/**	�����½���leaderѡ�ٵ�ʱ����еĸ��µ�ǰ���ڲ�����ÿ�����½���leaderѡ�ٵ�ʱ����Խ�һЩ��ʼ������������ص�������
	 */
	virtual void OnUpdateCurTerm();

	//����ǰ������leaderʱ�����й㲥��ʱ����õĻص������������ڸú����ڲ�ִ��һЩleder��صĹ���
	virtual void OnLeaderBroadcast();


	/** ����ǰ����ת��Ϊleaderʱ���еĻص�����������ʵ�ָ��麯�����ڸú����н���ת���leader��Ҫ����һЩ��ز���
	 */
	virtual void OnTransformToLeader();

	//���յ�Consul���͹�����server�ҵ�֪ͨ����ɾ��ĳ��server������������  reduceServerIdVec���server��ID��
	virtual void OnServerReduce(std::vector<std::string>  reduceServerIdVec);


	virtual void OnServerNumsAdd(int addedServerNums);
protected:

	//////////////////////////////////////////////////�ڲ�����

	/** ��ʱ���ص����� 
	 * @param[in] hHandle������ָ�����ĸ���ʱ��������
	 */
	void OnTimeOut(int hHandle);

	enum ROLE
	{
		LEADER,
		FOLLOWER,
		CANDIDATE
	};

	/** ����ص����� 
	 * @param[in] pMsg�������������Ϣ
	 */
	int OnReceiveCommand(CommandBase *pMsg);

	//ת���Leader
	void TransformToLeader();

	//message��������ģ�鷢�͹���������ͶƱ��Ϣ
	void VoteToOther(std::string message);

	//��ȡ����ģ�鷢�͹�����ͶƱ message��������ģ�鷢�͹�����ͶƱ
	void GetOtherBMSVote(std::string message);

	/** ��ǰ�����յ�leader���͹����Ĺ㲥���ݰ� 
	 * @param[in] message: leader���͹����Ĺ㲥���ݰ�
	 */
	void DealWithLeaderBroadCast(std::string message);

	/** ����ǰ������leaderʱ���������������͹������������� 
	 * @param[in] message:���������͹������������ݰ�
	 */
	void DealWithServerHeart(std::string message);

	/** ���ӵ�ǰ������������һ����ʱ�� 
	 * return void:
	 */
	void UpdateCurTerm(int AddTermValue=1);


	//�����������ͻ�ȡͶƱ����	
	void RequestVoteFromOtherBMS();

	//ͳ�Ƶ�ǰ��ѡLeader���ڵĵ�Ʊ��
	int CountCurTermWinVote();


	/** ����ǰ�����Ϊleader֮����й㲥
	 */
	void LeaderBroadcast();


	/** �˶���������������������ڵ�ǰ������������򷵻�0,���򷵻�-1 
	 * @param[in] term: �Ƚϵ�������
	 * return int: ������������ڵ�ǰ������������򷵻�0�����򷵻�-1
	 */
	int CheckTerm(int term);


	/** ��ȡһ����������� 
	 * @param[in] interval: �����Χ
	 * @param[in] multiValue: �Ŵ���
	 * return int: ���ز����ĺ�����
	 */
	int GetMilliSec(int interval=100,int multiValue=1);

	///////////////////
	/** ����leader�������������Ϣ��mq����
	 */
	void CreateLeaderOutMsgConsumer();

	/** ʹ��leader�������������Ϣ��mq����
	 */
	void EnableLeaderOutMsgConsumer();

	/** ����leader�������������Ϣ��mq����
	 */
	void DisableLeaderOutMsgConsumer();

	/** ����leader�������������Ϣ��mq����
	 */
	void DestroyLeaderOutMsgConsumer();

protected:
	std::map<std::string ,std::string> m_serverInfo;//����ǰ������leader��ʱ�򱣴����з������Ϣ
	std::string m_broadcastContent;//leader�㲥��������
	std::string m_serverHeartContent;//��ǰ�����leader���͵�������������
	int m_curTerm;//��ǰѡ��������Ŀ
	std::string m_strUUID;//Ψһ��ʶ��
	int m_randomValue;//����m_strUUID��ÿ��Ԫ�ص�ASCIIֵ�ĺͣ��û������ֵ
	boost::shared_ptr<BaseCore::Clock::Timer> m_spCountCurWinVoteTimer;  //����ͳ�Ƶ�ǰ���ڵĵ�Ʊ��
	BaseCore::Clock::Timer m_bmsHeartTimer;  //���ڵ�ǰ�����Leader֮��ά�������Ķ�ʱ��
	BaseCore::Clock::Timer m_leaderBroadcast;//����Leader�㲥
	boost::shared_ptr<BaseCore::Clock::Timer> m_spCandidateTimer;//���ڴ�Follow״̬�л���candidate״̬
	long m_lastHeartTime;  //��������Leader��ʱ���ֵ��ʾ���һ���յ�Leader�Ĺ㲥���ݰ�
	int  m_curRole;//��ǰ����Ľ�ɫ����ʼ��ɫ��Follower
	bool m_bConnectWithLeader;//�Ƿ���Leader�Ѿ���������
	bool m_bFinfishCurTremVote;//ÿ��ѡ������ֻ��һ��ͶƱ���ᣬ����ƱͶ�ݳ�ȥ�������棬����Ϊ��
	int m_nCurTremWinVote;//��ǰѡ�����ڻ�õ�ͶƱ��Ŀ
	BaseCore::Threads::Mutex *m_pMutex;
	std::string m_mqBrokeUrl;//MQ������ַ
	std::string m_ip;//��ǰ�����ip��ַ
	int m_leaderListenPort;//���÷����Ϊleader�����ļ����˿ڣ����Բ�����
	int m_modelNumbers;//��ǰ��Ⱥ�����ܸ���
	int m_modelHeartTimeOutMilSec;//����֮������������ʱ����
	std::string QUEUE_Leader;//leader��������������ݵ�MQ������
	std::string TOPIC_Colony;//leaderѡ��ʱ�õĹ㲥��
	bool m_bStarted;//�Ƿ��Ѿ���������
};




#endif //CUBMSLEADERELECTIONBEAN_H_