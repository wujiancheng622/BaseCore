#include <iostream>
#include <cstdio>
#include "Log.h"


using namespace BaseCore::Log;

using namespace std;

int main()
{
	//CREATE_LOG("ceshi.log",LogBaseCore::ChainedLogLevel::DEBUG_LEVEL);


	//while(true)
	{
		
		LOG_ERROR_EX("model","test 3");
	}

	LOG_WARN("test 4444");
	LOG_DEBUG("test 333");
	LOG_INFO("test 33");
	printf("\n in main \n");
	return 0;
}
