#ifndef  THREADCOREBASE_H_
#define  THREADCOREBASE_H_

#include <string>
#include "CrossPlatform.h"
#include "Mutex.h"





namespace boost
{
	class thread;
}

using std::string;
using namespace boost;

namespace BaseCore
{
namespace Threads
{




class DLL_CLASS ThreadCoreBase
{
public:
	ThreadCoreBase();
	virtual ~ThreadCoreBase();


	/*
		breif : 启动线程
		return : void
	*/
	void Start();


	/*
		breif : 关闭线程
		return : void
	*/
	void Stop();


	/*
		breif : 是否已经启动线程
		return : bool 以前启动返回真，否则返回false
	*/
	bool Is_Started();
	
	/*
		breif : 线程函数，派生类需重载该函数，在该函数中执行相关线程工作
		return :void
	*/
	virtual void Run()
	{
		
	}

	/*
		breif :Run函数执行一遍操作后在进行下一次操作之前的sleep时间，默认是5毫秒，可以在派生类中重载这个函数达到控制该线程的Sleep时间间隔
		return :void
	*/
	virtual void Sleep();
	
	/*
		breif :静态函数用来执行sleep操作
		param :millisec 睡眠时间
		return : void
	*/
	static void Sleep(int millisec );


	void SetDesc(string desc);

protected:

	static void StartThread(ThreadCoreBase *pThis);


//private:
public:
	thread *m_pThread;		
	bool m_bStart;//是否启动线程
	bool m_bStop;//是否已经停止线程
	string m_desc;
};

}
}



#endif  //THREADCOREBASE_H_
