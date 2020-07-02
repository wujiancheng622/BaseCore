#ifndef LOG_H_
#define LOG_H_

#include <string.h>
#include "LogBaseCore.h"

using namespace BaseCore::Log;

#define  LOG_BUFF_SIZE 1024

#define  CREATE_LOG(xxx,yyy)  	 (LogBaseCore::Instance()->Init(xxx,yyy))
#define  DESTROY_LOG()		 (LogBaseCore::Release())

#define  DLL_CREATE_LOG(xxx)  	 (LogBaseCoreWrap::Instance()->SetLogInstancePrt(xxx)) 
#define  DLL_DEATROY_LOG()		 (LogBaseCoreWrap::Release())

#define  SETMAXLOGDAYS(xxx)  	 (LogBaseCore::Instance()->SetMaxLogDays(xxx))
#define  SETLINELOCATION(xxx)  	 (LogBaseCore::Instance()->SetLineLocation(xxx))

/*
使用方法：

#include <iostream>
#include <cstdio>
#include "Log.h"
using namespace BaseCore::Log;
using namespace std;
int main()
{
SETMAXLOGDAYS(10);   //设置日志最长记录时间，现在日志库是每天生成一个日志文件，不设置默认情况下是保存30天的日志，该语句必须在CREATE_LOG之前调用
LogBaseCore *pLog=CREATE_LOG("logtest.log");   //创建日志文件
LOG_WARN("test 1");   //记录的日志数据在根路径下
LOG_WARN_EX("Gate","test 2");   //记录的日志数据在Gate子路径下
LOG_DEBUG("test 3");
LOG_DEBUG_EX("BPX","test 4");
LOG_INFO("test 5");
LOG_INFO_EX("BPX","test 6");
LOG_ERROR("test 7");
LOG_ERROR_EX("Gate","test 8");
return 0;
}

生成的日志文件:
月/日 时/分/秒 线程id		文件名:行号   日志路径 日志等级 - 打印数据
05/06 07:19:28 th:2728 [LogBaseCore.cpp:128] . WARN - test 1 
05/06 07:19:28 th:2728 [LogBaseCore.cpp:128] Gate WARN - test 2 
05/06 07:19:28 th:2728 [LogBaseCore.cpp:125] . ERROR - test 3 
05/06 07:19:28 th:2728 [LogBaseCore.cpp:125] BPX ERROR - test 4 
05/06 07:19:28 th:2728 [LogBaseCore.cpp:122] . INFO - test 5 
05/06 07:19:28 th:2728 [LogBaseCore.cpp:122] BPX INFO - test 6 
05/06 07:19:28 th:2728 [LogBaseCore.cpp:125] . ERROR - test 7 
05/06 07:19:28 th:2728 [LogBaseCore.cpp:125] Gate ERROR - test 8 



如果是加载的动态库需要使用日志库
该动态库可以重新创建一个日志文件也可以和主程序共用一个日志文件
如果是和主程序公用一个日志文件，使用方式如下：
LogBaseCore *pLog;
DLL_CREATE_LOG(pLog);//pLog参数就是主程序中CREATE_LOG语句的返回日志库指针
DLL_LOG_DEBUG_EX("Gate","GateManger::Init");注意这里使用的宏都是以DLL为前缀


如果该动态库自己使用一个单独的日志库，则使用方法和主程序中使用日志库的方式一样，使用凡是如下
LogBaseCore *pLog=CREATE_LOG("logtest.log");   
LOG_WARN("test 1");   
....


*/

