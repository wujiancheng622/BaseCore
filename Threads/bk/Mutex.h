#ifndef MUTEX_H_
#define MUTEX_H_


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

		class Mutex
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

			/**  是否已经被锁
			 * return bool : 已经被锁返回真，否则返回假
			 */
			bool IsLocked();
			
			mutex * operator()();

		protected:
			Mutex & operator = (const Mutex &other);//赋值函数
			Mutex(const Mutex& other);

		private:
			mutex *m_pMutex;
			bool m_bLocked;
		};



		/*
			MutexGuard类在构造函数中对锁进行加锁操作，在析构函数中对锁进行减锁操作
		*/
		class MutexGuard
		{
		public:
			MutexGuard(mutex *pMutex);
			MutexGuard(Mutex *pMutex);
			~MutexGuard();
		private:
			mutex *m_pMutex;
			Mutex *m_pMutexEx;
		};

	}
}



#endif //MUTEX_H_