#ifndef LOGBASECORE_H_
#define LOGBASECORE_H_ 


#include <string>
#include "CrossPlatform.h"
#include "Singleton.cpp"




using namespace BaseCore::Common;


namespace BaseCore
{

namespace Log
{


class LogBaseCoreHelper;

class DLL_CLASS LogBaseCore:public Singleton<LogBaseCore>
{
	friend class Singleton<LogBaseCore>;
public:
	~LogBaseCore();


	enum ChainedLogLevel
	{
		DEBUG_LEVEL = 10000,
		INFO_LEVEL	= 20000,
		WARN_LEVEL	= 30000,
		ERROR_LEVEL = 40000,
		FATAL_LEVEL = 50000
	};

	/** 初始化日志库 
	 * @param[in] logFileName:设置日志文件名
	 * @param[in] logLevel: 日志过滤级别
	 * return LogBaseCore *: 该日志库的指针
	 */
	LogBaseCore* Init(std::string logFileName, ChainedLogLevel logLevel = DEBUG_LEVEL);

	/** 设置日志最长保存天数,默认情况下是30天
	 * @param[in] days: 日志文件保存天数
	 * return void 
	 */
	void SetMaxLogDays(int days); 

	/*	设置是否打开日志具体的行数定位 
	 * @param[in] open: 是否打开文件行数定位
	 * return void
	*/
	void SetLineLocation(bool open);

	/*
		* 功能描述 返回是否已经打开行数定位
		* 返回值：bool : 打开为true，否则为false
	*/
	bool GetLineLocation();


	/** 写debug 日志数据 
	 * @param[in] data：数据内容
	 * @param[in] model：记录的模型路径 默认记录在.路径下
	 * return void
	 */
	void WriteDebugLog(std::string data,std::string model=".");

	/** 写info 日志数据 
	 * @param[in] data：数据内容
	 * @param[in] model：记录的模型路径 默认记录在.路径下
	 * return void
	 */
	void WriteInfoLog(std::string data,std::string model=".");

	/** 写warn 日志数据 
	 * @param[in] data：数据内容
	 * @param[in] model：记录的模型路径 默认记录在.路径下
	 * return void
	 */
	void WriteWarnLog(std::string data,std::string model=".");

	/** 写error 日志数据 
	 * @param[in] data：数据内容
	 * @param[in] model：记录的模型路径 默认记录在.路径下
	 * return void
	 */
	void WriteErrorLog(std::string data,std::string model=".");


	/** 写fatal 日志数据
	* @param[in] data：数据内容
	* @param[in] model：记录的模型路径 默认记录在.路径下
	* return void
	*/
	void WriteFatalLog(std::string data, std::string model = ".");
protected:
	LogBaseCore();

private:
	LogBaseCoreHelper *m_pHelper;

};




class DLL_CLASS LogBaseCoreWrap:public Singleton<LogBaseCoreWrap>
{
	friend class Singleton<LogBaseCoreWrap>;
public:
	~LogBaseCoreWrap();
	void SetLogInstancePrt(LogBaseCore *pLog);

	LogBaseCore *GetLogInstancePrt();
protected:
	LogBaseCoreWrap();
private:
	LogBaseCore *m_pLog;
};

}

}




#endif	//LOGBASECORE_H_