#include <iostream>
#include <cstdio>
#include "Log.h"
#include "ThreadCoreBase.h"


using namespace BaseCore::Log;

using namespace std;

int main()
{
	CREATE_LOG("ceshi.log");


	//while(true)
	{
		BaseCore::Threads::ThreadCoreBase::Sleep(100);
		LOG_ERROR_EX("model","test 3");
	}

	
	LOG_WARN("test 4444");
	LOG_DEBUG("test 333");
	LOG_INFO("test 33");

	//for (int i=0;i<1;++i)
	//{
	//	BaseCore::Threads::ThreadCoreBase::Sleep(100);
	//	LOG_ERROR("test fdf dfdsfdsfsdfdsfdsfdsfdsfdsfdfffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff3");
	//	LOG_ERROR_EX("model","testddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd 3");
	//}
	//


	//LOG_WARN_EX("Gate","test 4444");
	//LOG_DEBUG_EX("BPX","test 333");
	//LOG_INFO_EX("BPX","test 33");
	//LOG_ERROR_EX("Gate","test 3");
	//
	printf("\n in main \n");
	return 0;
}
