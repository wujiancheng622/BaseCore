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

	/** ��ʼ����־�� 
	 * @param[in] logFileName:������־�ļ���
	 * @param[in] logLevel: ��־���˼���
	 * return LogBaseCore *: ����־���ָ��
	 */
	LogBaseCore* Init(std::string logFileName, ChainedLogLevel logLevel = DEBUG_LEVEL);

	/** ������־���������,Ĭ���������30��
	 * @param[in] days: ��־�ļ���������
	 * return void 
	 */
	void SetMaxLogDays(int days); 

	/*	�����Ƿ����־�����������λ 
	 * @param[in] open: �Ƿ���ļ�������λ
	 * return void
	*/
	void SetLineLocation(bool open);

	/*
		* �������� �����Ƿ��Ѿ���������λ
		* ����ֵ��bool : ��Ϊtrue������Ϊfalse
	*/
	bool GetLineLocation();


	/** дdebug ��־���� 
	 * @param[in] data����������
	 * @param[in] model����¼��ģ��·�� Ĭ�ϼ�¼��.·����
	 * return void
	 */
	void WriteDebugLog(std::string data,std::string model=".");

	/** дinfo ��־���� 
	 * @param[in] data����������
	 * @param[in] model����¼��ģ��·�� Ĭ�ϼ�¼��.·����
	 * return void
	 */
	void WriteInfoLog(std::string data,std::string model=".");

	/** дwarn ��־���� 
	 * @param[in] data����������
	 * @param[in] model����¼��ģ��·�� Ĭ�ϼ�¼��.·����
	 * return void
	 */
	void WriteWarnLog(std::string data,std::string model=".");

	/** дerror ��־���� 
	 * @param[in] data����������
	 * @param[in] model����¼��ģ��·�� Ĭ�ϼ�¼��.·����
	 * return void
	 */
	void WriteErrorLog(std::string data,std::string model=".");


	/** дfatal ��־����
	* @param[in] data����������
	* @param[in] model����¼��ģ��·�� Ĭ�ϼ�¼��.·����
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