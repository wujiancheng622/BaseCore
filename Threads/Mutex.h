#ifndef MUTEX_H_
#define MUTEX_H_

#include "CrossPlatform.h"
namespace boost
{
	class mutex;
}


using namespace boost;

namespace BaseCore
{
	namespace Threads
	{


		/*********************************************************************************************************
		*	线程锁类
		*********************************************************************************************************/

		class DLL_CLASS Mutex
		{
		public:
			Mutex();
			~Mutex();

			/*
				breif :  加锁操作
				return : void
			*/
			void Lock();

			/*
				breif : 减锁操作
				return : void
			*/
			void UnLock();
			
			mutex * operator()();

		protected:
			Mutex & operator = (const Mutex &other);//赋值函数
			Mutex(const Mutex& other);

		private:
			mutex *m_pMutex;
		};



		/*
			MutexGuard类在构造函数中对锁进行加锁操作，在析构函数中对锁进行减锁操作
		*/
		class DLL_CLASS MutexGuard
		{
		public:
			MutexGuard(mutex *pMutex);
			~MutexGuard();
		private:
			mutex *m_pMutex;
		};

	}
}



#endif //MUTEX_H_