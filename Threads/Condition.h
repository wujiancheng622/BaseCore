#ifndef _CONDITION_H_
#define _CONDITION_H_


#include "CrossPlatform.h"

namespace boost
{
	class mutex;
	class condition_variable_any;
}

namespace BaseCore
{
	namespace Threads
	{

	//��װһ��������������������Ϊ״̬
	class  DLL_CLASS condition_t
	{
	public:
		condition_t():pMutex(NULL),pCondVar(NULL){}
		boost::mutex *pMutex;
		boost::condition_variable_any *pCondVar;
	};

	//��״̬�Ĳ�������
	int DLL_CLASS condition_init(condition_t *cond);
	int DLL_CLASS condition_lock(condition_t *cond);
	int DLL_CLASS condition_unlock(condition_t *cond);
	int DLL_CLASS condition_wait(condition_t *cond);
	int DLL_CLASS condition_timedwait(condition_t *cond, int waitMilSec);
	int DLL_CLASS condition_signal(condition_t* cond);
	int DLL_CLASS condition_broadcast(condition_t *cond);
	int DLL_CLASS condition_destroy(condition_t *cond);

	}
}


#endif