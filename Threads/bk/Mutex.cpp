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
			if (m_pMutexEx)
			{
				m_pMutexEx->UnLock();
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
			m_pMutexEx=NULL;
		}

		MutexGuard::MutexGuard( Mutex *pMutex )
		{
			m_pMutex=NULL;
			//std::cout<<"MutexGuard::MutexGuard pMutex1 "<<(*pMutex)()<<std::endl;
			if ((*pMutex)())
			{
				m_pMutexEx=pMutex;
				pMutex->Lock();
			}
			
		}





		Mutex::Mutex()
		{
			
			m_pMutex=new mutex;
			//std::cout<<"Mutex::Mutex  m_pMutex"<<m_pMutex<<std::endl;
			m_bLocked=false;
		}

		Mutex::Mutex( const Mutex& other )
		{
			
		}

		bool Mutex::IsLocked()
		{
			//std::cout<<"IsLocked m_bLocked<<"<<m_bLocked<<std::endl;
			return m_bLocked; 
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
			m_bLocked=true;
			//std::cout<<"Lock m_bLocked "<<m_bLocked<<std::endl;
		}

		void Mutex::UnLock()
		{
			m_pMutex->unlock();
			m_bLocked=false;
			//std::cout<<"UnLock m_bLocked "<<m_bLocked<<std::endl;
		}





	}
}
