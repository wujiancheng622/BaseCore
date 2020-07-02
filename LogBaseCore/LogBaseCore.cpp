#include <iostream>  
#include <log4cplus/logger.h>  
#include <log4cplus/loggingmacros.h>  
#include <log4cplus/configurator.h>  
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/logger.h>  
#include <log4cplus/fileappender.h>  
#include <log4cplus/consoleappender.h>  
#include <log4cplus/layout.h>  
#include <boost/date_time/gregorian/gregorian.hpp>    
#include <boost/date_time/posix_time/posix_time.hpp> 
#include <string>
#include <map>

#define BOOST_DATE_TIME_SOURCE  


#if defined(WIN32)||defined(WIN64)||defined(WINCE)		//	Windows使用
#else	//	Linux使用
#include <sys/types.h>
#include <unistd.h>
#endif	

using namespace std;  
using namespace log4cplus;  
using namespace log4cplus::helpers;
using namespace std;  
#include "LogBaseCore.h"
#include "Mutex.h"


using namespace boost::posix_time;
using namespace boost::gregorian;
using namespace BaseCore::Threads;

namespace BaseCore
{

namespace Log
{

	class LogBaseCoreHelper
	{

	public:
		enum LogType
		{
			DEBUG =0,
			INFO  =1,
			WARN  =2,
			WRONG =3,
			FATAL =4,
		};

		LogBaseCoreHelper();
		~LogBaseCoreHelper();
		void Init(string fileName,int chainedLogLevel);
		void Uninit();
		void WriteLog(string data,LogType type,string model=".");

		void SetMaxLogDays(int days); 

		void SetLineLocation(bool open);

		bool GetLineLocation();

	private:
		string m_logFileName;//日志文件名
		Logger m_log;
		bool m_init;
		map<string,Logger> m_logMaps;
		Mutex m_mutex;
		int m_maxLogDays;
		bool m_openLineLocation;
		
	};

	LogBaseCoreHelper::LogBaseCoreHelper()
	{
		m_openLineLocation = true;
		m_maxLogDays=30;
		m_init=false;
		log4cplus::initialize();
	}

	LogBaseCoreHelper::~LogBaseCoreHelper()
	{
		m_logMaps.clear();
	}

	void LogBaseCoreHelper::Init( string fileName, int chainedLogLevel)
	{
		MutexGuard lock(m_mutex());
		helpers::LogLog::getLogLog()->setInternalDebugging(true);


		//#if defined(WIN32)||defined(WIN64)||defined(WINCE)		//	Windows使用
		//#else	//	Linux使用
		//char pidtmp[16]={0};
		//sprintf(pidtmp,"%d",getpid());
		//fileName=fileName+pidtmp;
		//#endif	//


		ptime now = second_clock::local_time();
		string now_str = to_iso_extended_string(now.date()) + " " + to_simple_string(now.time_of_day());
		//SharedAppenderPtr append(new DailyRollingFileAppender(fileName.c_str(), DAILY,true, m_maxLogDays));
		SharedAppenderPtr append(new FileAppender(fileName.c_str(), ios::app, true));
		char tmp[128]={0};
		sprintf(tmp,"%s  append instance",fileName.c_str());
		append->setName(LOG4CPLUS_TEXT(tmp));
		std::string pattern = "%D{%m/%d %H:%M:%S} th:%t %c %p - %m %n";
		std::auto_ptr<Layout> _layout(new PatternLayout(pattern));
		append->setLayout( _layout );
		Logger root = Logger::getRoot();
		root.addAppender(append);
		m_logMaps["."]=Logger::getInstance(LOG4CPLUS_TEXT("EXE"));

		string title;
		title = "============================================================================================================";
		LOG4CPLUS_INFO(m_logMaps["."], title.c_str());
		title = "Common log file";
		LOG4CPLUS_INFO(m_logMaps["."], title.c_str());
		title = "Created - Time : "+ now_str;
		LOG4CPLUS_INFO(m_logMaps["."], title.c_str());
		title = "Module :";
		LOG4CPLUS_INFO(m_logMaps["."], title.c_str());
		title = "============================================================================================================\n\n";
		LOG4CPLUS_INFO(m_logMaps["."], title.c_str());
		m_init=true;

		m_logMaps["."].setLogLevel(chainedLogLevel);

	}

