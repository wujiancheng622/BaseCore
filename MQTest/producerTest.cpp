#include <iostream>
#include <string>
#include <unistd.h>
#include <fstream>
#include "ActivemqParseMessage.h"
#include "ActivemqAPI.h"
#include "MqLog.h"
#include "ParamMessageBean.pb.h"
#include "DataType.pb.h"
#include "ModuleType.pb.h"
#include "DataType.pb.h"
#include "CaptureDataBean.pb.h"


using namespace  std;

using namespace cms;
using namespace com::arges::file::proto;





std::string GetParamMessage(int model,int type,int srcModel,std::string content,std::string brokerUrl="",std::string destUrl="",int code=1,std::string doman="1",std::string sessionId="1")
{
	ParamMessage paramMessage;
	paramMessage.set_model(model);
	paramMessage.set_type(type);
	paramMessage.set_srcmodule(srcModel);
	paramMessage.set_content(content);
	paramMessage.set_code(code);
	paramMessage.set_brokerurl(brokerUrl);
	paramMessage.set_desturl(destUrl);
	paramMessage.set_sessionid(sessionId);
	std::string message;
	paramMessage.SerializeToString(&message);
	return message;
}


int _ParseMessageFromMq(std::string& str)
{
	printf("_ParseMessageFromMq\n");
	return 0;
}



int main()
{

	int ret=hlog_init();
	if (ret!=RET_OK)
	{
		//打印输出提示初始化hlog库失败
		exit(0);
	}

	ret=_CreateMqLog();
	if (ret!=RET_OK)
	{
		//打印输出提示实例化log对象失败
		hlog_uninit();
		exit(0);
	}

	ret=_InitMq();
	if (ret!=RET_OK)
	{
		//打印输出提示初始化mq库失败
		hlog_uninit();
		exit(0);
	}

	//	初始化线程池
	InitThreadPoolByActivemq(200, 200, 10000);


	printf("run here\n");
	ActivemqProducer *m_pETSProducer=_CreateActivemqProducer("failover://tcp://192.168.3.173:61616?connection.sendTimeout=1000","QUEUE_FACECALL" );//192.168.3.136





	string  content;
	CaptureData captureData;
	captureData.set_scannerdevicecode("0001",strlen("0001"));
	captureData.set_wristmac("fff",strlen("fff"));			
	captureData.set_time("1234",strlen("1234"));				
	captureData.set_actiontype("type1",strlen("type1"));			
	captureData.set_actiondescribe("describe",strlen("describe"));			
	{
		// 打开文件  
		std::locale::global(std::locale(""));   
		std::ifstream textFile("./picA.jpg");  
		if(!textFile.is_open())  
		{  
			printf("\n empty\n");
			return 0;  
		}  
		// 计算文件大小  
		textFile.seekg(0, std::ios::end);  
		std::streampos len = textFile.tellg();  
		textFile.seekg(0, std::ios::beg);  
		std::string strPicData;  
		strPicData.reserve(len);   // 预先分配内存空间大小, 避免频繁分配内存  
		strPicData.assign(std::istreambuf_iterator<char>(textFile), std::istreambuf_iterator<char>());  
		captureData.set_picture(strPicData);
		captureData.set_actiondata1(strPicData);
	}
	{
		// 打开文件  
		std::locale::global(std::locale(""));   
		std::ifstream textFile("./picB.jpg");  
		if(!textFile.is_open())  
		{  
			return 0;  
		}  
		// 计算文件大小  
		textFile.seekg(0, std::ios::end);  
		std::streampos len = textFile.tellg();  
		textFile.seekg(0, std::ios::beg);  
		std::string strPicData;  
		strPicData.reserve(len);   // 预先分配内存空间大小, 避免频繁分配内存  
		strPicData.assign(std::istreambuf_iterator<char>(textFile), std::istreambuf_iterator<char>());  
		captureData.set_actiondata2(strPicData);
	}
	{
		// 打开文件  
		std::locale::global(std::locale(""));   
		std::ifstream textFile("./picC.jpg");  
		if(!textFile.is_open())  
		{  
			return 0;  
		}  
		// 计算文件大小  
		textFile.seekg(0, std::ios::end);  
		std::streampos len = textFile.tellg();  
		textFile.seekg(0, std::ios::beg);  
		std::string strPicData;  
		strPicData.reserve(len);   // 预先分配内存空间大小, 避免频繁分配内存  
		strPicData.assign(std::istreambuf_iterator<char>(textFile), std::istreambuf_iterator<char>());  
		captureData.set_actiondata3(strPicData);
	}

	captureData.set_actiontype("actiontype", strlen("actiontype"));
	captureData.SerializeToString(&content);




	string strMessage=GetParamMessage(C_FACECALL_SERVER,REQ_FACE_REGONI,C_ETS_SERVER,content);
	int sendTime=0;
	while(true)
	{
		_SendBytesMessage(m_pETSProducer,strMessage);
		//_SendBytesMessage(m_pETSProducer,strMessage);
		//_SendBytesMessage(m_pETSProducer,strMessage);
		//_SendBytesMessage(m_pETSProducer,strMessage);
		sleep(1);
		sendTime+=2;
		printf("sendTime:%d  new \n",sendTime);
	}

	
	printf("run end\n");
	while(true)
	{
		sleep(5);
	}
	
	return 0;

}
