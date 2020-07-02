#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <boost/lexical_cast.hpp>
#include <boost/thread.hpp>
#include <boost/thread/lock_factories.hpp>
#include "ThreadPool.h"



using namespace boost;


namespace BaseCore
{
namespace Threads
{

#define  MAXTHREADS 65535

//�������߳�ִ��
void *thread_routine(void *arg)
{
	
	
	threadpool *pool = (threadpool *)arg;//��ȡ�̳߳�ָ��
        std::string threadId = boost::lexical_cast<std::string>(boost::this_thread::get_id());
	printf("\n thread %s is starting pool->count:%d  \n", threadId.c_str(),pool->counter);//��ӡ�߳�id
	while(true)
	{
		//�����̳߳�֮ǰ��Ҫ����
		//printf("\n thread_routine 1\n");
		bool timeout=false;
		condition_lock(&pool->ready);
		//����
		pool->idle++;
		//�ȴ������������� ���� �յ��̳߳�����֪ͨ
		while(pool->first == NULL && !pool->quit)
		{
			//�����߳������ȴ�
                        std::string threadId = boost::lexical_cast<std::string>(boost::this_thread::get_id());
			printf("thread %s is waiting  test \n", threadId.c_str());
			int status;
			status = condition_timedwait(&pool->ready, 2000);  //�ú�������������������̷߳��ʣ���������ʱ������
			//printf("\n status:%d ETIMEDOUT:%d \n",status,ETIMEDOUT);
			if(status == ETIMEDOUT)
			{
				printf("thread %s wait timed out\n", threadId.c_str());
				timeout = true;
				break;
			}
		}

		pool->idle--;
		if(pool->first != NULL)
		{
			//ȡ���ȴ�������ǰ�������Ƴ����񣬲�ִ������
			task_t *t = pool->first;
			pool->first = t->next;
			//��������ִ����Ҫ����ʱ�䣬�Ƚ����������̷߳����̳߳�
			condition_unlock(&pool->ready);
			//ִ������			
			bool bReRun=false;
			t->run(t->arg,&bReRun);
			condition_lock(&pool->ready);

			if (bReRun)
			{
				//����һ���µ�����
				task_t *newtask = (task_t *)malloc(sizeof(task_t));
				newtask->run = t->run;
				newtask->arg = t->arg;
				newtask->next=NULL;//�¼ӵ�������ڶ���β��
				if(pool->first == NULL)//��һ���������
				{
					pool->first = newtask;
				}        
				else    
				{
					pool->last->next = newtask;
				}
				pool->last = newtask;  //����βָ���¼�����߳�
			}

			//ִ���������ͷ��ڴ�
			free(t);
			//���¼���
			//printf("\n thread_routine 2\n");
			
		}

		//�˳��̳߳�
		if(pool->quit && pool->first == NULL)
		{
			
			pool->counter--;//��ǰ�������߳���-1

			printf("\n exit thread count:%d \n",pool->counter);
			//���̳߳���û���̣߳�֪ͨ�ȴ��̣߳����̣߳�ȫ�������Ѿ����
			if(pool->counter == 0)
			{
				condition_signal(&pool->ready);
			}
			condition_unlock(&pool->ready);
			break;
		}
		//��ʱ�����������߳�
		if(timeout == true)
		{
			pool->counter--;//��ǰ�������߳���-1
			condition_unlock(&pool->ready);
			break;
		}

		condition_unlock(&pool->ready);
	}

	printf("thread %s is exiting\n", threadId.c_str());
	return NULL;

}


//�̳߳س�ʼ��
void threadpool_init(threadpool *pool, int threads)
{

	condition_init(&pool->ready);
	pool->first = NULL;
	pool->last =NULL;
	//printf("\n threadpool_init \n");
	pool->counter =0;
	pool->idle =0;

	if (threads == -1 )
	{
		pool->max_threads = MAXTHREADS;
	}
	else
	{
		pool->max_threads = threads;
	}
	
	pool->quit =0;

}


//����һ�������̳߳�
void threadpool_add_task(threadpool *pool, void *(*run)(void *arg,bool *bReRun), void *arg)
{
	//����һ���µ�����
	task_t *newtask = (task_t *)malloc(sizeof(task_t));
	newtask->run = run;
	newtask->arg = arg;
	newtask->next=NULL;//�¼ӵ�������ڶ���β��

	
	//printf("\n threadpool_add_task wait 1 \n");
	//�̳߳ص�״̬������̹߳�������ǰ��Ҫ����
	condition_lock(&pool->ready);
	//printf("\n threadpool_add_task wait 2 \n");

	if(pool->first == NULL)//��һ���������
	{
		pool->first = newtask;
	}        
	else    
	{
		pool->last->next = newtask;
	}
	pool->last = newtask;  //����βָ���¼�����߳�



	printf("\n in threadpool_add_task pool->idle :%d pool->counter :%d pool->max_threads:%d \n",pool->idle  ,pool->counter ,pool->max_threads);
	//�̳߳������߳̿��У�����
	if(pool->idle > 0)
	{
		printf("\n in threadpool_add_task idle > 0 \n");
		condition_signal(&pool->ready);
	}
	//��ǰ�̳߳����̸߳���û�дﵽ�趨�����ֵ������һ���µ�����
	else if(pool->counter < pool->max_threads)
	{
		//printf("\n in threadpool_add_task start create  pool->counter:%d begin \n",pool->counter);
		new thread(thread_routine,pool);//���������ڴ���ڳ����˳���ʱ���ͷŵ�
		pool->counter++;
		printf("\n in threadpool_add_task start create  pool->counter:%d \n",pool->counter);
	}


	//����������
	condition_unlock(&pool->ready);
}

//�̳߳�����
void threadpool_destroy(threadpool *pool)
{
	//����Ѿ��������٣�ֱ�ӷ���
	if(pool->quit)
	{
		return;
	}
	//����
	condition_lock(&pool->ready);
	//�������ٱ��Ϊ1
	pool->quit = 1;
	//�̳߳����̸߳�������0
	if(pool->counter > 0)
	{
		//���ڵȴ����̣߳������źŻ���
		if(pool->idle > 0)
		{
			condition_broadcast(&pool->ready);
		}
		//����ִ��������̣߳��ȴ����ǽ�������
		while(pool->counter)
		{
			condition_wait(&pool->ready);
		}
	}
	condition_unlock(&pool->ready);
	condition_destroy(&pool->ready);
}

int  GetCurRunningThreadsNums( threadpool *pool )
{
	return pool->counter-pool->idle;
}

int  GetCurIdleThreadsNums( threadpool *pool )
{
	return pool->idle;
}

int  GetCurAllThreadsNums( threadpool *pool )
{
	return pool->counter;
}

threadpool * threadpool::m_pInstance=NULL;
boost::mutex threadpool::m_mutex;


threadpool* threadpool::Instance()
{
	m_mutex.lock();
	if(NULL==m_pInstance )
	{
		m_pInstance=new threadpool;
	}
	m_mutex.unlock();
	return m_pInstance;  
}

void threadpool::Release()
{
	m_mutex.lock();
	if(m_pInstance)
	{
		delete m_pInstance;
		m_pInstance=NULL;
	}
	m_mutex.unlock();
}

}
}