	void LogBaseCoreHelper::Uninit()
	{
		MutexGuard lock(m_mutex());
		m_init=false;
	}

	void LogBaseCoreHelper::WriteLog( string data,LogType type,string model)
	{
		MutexGuard lock(m_mutex());
		if (m_init)
		{
			if (model.empty())
			{
				char tmp[128]={0};
				LogLog::getLogLog()->error("WriteLog model empty error");
				return ;
			}

			Logger log;
			if (m_logMaps.find(model)!=m_logMaps.end())
			{
				log=m_logMaps[model];
			}else{
				log=Logger::getInstance(LOG4CPLUS_TEXT(model.c_str()));
				m_logMaps[model]=log;
			}
			switch (type)
			{
			case  DEBUG:
				LOG4CPLUS_DEBUG(log,data.c_str());
				break;
			case INFO:
				LOG4CPLUS_INFO(log,data.c_str());
				break;
			case WRONG:
				LOG4CPLUS_ERROR(log,data.c_str());
				break;
			case WARN:
				LOG4CPLUS_WARN(log,data.c_str());
				break;
			case FATAL:
				LOG4CPLUS_FATAL(log, data.c_str());
				break;
			default:
				LogLog::getLogLog()->error("WriteLog type error");
			}
		}
	}

	void LogBaseCoreHelper::SetMaxLogDays( int days )
	{
		m_maxLogDays=days;
	}



	void LogBaseCoreHelper::SetLineLocation(bool open)
	{
		m_openLineLocation = open;
	}

	bool LogBaseCoreHelper::GetLineLocation()
	{
		return m_openLineLocation;
	}

	LogBaseCore::LogBaseCore()
	{
		m_pHelper=new LogBaseCoreHelper;
	}

	LogBaseCore::~LogBaseCore()
	{
		if (m_pHelper)
		{
			delete m_pHelper;
			m_pHelper=NULL;
		}
	}

	LogBaseCore* LogBaseCore::Init( std::string logFileName, ChainedLogLevel logLevel)
	{
		m_pHelper->Init(logFileName, logLevel);
		return this;
	}

	void LogBaseCore::WriteDebugLog( std::string data ,std::string model)
	{
		m_pHelper->WriteLog(data,LogBaseCoreHelper::DEBUG,model);
	}

	void LogBaseCore::WriteInfoLog( std::string data ,std::string model)
	{
		m_pHelper->WriteLog(data,LogBaseCoreHelper::INFO,model);
	}

	void LogBaseCore::WriteWarnLog( std::string data ,std::string model)
	{
		m_pHelper->WriteLog(data,LogBaseCoreHelper::WARN,model);
	}

	void LogBaseCore::WriteErrorLog( std::string data ,std::string model)
	{
		m_pHelper->WriteLog(data,LogBaseCoreHelper::WRONG,model);
	}



	void LogBaseCore::WriteFatalLog(std::string data, std::string model /*= "."*/)
	{
		m_pHelper->WriteLog(data, LogBaseCoreHelper::FATAL, model);
	}

	void LogBaseCore::SetMaxLogDays(int days)
	{
		m_pHelper->SetMaxLogDays(days);
	}


	void LogBaseCore::SetLineLocation(bool open)
	{
		m_pHelper->SetLineLocation(open);
	}

	bool LogBaseCore::GetLineLocation()
	{
		return m_pHelper->GetLineLocation();
	}

	LogBaseCoreWrap::~LogBaseCoreWrap()
	{

	}

	LogBaseCoreWrap::LogBaseCoreWrap()
	{
		m_pLog=NULL;
	}

	void LogBaseCoreWrap::SetLogInstancePrt( LogBaseCore *pLog )
	{
		m_pLog=pLog;
	}

	LogBaseCore * LogBaseCoreWrap::GetLogInstancePrt()
	{
		return m_pLog;
	}

}

}