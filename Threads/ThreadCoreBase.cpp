#include <iostream>
#include <cstdio>
#include <set>
#include <boost/thread.hpp>
#include <boost/thread/lock_factories.hpp>
#include "./ThreadCoreBase.h"



namespace BaseCore
{

	namespace Threads
	{


		ThreadCoreBase::ThreadCoreBase()
		{
			m_pThread=NULL;
			m_bStart=false;
			m_bStop=false;


			//printf("\n ThreadCoreBase::ThreadCoreBase this:%p  \n",this);
		}

		ThreadCoreBase::~ThreadCoreBase()
		{
			//printf("\n in ~ThreadCoreBase \n");
			Stop();
			if (m_pThread)
			{
				delete m_pThread;
				m_pThread=NULL;
			}
			//printf("\n in ~ThreadCoreBase out \n");
		}


		void ThreadCoreBase::StartThread(ThreadCoreBase *pThis)
		{
			try
			{
				while(true)
				{
					//sleep(1);
					//this_thread::sleep(boost::posix_time::millisec(5));
					static std::set<long>  pthset;
					if (pThis->m_bStart)
					{
						//printf("\n StartThread   desc :%s \n",pThis->m_desc.c_str());
						pThis->Run();
						pThis->Sleep();
					}else{
						printf("\n exit thread desc :%s \n",pThis->m_desc.c_str());
						pThis->m_bStop=true;
						return;
					}
				}
			}
			catch (...)
			{
				return ;
			}
			return ;
		}

		void ThreadCoreBase::Start()
		{
			if (!m_bStart&&!m_pThread)
			{
				m_pThread=new thread(StartThread,this);
				m_bStart=true;
				m_bStop=false;
				printf("\n Start thread:( %s )  success\n",m_desc.c_str());
			}
		}

		void ThreadCoreBase::Stop()
		{
			printf("\nThreadCoreBase::Stop desc:%s \n",m_desc.c_str());
			if (m_bStart&&m_pThread)
			{
				m_bStart=false;
				for(int i=0; !m_bStop && i<100; ++i)
				{
#if defined(WIN32)||defined(WIN64)||defined(WINCE)	
					this_thread::sleep(boost::posix_time::millisec(50));
					//printf("\nThreadCoreBase::Stop wait desc:%s win\n",m_desc.c_str());
#else
					usleep(1000 *50);
					//printf("\nThreadCoreBase::Stop wait desc:%s lin\n",m_desc.c_str());
#endif
					//printf("\nThreadCoreBase::Stop wait desc:%s \n",m_desc.c_str());
				}
				m_pThread->join();
				//printf("\n ThreadCoreBase::Stop join success \n");
				delete m_pThread;
				m_pThread=NULL;
				printf("\n Stop thread:( %s ) success \n",m_desc.c_str());
			}
		}

		void ThreadCoreBase::Sleep()
		{


#if defined(WIN32)||defined(WIN64)||defined(WINCE)	
	this_thread::sleep(boost::posix_time::millisec(5));
#else
	usleep(1000 *5);
#endif


		}

		void ThreadCoreBase::Sleep( int millisec )
		{

#if defined(WIN32)||defined(WIN64)||defined(WINCE)	
			this_thread::sleep(boost::posix_time::millisec(millisec));
#else
			usleep(1000 *millisec);
#endif
		}


		bool ThreadCoreBase::Is_Started()
		{
			return m_bStart;
		}


		void ThreadCoreBase::SetDesc( string desc )
		{
			m_desc=desc;
		}





	}
}
