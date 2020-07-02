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
		*	�߳�����
		*********************************************************************************************************/

		class Mutex
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

			/**  �Ƿ��Ѿ�����
			 * return bool : �Ѿ����������棬���򷵻ؼ�
			 */
			bool IsLocked();
			
			mutex * operator()();

		protected:
			Mutex & operator = (const Mutex &other);//��ֵ����
			Mutex(const Mutex& other);

		private:
			mutex *m_pMutex;
			bool m_bLocked;
		};



		/*
			MutexGuard���ڹ��캯���ж������м��������������������ж������м�������
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