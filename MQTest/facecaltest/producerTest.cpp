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



//struct CaptureData 
//{
//	string  scannerdevicecode;		
//	string  wristmac;			
//	string  time;				
//	string  actiontype;			
//	string  actiondescribe;		
//	bytes   actiondata1;			
//	bytes   actiondata2;			
//	bytes   actiondata3;			
//	bytes   actiondata;			
//	bytes   picture;		    
//	string  picturetype;			
//	string  actiondatatype;      
//}








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
	ActivemqProducer *m_pETSProducer=_CreateActivemqProducer("failover://tcp://192.168.1.76:61616?connection.sendTimeout=1000","QUEUE_FACECALL" );//192.168.3.136

	
	printf("\n test   \n ",REQ_HM_CollectorData);



	string  content;
	CaptureData captureData;
	captureData.set_scannerdevicecode("0001",strlen("0001"));
	captureData.set_wristmac("fff",strlen("fff"));			
	captureData.set_time("1234",strlen("1234"));				
	captureData.set_actiontype("type1",strlen("type1"));			
	captureData.set_actiondescribe("describe",strlen("describe"));			
	captureData.set_picturetype("net",strlen("net"));		
	captureData.set_actiondatatype("actiontype",strlen("actiontype"));		






	//设置证件照
	{
		// 打开文件  
		std::locale::global(std::locale(""));   
		std::ifstream textFile("./D.jpg");  
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
	}






	//设置抓拍照1
	{
		// 打开文件  
		std::locale::global(std::locale(""));   
		std::ifstream textFile("./C.jpg");  
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
		captureData.set_actiondata1(strPicData);
	}



	//设置抓拍照2
	{
		// 打开文件  
		std::locale::global(std::locale(""));   
		std::ifstream textFile("./B.jpg");  
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



	//设置抓拍照3
	{
		// 打开文件  
		std::locale::global(std::locale(""));   
		std::ifstream textFile("./A.jpg");  
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



    
	captureData.SerializeToString(&content);
	string strMessage=GetParamMessage(C_TMS_SERVER,REQ_FACE_REGONI,C_ETS_SERVER,content);
	int sendTime=0;
	while(true)
	{
		_SendBytesMessage(m_pETSProducer,strMessage);
 		 //_SendBytesMessage(m_pETSProducer,strMessage);
		
 		 _SendBytesMessage(m_pETSProducer,strMessage);
		_SendBytesMessage(m_pETSProducer,strMessage);
		_SendBytesMessage(m_pETSProducer,strMessage);
		_SendBytesMessage(m_pETSProducer,strMessage);
		_SendBytesMessage(m_pETSProducer,strMessage);
		_SendBytesMessage(m_pETSProducer,strMessage);
		_SendBytesMessage(m_pETSProducer,strMessage);
		_SendBytesMessage(m_pETSProducer,strMessage);
		_SendBytesMessage(m_pETSProducer,strMessage);
		
		usleep(2500*1000);
		sendTime+=10;
		printf("sendTime:%d \n",sendTime);
	}

	return 0;

}