#define LOGDOBEGIN  \
	do{																		\
	if (!LogBaseCore::IsCreated()) break;\
	char message[LOG_BUFF_SIZE] = {0};								\

#define  LOGDOXX \
	message[LOG_BUFF_SIZE-1] = '\0';								\
	char szTmp[256] = { 0 };									\
	if(LogBaseCore::Instance()->GetLineLocation()) \
	{\
		sprintf(szTmp, "[%s %s:%d] ", __filename__(__FILE__), __FUNCTION__, __LINE__);	\
	}\
	char *szPtr = strcat(szTmp, message);	\
	memset(message, 0, LOG_BUFF_SIZE);	\
	strcpy(message, szPtr);		\

#define  DLLLOGDOXX \
	message[LOG_BUFF_SIZE-1] = '\0';								\
	char szTmp[256] = { 0 };									\
	if(LogBaseCoreWrap::Instance()->GetLogInstancePrt()->GetLineLocation()) \
	{\
		sprintf(szTmp, "[%s %s:%d] ", __filename__(__FILE__), __FUNCTION__, __LINE__);	\
	}\
	char *szPtr = strcat(szTmp, message);	\
	memset(message, 0, LOG_BUFF_SIZE);	\
	strcpy(message, szPtr);		\

#define DLLLOGDEBUG \
	DLLLOGDOXX \
	LogBaseCoreWrap::Instance()->GetLogInstancePrt()->WriteDebugLog(message);           \
	if (LogBaseCoreWrap::Instance()->GetLogInstancePrt()->GetLineLocation()) \
	{\
		printf("\n%s:%s:%d DEBUG %s\n", __filename__(__FILE__), __FUNCTION__, __LINE__, message);		\
	}\
	else \
	{\
		printf("\nDEBUG %s\n", message);		\
	}\
	} while (0); \

#define  DLLLOGFATAL \
	DLLLOGDOXX \
	LogBaseCoreWrap::Instance()->GetLogInstancePrt()->WriteFatalLog(message);           \
	if (LogBaseCoreWrap::Instance()->GetLogInstancePrt()->GetLineLocation()) \
	{\
		printf("\n%s:%s:%d FATAL %s\n", __filename__(__FILE__), __FUNCTION__, __LINE__, message);		\
	} \
	else \
	{\
		printf("\FATAL %s\n", message);		\
	}\
	}while (0); \

#define  DLLLOGWARN \
	DLLLOGDOXX \
	LogBaseCoreWrap::Instance()->GetLogInstancePrt()->WriteWarnLog(message);           \
	if (LogBaseCoreWrap::Instance()->GetLogInstancePrt()->GetLineLocation()) \
	{\
		printf("\n%s:%s:%d WARN %s\n", __filename__(__FILE__), __FUNCTION__, __LINE__, message);		\
	} \
	else \
	{\
		printf("\WARN %s\n", message);		\
	}\
	}while (0); \

#define  DLLLOGINFO \
	DLLLOGDOXX \
	LogBaseCoreWrap::Instance()->GetLogInstancePrt()->WriteInfoLog(message);           \
	if (LogBaseCoreWrap::Instance()->GetLogInstancePrt()->GetLineLocation()) \
	{\
		printf("\n%s:%s:%d INFO %s\n", __filename__(__FILE__), __FUNCTION__, __LINE__, message);		\
	} \
	else \
	{\
		printf("\INFO %s\n", message);		\
	}\
	}while (0); \

#define  DLLLOGERROR \
	DLLLOGDOXX \
	LogBaseCoreWrap::Instance()->GetLogInstancePrt()->WriteErrorLog(message);           \
	if (LogBaseCoreWrap::Instance()->GetLogInstancePrt()->GetLineLocation()) \
	{\
		printf("\n%s:%s:%d ERROR %s\n", __filename__(__FILE__), __FUNCTION__, __LINE__, message);		\
	} \
	else \
	{\
		printf("\ERROR %s\n", message);		\
	}\
	}while (0); \

#define  DLLLOGFATALEX(model) \
	DLLLOGDOXX \
	LogBaseCoreWrap::Instance()->GetLogInstancePrt()->WriteFatalLog(message, model);           \
	if (LogBaseCoreWrap::Instance()->GetLogInstancePrt()->GetLineLocation()) \
	{\
		printf("\n%s:%s:%d FATAL %s\n", __filename__(__FILE__), __FUNCTION__, __LINE__, message);		\
	} \
	else \
	{\
		printf("\FATAL %s\n", message);		\
	}\
	}while (0); \

