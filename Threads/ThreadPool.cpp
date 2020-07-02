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

//创建的线程执行
void *thread_routine(void *arg)
{
	
	
	threadpool *pool = (threadpool *)arg;//获取线程池指针
        std::string threadId = boost::lexical_cast<std::string>(boost::this_thread::get_id());
	printf("\n thread %s is starting pool->count:%d  \n", threadId.c_str(),pool->counter);//打印线程id
	while(true)
	{
		//访问线程池之前需要加锁
		//printf("\n thread_routine 1\n");
		bool timeout=false;
		condition_lock(&pool->ready);
		//空闲
		pool->idle++;
		//等待队列有任务到来 或者 收到线程池销毁通知
		while(pool->first == NULL && !pool->quit)
		{
			//否则线程阻塞等待
                        std::string threadId = boost::lexical_cast<std::string>(boost::this_thread::get_id());
			printf("thread %s is waiting  test \n", threadId.c_str());
			int status;
			status = condition_timedwait(&pool->ready, 2000);  //该函数会解锁，允许其他线程访问，当被唤醒时，加锁
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
			//取出等待队列最前的任务，移除任务，并执行任务
			task_t *t = pool->first;
			pool->first = t->next;
			//由于任务执行需要消耗时间，先解锁让其他线程访问线程池
			condition_unlock(&pool->ready);
			//执行任务			
			bool bReRun=false;
			t->run(t->arg,&bReRun);
			condition_lock(&pool->ready);

			if (bReRun)
			{
				//产生一个新的任务
				task_t *newtask = (task_t *)malloc(sizeof(task_t));
				newtask->run = t->run;
				newtask->arg = t->arg;
				newtask->next=NULL;//新加的任务放在队列尾端
				if(pool->first == NULL)//第一个任务加入
				{
					pool->first = newtask;
				}        
				else    
				{
					pool->last->next = newtask;
				}
				pool->last = newtask;  //队列尾指向新加入的线程
			}

			//执行完任务释放内存
			free(t);
			//重新加锁
			//printf("\n thread_routine 2\n");
			
		}

		//退出线程池
		if(pool->quit && pool->first == NULL)
		{
			
			pool->counter--;//当前工作的线程数-1

			printf("\n exit thread count:%d \n",pool->counter);
			//若线程池中没有线程，通知等待线程（主线程）全部任务已经完成
			if(pool->counter == 0)
			{
				condition_signal(&pool->ready);
			}
			condition_unlock(&pool->ready);
			break;
		}
		//超时，跳出销毁线程
		if(timeout == true)
		{
			pool->counter--;//当前工作的线程数-1
			condition_unlock(&pool->ready);
			break;
		}

		condition_unlock(&pool->ready);
	}

	printf("thread %s is exiting\n", threadId.c_str());
	return NULL;

}


//线程池初始化
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


//增加一个任务到线程池
void threadpool_add_task(threadpool *pool, void *(*run)(void *arg,bool *bReRun), void *arg)
{
	//产生一个新的任务
	task_t *newtask = (task_t *)malloc(sizeof(task_t));
	newtask->run = run;
	newtask->arg = arg;
	newtask->next=NULL;//新加的任务放在队列尾端

	
	//printf("\n threadpool_add_task wait 1 \n");
	//线程池的状态被多个线程共享，操作前需要加锁
	condition_lock(&pool->ready);
	//printf("\n threadpool_add_task wait 2 \n");

	if(pool->first == NULL)//第一个任务加入
	{
		pool->first = newtask;
	}        
	else    
	{
		pool->last->next = newtask;
	}
	pool->last = newtask;  //队列尾指向新加入的线程



	printf("\n in threadpool_add_task pool->idle :%d pool->counter :%d pool->max_threads:%d \n",pool->idle  ,pool->counter ,pool->max_threads);
	//线程池中有线程空闲，唤醒
	if(pool->idle > 0)
	{
		printf("\n in threadpool_add_task idle > 0 \n");
		condition_signal(&pool->ready);
	}
	//当前线程池中线程个数没有达到设定的最大值，创建一个新的线性
	else if(pool->counter < pool->max_threads)
	{
		//printf("\n in threadpool_add_task start create  pool->counter:%d begin \n",pool->counter);
		new thread(thread_routine,pool);//这里分配的内存会在程序退出的时候被释放掉
		pool->counter++;
		printf("\n in threadpool_add_task start create  pool->counter:%d \n",pool->counter);
	}


	//结束，访问
	condition_unlock(&pool->ready);
}

//线程池销毁
void threadpool_destroy(threadpool *pool)
{
	//如果已经调用销毁，直接返回
	if(pool->quit)
	{
		return;
	}
	//加锁
	condition_lock(&pool->ready);
	//设置销毁标记为1
	pool->quit = 1;
	//线程池中线程个数大于0
	if(pool->counter > 0)
	{
		//对于等待的线程，发送信号唤醒
		if(pool->idle > 0)
		{
			condition_broadcast(&pool->ready);
		}
		//正在执行任务的线程，等待他们结束任务
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