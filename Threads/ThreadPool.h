#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_

//线程池头文件

#include "CrossPlatform.h"
#include "Condition.h"



namespace BaseCore
{
namespace Threads
{

//封装线程池中的对象需要执行的任务对象
class DLL_CLASS task_t
{
public:
	task_t():run(NULL),arg(NULL),next(NULL){}
	void *(*run)(void *args,bool *bReRun);  //函数指针，需要执行的任务
	void *arg;              //参数
	task_t  *next;      //任务队列中下一个任务
};


//下面是线程池结构体
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
	condition_t ready;    //状态量
	task_t *first;       //任务队列中第一个任务
	task_t *last;        //任务队列中最后一个任务
	int counter;         //线程池中已有线程数
	int idle;            //线程池中空闲线程数
	int max_threads;     //线程池最大线程数
	int quit;            //是否退出标志
};


//线程池初始化 如果threads是-1标识线程数不受限
void DLL_CLASS threadpool_init(threadpool *pool, int threads=5);

//往线程池中加入任务
void DLL_CLASS threadpool_add_task(threadpool *pool, void *(*run)(void *arg,bool *bReRun),void *arg);

//摧毁线程池
void DLL_CLASS threadpool_destroy(threadpool *pool);


int DLL_CLASS GetCurRunningThreadsNums(threadpool *pool);

int DLL_CLASS GetCurIdleThreadsNums(threadpool *pool);

int DLL_CLASS GetCurAllThreadsNums(threadpool *pool);


}
}

#endif