#define  DLLLOGINFOEX(model) \
	DLLLOGDOXX \
	LogBaseCoreWrap::Instance()->GetLogInstancePrt()->WriteInfoLog(message, model);           \
	if (LogBaseCoreWrap::Instance()->GetLogInstancePrt()->GetLineLocation()) \
	{\
		printf("\n%s:%s:%d INFO %s\n", __filename__(__FILE__), __FUNCTION__, __LINE__, message);		\
	} \
	else \
	{\
		printf("\INFO %s\n", message);		\
	}\
	}while (0); \

#define  DLLLOGWARNEX(model) \
	DLLLOGDOXX \
	LogBaseCoreWrap::Instance()->GetLogInstancePrt()->WriteWarnLog(message, model);           \
	if (LogBaseCoreWrap::Instance()->GetLogInstancePrt()->GetLineLocation()) \
	{\
		printf("\n%s:%s:%d WARN %s\n", __filename__(__FILE__), __FUNCTION__, __LINE__, message);		\
	} \
	else \
	{\
		printf("\WARN %s\n", message);		\
	}\
	}while (0); \

#define  DLLLOGERROREX(model) \
	DLLLOGDOXX \
	LogBaseCoreWrap::Instance()->GetLogInstancePrt()->WriteErrorLog(message, model);           \
	if (LogBaseCoreWrap::Instance()->GetLogInstancePrt()->GetLineLocation()) \
	{\
		printf("\n%s:%s:%d ERROR %s\n", __filename__(__FILE__), __FUNCTION__, __LINE__, message);		\
	} \
	else \
	{\
		printf("\ERROR %s\n", message);		\
	}\
	}while (0); \

#define DLLLOGDEBUGEX(model) \
	DLLLOGDOXX \
	LogBaseCoreWrap::Instance()->GetLogInstancePrt()->WriteDebugLog(message,model);           \
	if (LogBaseCoreWrap::Instance()->GetLogInstancePrt()->GetLineLocation()) \
	{\
		printf("\n%s:%s:%d DEBUG %s\n", __filename__(__FILE__), __FUNCTION__, __LINE__, message);		\
	}\
	else \
	{\
		printf("\nDEBUG %s\n", message);		\
	}\
	} while (0); \

#define  DLL_LOGDOBEGIN \
	do{																		\
	if (!LogBaseCoreWrap::IsCreated()) break;\
	char message[LOG_BUFF_SIZE] = {0};								\

#define LOGDEBUG \
	LOGDOXX \
	LogBaseCore::Instance()->WriteDebugLog(message);           \
	if(LogBaseCore::Instance()->GetLineLocation()) \
	{\
		printf("\n%s:%s:%d DEBUG %s\n", __filename__(__FILE__), __FUNCTION__, __LINE__, message);		\
	}else \
	{\
		printf("\nDEBUG %s\n", message);		\
	}\
	} while (0) ;\
	
#define LOGFATAL \
	LOGDOXX \
	LogBaseCore::Instance()->WriteFatalLog(message);           \
	if(LogBaseCore::Instance()->GetLineLocation()) \
	{\
		printf("\n%s:%s:%d FATAL %s\n", __filename__(__FILE__), __FUNCTION__, __LINE__, message);		\
	}else \
	{\
		printf("\FATAL %s\n", message);		\
	}\
	}while(0); \

#define LOGINFO \
	LOGDOXX \
	LogBaseCore::Instance()->WriteInfoLog(message);           \
	if(LogBaseCore::Instance()->GetLineLocation()) \
	{\
		printf("\n%s:%s:%d INFO %s\n", __filename__(__FILE__), __FUNCTION__, __LINE__, message);		\
	}else \
	{\
		printf("\INFO %s\n", message);		\
	}\
	}while(0); \

#define LOGWARN \
	LOGDOXX \
	LogBaseCore::Instance()->WriteWarnLog(message);           \
	if(LogBaseCore::Instance()->GetLineLocation()) \
	{\
		printf("\n%s:%s:%d WARN %s\n", __filename__(__FILE__), __FUNCTION__, __LINE__, message);		\
	}else \
	{\
		printf("\WARN %s\n", message);		\
	}\
	}while(0); \

