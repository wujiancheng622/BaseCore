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
		breif : �����߳�
		return : void
	*/
	void Start();


	/*
		breif : �ر��߳�
		return : void
	*/
	void Stop();


	/*
		breif : �Ƿ��Ѿ������߳�
		return : bool ��ǰ���������棬���򷵻�false
	*/
	bool Is_Started();
	
	/*
		breif : �̺߳����������������ظú������ڸú�����ִ������̹߳���
		return :void
	*/
	virtual void Run()
	{
		
	}

	/*
		breif :Run����ִ��һ��������ڽ�����һ�β���֮ǰ��sleepʱ�䣬Ĭ����5���룬��������������������������ﵽ���Ƹ��̵߳�Sleepʱ����
		return :void
	*/
	virtual void Sleep();
	
	/*
		breif :��̬��������ִ��sleep����
		param :millisec ˯��ʱ��
		return : void
	*/
	static void Sleep(int millisec );


	void SetDesc(string desc);

protected:

	static void StartThread(ThreadCoreBase *pThis);


//private:
public:
	thread *m_pThread;		
	bool m_bStart;//�Ƿ������߳�
	bool m_bStop;//�Ƿ��Ѿ�ֹͣ�߳�
	string m_desc;
};

}
}



#endif  //THREADCOREBASE_H_
