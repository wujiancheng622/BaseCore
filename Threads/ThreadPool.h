#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_

//�̳߳�ͷ�ļ�

#include "CrossPlatform.h"
#include "Condition.h"



namespace BaseCore
{
namespace Threads
{

//��װ�̳߳��еĶ�����Ҫִ�е��������
class DLL_CLASS task_t
{
public:
	task_t():run(NULL),arg(NULL),next(NULL){}
	void *(*run)(void *args,bool *bReRun);  //����ָ�룬��Ҫִ�е�����
	void *arg;              //����
	task_t  *next;      //�����������һ������
};


//�������̳߳ؽṹ��
class DLL_CLASS threadpool
{
public:
	~threadpool(){}
	static threadpool* Instance();
	static void Release();
protected:
	threadpool(){}
	static threadpool * m_pInstance;
	static boost::mutex m_mutex;
public:
	condition_t ready;    //״̬��
	task_t *first;       //��������е�һ������
	task_t *last;        //������������һ������
	int counter;         //�̳߳��������߳���
	int idle;            //�̳߳��п����߳���
	int max_threads;     //�̳߳�����߳���
	int quit;            //�Ƿ��˳���־
};


//�̳߳س�ʼ�� ���threads��-1��ʶ�߳���������
void DLL_CLASS threadpool_init(threadpool *pool, int threads=5);

//���̳߳��м�������
void DLL_CLASS threadpool_add_task(threadpool *pool, void *(*run)(void *arg,bool *bReRun),void *arg);

//�ݻ��̳߳�
void DLL_CLASS threadpool_destroy(threadpool *pool);


int DLL_CLASS GetCurRunningThreadsNums(threadpool *pool);

int DLL_CLASS GetCurIdleThreadsNums(threadpool *pool);

int DLL_CLASS GetCurAllThreadsNums(threadpool *pool);


}
}

#endif