#define LOGERROR \
	LOGDOXX \
	LogBaseCore::Instance()->WriteErrorLog(message);           \
	if(LogBaseCore::Instance()->GetLineLocation()) \
	{\
		printf("\n%s:%s:%d ERROR %s\n", __filename__(__FILE__), __FUNCTION__, __LINE__, message);		\
	}else \
	{\
		printf("\ERROR %s\n", message);		\
	}\
	}while(0); \

#define LOGFATALEX(model) \
	LOGDOXX \
	LogBaseCore::Instance()->WriteFatalLog(message,model);           \
	if(LogBaseCore::Instance()->GetLineLocation()) \
	{\
		printf("\n%s:%s:%d FATAL %s\n", __filename__(__FILE__), __FUNCTION__, __LINE__, message);		\
	}else \
	{\
		printf("\FATAL %s\n", message);		\
	}\
	}while(0); \

#define LOGWARNEX(model) \
	LOGDOXX \
	LogBaseCore::Instance()->WriteWarnLog(message,model);           \
	if(LogBaseCore::Instance()->GetLineLocation()) \
	{\
		printf("\n%s:%s:%d WARN %s\n", __filename__(__FILE__), __FUNCTION__, __LINE__, message);		\
	}else \
	{\
		printf("\WARN %s\n", message);		\
	}\
	}while(0); \

#define LOGINFOEX(model) \
	LOGDOXX \
	LogBaseCore::Instance()->WriteInfoLog(message,model);           \
	if(LogBaseCore::Instance()->GetLineLocation()) \
	{\
		printf("\n%s:%s:%d INFO %s\n", __filename__(__FILE__), __FUNCTION__, __LINE__, message);		\
	}else \
	{\
		printf("\INFO %s\n", message);		\
	}\
	}while(0); \

#define LOGERROREX(model) \
	LOGDOXX \
	LogBaseCore::Instance()->WriteErrorLog(message,model);           \
	if(LogBaseCore::Instance()->GetLineLocation()) \
	{\
		printf("\n%s:%s:%d ERROR %s\n", __filename__(__FILE__), __FUNCTION__, __LINE__, message);		\
	}else \
	{\
		printf("\ERROR %s\n", message);		\
	}\
	}while(0); \

#define LOGDEBUGEX(model) \
	LOGDOXX \
	LogBaseCore::Instance()->WriteDebugLog(message,model);           \
	if(LogBaseCore::Instance()->GetLineLocation()) \
	{\
		printf("\n%s:%s:%d DEBUG %s\n", __filename__(__FILE__), __FUNCTION__, __LINE__, message);		\
	}else \
	{\
		printf("\nDEBUG %s\n", message);		\
	}\
	} while (0) ;\
	

#if defined(WIN32)||defined(WIN64)||defined(WINCE)		//	Windows使用
#define __filename__(x) strrchr(x,'\\')?strrchr(x,'\\')+1:x 
#define  LOG_DEBUG(format,...) 									\
	LOGDOBEGIN \
	sprintf_s(message, LOG_BUFF_SIZE, format, __VA_ARGS__);			\
	LOGDEBUG \

#define  LOG_DEBUG_EX(model,format,...) 									\
	LOGDOBEGIN \
	sprintf_s(message, LOG_BUFF_SIZE, format, __VA_ARGS__);			\
	LOGDEBUGEX(model) \

#define  DLL_LOG_DEBUG(format,...) 									\
	DLL_LOGDOBEGIN \
	sprintf_s(message, LOG_BUFF_SIZE, format, __VA_ARGS__);			\
	DLLLOGDEBUG \

#define  DLL_LOG_DEBUG_EX(model,format,...) 									\
	DLL_LOGDOBEGIN \
	sprintf_s(message, LOG_BUFF_SIZE, format, __VA_ARGS__);			\
	DLLLOGDEBUGEX(model) \

#define  LOG_FATAL(format,...) 									\
	LOGDOBEGIN \
	sprintf_s(message, LOG_BUFF_SIZE, format, __VA_ARGS__);			\
	LOGFATAL \

