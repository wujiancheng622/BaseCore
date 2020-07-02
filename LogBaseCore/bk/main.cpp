#include <iostream>
#include <log4cplus/logger.h>  
#include <log4cplus/loggingmacros.h>  
#include <log4cplus/configurator.h>  
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/logger.h>  
#include <log4cplus/fileappender.h>  
#include <log4cplus/consoleappender.h>  
#include <log4cplus/layout.h>  

using namespace std;  
using namespace log4cplus;  
using namespace log4cplus::helpers;


int main()
{
	printf("\n hello in main \n");
	log4cplus::initialize(); 
	PropertyConfigurator::doConfigure(LOG4CPLUS_STRING_TO_TSTRING("./log4cplus.cfg"));
	Logger::getInstance(LOG4CPLUS_STRING_TO_TSTRING("ALL_MSGS"));


	//for (int i=0;i<5;++i)
	{
		INFO_LOG_LEVEL(20000)
		usleep(5000);
		LOG4CPLUS_DEBUG(Logger::getInstance(LOG4CPLUS_STRING_TO_TSTRING("ALL_MSGS")), LOG4CPLUS_STRING_TO_TSTRING("msg"));	
		LOG4CPLUS_ERROR(Logger::getInstance(LOG4CPLUS_STRING_TO_TSTRING("ALL_MSGS")), LOG4CPLUS_STRING_TO_TSTRING("msg"));	
		LOG4CPLUS_WARN(Logger::getInstance(LOG4CPLUS_STRING_TO_TSTRING("ALL_MSGS")), LOG4CPLUS_STRING_TO_TSTRING("msg"));	
		LOG4CPLUS_INFO(Logger::getInstance(LOG4CPLUS_STRING_TO_TSTRING("ALL_MSGS")), LOG4CPLUS_STRING_TO_TSTRING("msg"));	
	}
	
	return 0;
}