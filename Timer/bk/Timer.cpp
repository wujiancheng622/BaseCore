#include <iostream>
#include <boost/date_time.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#define BOOST_ASIO_DISABLE_STD_CHRONO
#include <boost/asio.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/thread.hpp>
#include "Timer.h"
#include "Mutex.h"



namespace BaseCore
{

	using namespace Threads;


	namespace Clock
	{



		class TimerHelper
		{
		public:
			TimerHelper(Timer *pTimer,TimerListener *pListener)
			{
				//m_pIO=NULL;
				m_pIO=new boost::asio::io_service;
				m_pSteadyTimer=NULL;
				m_pListener=pListener;
				m_pTimer=pTimer;
				m_totalTimes=0;
				m_curTimes=0;
				m_bStart=false;
				m_pThread=NULL;
				m_bInTimeOutFunc=false;
				m_hHandle=0;
				m_bStopSucc=false;
			}
			~TimerHelper()
			{

				if (m_pThread)
				{
					m_pThread->interrupt();
					delete m_pThread;
					m_pThread=NULL;
				}

				if (m_pSteadyTimer)
				{
					m_pSteadyTimer->cancel();
					delete m_pSteadyTimer;
					m_pSteadyTimer=NULL;
				}

				if (m_pIO)
				{
					m_pIO->stop();
					delete m_pIO;
					m_pIO=NULL;
				}

			}


			void Start(int intervalMilSec=3000,int times=0);
			void Stop();


			int GetHandle();

			void SetHandle( int hHandle );


			void TimeOut(const boost::system::error_code& ec);
		public:
			boost::thread *m_pThread;		
			boost::asio::io_service *m_pIO;
			boost::asio::steady_timer *m_pSteadyTimer;

			Timer *m_pTimer;
			TimerListener *m_pListener;
			int m_intervalMilSec;
			int m_totalTimes;
			int m_curTimes;

			Mutex m_mutex;
			Mutex m_mutexForInTimeOutFunc;

			bool m_bInTimeOutFunc;

			bool m_bStart;//是否已经启动
			bool m_bStopSucc;

			int m_hHandle;
		};


		int TimerHelper::GetHandle()
		{
			return m_hHandle;
		}

		void TimerHelper::SetHandle( int hHandle )
		{
			m_hHandle=hHandle;
		}



		void TimerHelper::TimeOut( const boost::system::error_code& ec )
		{
			{
				MutexGuard mutexLock(m_mutex());
				{
					MutexGuard mutexLock(m_mutexForInTimeOutFunc());
					m_bInTimeOutFunc=true;
				}

				if (m_bStart)
				{
					int curTimesTmp=++m_curTimes;
					int curTotalTimesTmp=m_totalTimes;
					int intervalMilSecTmp=m_intervalMilSec;

					m_pListener->OnTimeOut(m_hHandle);

					if (curTimesTmp<curTotalTimesTmp||curTotalTimesTmp==0)
					{
						m_pSteadyTimer->expires_from_now(boost::chrono::milliseconds(intervalMilSecTmp));
						m_pSteadyTimer->async_wait(boost::bind(&TimerHelper::TimeOut, this,  boost::asio::placeholders::error));
					}else{

					}


				}
			}

			{
				MutexGuard mutexLock(m_mutexForInTimeOutFunc());
				m_bInTimeOutFunc=false;
			}
		}

		void StartThread(TimerHelper *pThis)
		{
			while(true)
			{
				if (pThis->m_bStart&&pThis->m_pIO&&!(pThis->m_pIO->stopped()))
				{
					pThis->m_pIO->poll();
				}else{
					pThis->m_bStopSucc=true;
					return ;
				}
				boost::this_thread::sleep(boost::posix_time::millisec(5));
			}
		}



		void TimerHelper::Start( int intervalMilSec/*=3000*/,int times/*=0*/ )
		{

			//std::cout<<"TimerHelper::Start"<<std::endl;
			//m_pIO=new boost::asio::io_service;
			m_pSteadyTimer=new boost::asio::steady_timer(*m_pIO);
			m_pIO->reset();
			boost::system::error_code errCode;
			m_intervalMilSec=intervalMilSec;
			m_totalTimes=times;
			m_curTimes=0;

			m_pSteadyTimer->expires_from_now(boost::chrono::milliseconds(intervalMilSec)); //设置过期时间长度
			m_pSteadyTimer->async_wait(boost::bind(&TimerHelper::TimeOut, this, boost::asio::placeholders::error));//异步等待
			m_bStart=true;
			m_bStopSucc=false;

			m_pThread=new boost::thread(StartThread,this);
			printf("\n Start thread:( timer handle:%d  )  success\n",m_hHandle);
		}

		void TimerHelper::Stop()
		{
			m_bStart=false;

			

			
			//m_pThread->interrupt();
			//m_pThread->join();
			

			while(!m_bStopSucc)
			{
				boost::this_thread::sleep(boost::posix_time::millisec(5));
			}
			m_pThread->join();
			printf("\n Stop thread:( timer handle:%d  )  success\n",m_hHandle);
			m_pIO->stop();

			delete m_pThread;
			m_pThread=NULL;

			m_pSteadyTimer->cancel();  // 取消所有handler


			delete m_pSteadyTimer;
			m_pSteadyTimer=NULL;


			//try
			//{
			//	delete m_pIO;
			//	m_pIO=NULL;
			//}
			//catch (...)
			//{
			//}

		}



		Timer::Timer(TimerListener *pListener)
		{
			m_pDataHelper=new TimerHelper(this,pListener);
		}



		void Timer::Start(int intervalMilSec,int times)
		{
			if (m_pDataHelper->m_bStart)
			{
				Stop();
			}

			//std::cout<<"Timer::Start"<<std::endl;

			bool bInTimeOutFunc=false;
			{
				MutexGuard mutexLock((m_pDataHelper->m_mutexForInTimeOutFunc)());
				bInTimeOutFunc=m_pDataHelper->m_bInTimeOutFunc;
			}

			if (bInTimeOutFunc)
			{
				//std::cout<<"Timer::Start 1"<<std::endl;
				m_pDataHelper->Start(intervalMilSec,times);
			}else{

				MutexGuard mutexLock((m_pDataHelper->m_mutex)());
				//std::cout<<"Timer::Start 2"<<std::endl;
				m_pDataHelper->Start(intervalMilSec,times);
			}


		}

		void Timer::Stop()
		{
			if (m_pDataHelper->m_bStart)
			{
				//std::cout<<"Timer::Stop"<<std::endl;

				bool bInTimeOutFunc=false;
				{
					MutexGuard mutexLock((m_pDataHelper->m_mutexForInTimeOutFunc)());
					bInTimeOutFunc=m_pDataHelper->m_bInTimeOutFunc;
				}

				if (bInTimeOutFunc)
				{
					m_pDataHelper->Stop();
				}else{
					MutexGuard mutexLock((m_pDataHelper->m_mutex)());
					m_pDataHelper->Stop();
				}
			}

		}

		std::string Timer::LocalTime()
		{
			return boost::posix_time::to_simple_string(boost::posix_time::microsec_clock::local_time());
		}



		Timer::~Timer()
		{
			delete m_pDataHelper;
			m_pDataHelper=NULL;
		}

		int Timer::GetHandle()
		{
			return m_pDataHelper->GetHandle();
		}

		void Timer::SetHandle( int hHandle )
		{
			m_pDataHelper->SetHandle(hHandle);
		}


	}
}