#define  LOG_FATAL_EX(model,format,...) 									\
	LOGDOBEGIN \
	sprintf_s(message, LOG_BUFF_SIZE, format, __VA_ARGS__);			\
	LOGFATALEX(model) \

#define  DLL_LOG_FATAL(format,...) 									\
	DLL_LOGDOBEGIN \
	sprintf_s(message, LOG_BUFF_SIZE, format, __VA_ARGS__);			\
	DLLLOGFATAL \

#define  DLL_LOG_FATAL_EX(model,format,...) 									\
	DLL_LOGDOBEGIN \
	sprintf_s(message, LOG_BUFF_SIZE, format, __VA_ARGS__);			\
	DLLLOGFATALEX(model) \

#define  LOG_INFO(format,...) 									\
	LOGDOBEGIN \
	sprintf_s(message, LOG_BUFF_SIZE, format, __VA_ARGS__);			\
	LOGINFO \

#define  LOG_INFO_EX(model,format,...) 									\
	LOGDOBEGIN \
	sprintf_s(message, LOG_BUFF_SIZE, format, __VA_ARGS__);			\
	LOGINFOEX(model) \

#define  DLL_LOG_INFO(format,...) 									\
	DLL_LOGDOBEGIN \
	sprintf_s(message, LOG_BUFF_SIZE, format, __VA_ARGS__);			\
	DLLLOGINFO \

#define  DLL_LOG_INFO_EX(model,format,...) 									\
	DLL_LOGDOBEGIN \
	sprintf_s(message, LOG_BUFF_SIZE, format, __VA_ARGS__);			\
	DLLLOGINFOEX(model) \

#define  LOG_WARN(format,...) 									\
	LOGDOBEGIN \
	sprintf_s(message, LOG_BUFF_SIZE, format, __VA_ARGS__);			\
	LOGWARN \

#define  LOG_WARN_EX(model,format,...) 									\
	LOGDOBEGIN \
	sprintf_s(message, LOG_BUFF_SIZE, format, __VA_ARGS__);			\
	LOGWARNEX(model) \

#define  DLL_LOG_WARN(format,...) 									\
	DLL_LOGDOBEGIN \
	sprintf_s(message, LOG_BUFF_SIZE, format, __VA_ARGS__);			\
	DLLLOGWARN \

#define  DLL_LOG_WARN_EX(model,format,...) 									\
	DLL_LOGDOBEGIN \
	sprintf_s(message, LOG_BUFF_SIZE, format, __VA_ARGS__);			\
	DLLLOGWARNEX(model) \

#define  LOG_ERROR(format,...) 									\
	LOGDOBEGIN \
	sprintf_s(message, LOG_BUFF_SIZE, format, __VA_ARGS__);			\
	LOGERROR \

#define  LOG_ERROR_EX(model,format,...) 									\
	LOGDOBEGIN \
	sprintf_s(message, LOG_BUFF_SIZE, format, __VA_ARGS__);			\
	LOGERROREX(model) \

#define  DLL_LOG_ERROR(format,...) 									\
	DLL_LOGDOBEGIN \
	sprintf_s(message, LOG_BUFF_SIZE, format, __VA_ARGS__);			\
	DLLLOGERROR \

#define  DLL_LOG_ERROR_EX(model,format,...) 									\
	DLL_LOGDOBEGIN \
	sprintf_s(message, LOG_BUFF_SIZE, format, __VA_ARGS__);			\
	DLLLOGERROREX(model) \

