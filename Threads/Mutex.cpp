#include <iostream>
#include <boost/thread.hpp>
#include <boost/thread/lock_factories.hpp>
#include "./Mutex.h"



namespace BaseCore
{


	namespace Threads
	{

		MutexGuard::~MutexGuard()
		{
			if (m_pMutex)
			{
				m_pMutex->unlock();
			}


		}

		MutexGuard::MutexGuard(mutex *pMutex)
		{
			//std::cout<<"MutexGuard::MutexGuard pMutex"<<pMutex<<std::endl;
			if (pMutex)
			{
				m_pMutex=pMutex;
				m_pMutex->lock();
			}

		}




		Mutex::Mutex()
		{

			m_pMutex=new mutex;
			//std::cout<<"Mutex::Mutex  m_pMutex"<<m_pMutex<<std::endl;
		}

		Mutex::Mutex( const Mutex& other )
		{

		}


		Mutex::~Mutex()
		{
			//std::cout<<"Mutex::~Mutex"<<std::endl;
			if (m_pMutex)
			{
				delete m_pMutex;
				m_pMutex=NULL;
			}
		}

		mutex * Mutex::operator()()
		{
			//std::cout<<"Mutex::operator  m_pMutex"<<m_pMutex<<std::endl;
			return m_pMutex;
		}

		Mutex & Mutex::operator=( const Mutex &other )
		{
			return *this;
		}

		void Mutex::Lock()
		{
			m_pMutex->lock();
		}

		void Mutex::UnLock()
		{
			m_pMutex->unlock();
		}





	}
}
