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
		*	�߳�����
		*********************************************************************************************************/

		class DLL_CLASS Mutex
		{
		public:
			Mutex();
			~Mutex();

			/*
				breif :  ��������
				return : void
			*/
			void Lock();

			/*
				breif : ��������
				return : void
			*/
			void UnLock();
			
			mutex * operator()();

		protected:
			Mutex & operator = (const Mutex &other);//��ֵ����
			Mutex(const Mutex& other);

		private:
			mutex *m_pMutex;
		};



		/*
			MutexGuard���ڹ��캯���ж������м��������������������ж������м�������
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