#else	//	Linux使用
#define __filename__(x) (strrchr(x,'/')?strrchr(x,'/')+1:x)
#define  LOG_DEBUG(format,args...) 									\
	LOGDOBEGIN \
	snprintf(message, LOG_BUFF_SIZE, format, ##args);				\
	LOGDEBUG \

#define  LOG_DEBUG_EX(model,format,args...) 									\
	LOGDOBEGIN \
	snprintf(message, LOG_BUFF_SIZE, format, ##args);				\
	LOGDEBUGEX(model) \

#define  DLL_LOG_DEBUG(format,args...) 									\
	DLL_LOGDOBEGIN \
	snprintf(message, LOG_BUFF_SIZE, format, ##args);				\
	DLLLOGDEBUG \

#define  DLL_LOG_DEBUG_EX(model,format,args...) 									\
	DLL_LOGDOBEGIN \
	snprintf(message, LOG_BUFF_SIZE, format, ##args);				\
	DLLLOGDEBUGEX(model) \

#define  LOG_FATAL(format,args...) 									\
	LOGDOBEGIN \
	snprintf(message, LOG_BUFF_SIZE, format, ##args);				\
	LOGFATAL \

#define  LOG_FATAL_EX(model,format,args...) 									\
	LOGDOBEGIN \
	snprintf(message, LOG_BUFF_SIZE, format, ##args);				\
	LOGFATALEX(model) \

#define  DLL_LOG_FATAL(format,args...) 									\
	DLL_LOGDOBEGIN \
	snprintf(message, LOG_BUFF_SIZE, format, ##args);				\
	DLLLOGFATAL \

#define  DLL_LOG_FATAL_EX(model,format,args...) 									\
	DLL_LOGDOBEGIN \
	snprintf(message, LOG_BUFF_SIZE, format, ##args);				\
	DLLLOGFATALEX(model) \

#define  LOG_INFO(format,args...) 									\
	LOGDOBEGIN \
	snprintf(message, LOG_BUFF_SIZE, format, ##args);				\
	LOGINFO \

#define  LOG_INFO_EX(model,format,args...) 									\
	LOGDOBEGIN \
	snprintf(message, LOG_BUFF_SIZE, format, ##args);				\
	LOGINFOEX(model) \

#define  DLL_LOG_INFO(format,args...) 									\
	DLL_LOGDOBEGIN \
	snprintf(message, LOG_BUFF_SIZE, format, ##args);				\
	DLLLOGINFO \

#define  DLL_LOG_INFO_EX(model,format,args...) 									\
	DLL_LOGDOBEGIN \
	snprintf(message, LOG_BUFF_SIZE, format, ##args);				\
	DLLLOGINFOEX(model) \

#define  LOG_WARN(format,args...) 									\
	LOGDOBEGIN \
	snprintf(message, LOG_BUFF_SIZE, format, ##args);				\
	LOGWARN \

#define  LOG_WARN_EX(model,format,args...) 									\
	LOGDOBEGIN \
	snprintf(message, LOG_BUFF_SIZE, format, ##args);				\
	LOGWARNEX(model) \

#define  DLL_LOG_WARN(format,args...) 									\
	DLL_LOGDOBEGIN \
	snprintf(message, LOG_BUFF_SIZE, format, ##args);				\
	DLLLOGWARN \

#define  DLL_LOG_WARN_EX(model,format,args...) 									\
	DLL_LOGDOBEGIN \
	snprintf(message, LOG_BUFF_SIZE, format, ##args);				\
	DLLLOGWARNEX(model) \

#define  LOG_ERROR(format,args...) 									\
	LOGDOBEGIN \
	snprintf(message, LOG_BUFF_SIZE, format, ##args);				\
	LOGERROR \

#define  LOG_ERROR_EX(model,format,args...) 									\
	LOGDOBEGIN \
	snprintf(message, LOG_BUFF_SIZE, format, ##args);				\
	LOGERROREX(model) \

#define  DLL_LOG_ERROR(format,args...) 									\
	DLL_LOGDOBEGIN \
	snprintf(message, LOG_BUFF_SIZE, format, ##args);				\
	DLLLOGERROR \

#define  DLL_LOG_ERROR_EX(model,format,args...) 									\
	DLL_LOGDOBEGIN \
	snprintf(message, LOG_BUFF_SIZE, format, ##args);				\
	DLLLOGERROREX(model) \

#endif	//LOG_H_

#endif




//需要控制的格式
//必须要有的参数：文件名，函数名，行号，模型名，时间,level
//可选项：线程id