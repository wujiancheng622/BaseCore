#include <cstdio>
#include <boost/thread.hpp>
#include <boost/thread/lock_factories.hpp>

#include "Condition.h"

using namespace boost;

namespace BaseCore
{
namespace Threads
{


	int condition_init( condition_t *cond )
	{
		cond->pMutex=new boost::mutex;
		cond->pCondVar=new boost::condition_variable_any;
		return 0;
	}

	int condition_lock( condition_t *cond )
	{
		(cond->pMutex)->lock();
		return 0;
	}

	int condition_unlock( condition_t *cond )
	{
		(cond->pMutex)->unlock();
		return 0;
	}

	int condition_wait( condition_t *cond )
	{
		cond->pCondVar->wait( *(cond->pMutex) );
		return 0;
	}

	int condition_timedwait( condition_t *cond, int waitMilSec)
	{
		cv_status status=cond->pCondVar->wait_for( *(cond->pMutex) ,boost::chrono::milliseconds(waitMilSec));
		if (status == cv_status::no_timeout)
		{
			return 0;
		}else if (status == cv_status::timeout)
		{
			return ETIMEDOUT;
		}
		return 0;
	}

	int condition_signal( condition_t* cond )
	{
		cond->pCondVar->notify_one();
		return 0;
	}

	int condition_broadcast( condition_t *cond )
	{
		cond->pCondVar->notify_all();
		return 0;
	}

	int condition_destroy( condition_t *cond )
	{
		if (cond->pMutex)
		{
			delete cond->pMutex;
		}
		
		if (cond->pCondVar)
		{
			delete cond->pCondVar;
		}
		return 0;
	}

}
}