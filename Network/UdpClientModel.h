#ifndef UDPCLIENTMODEL_H_
#define UDPCLIENTMODEL_H_ 

#include <string>
#include "CrossPlatform.h"
#include "NetSdkListener.h"


	
namespace BaseCore
{
	
namespace Net
{



class UdpClient_Helper; 
class AsioUdpClient;
class DLL_CLASS UdpClient
{
 public:
	 UdpClient(NetSdkListener *pListener);
	 virtual ~UdpClient(void);


	 /** 启动服务 
	  * @param[in]  desc:每个udp client内部会启动一个线程 desc用来表示这个线程的名称，主要用于调试时使用，可以不设置
	  * return void
	  */
	 void Start(std::string desc="");

	 /** 停止服务 
	  * return void
	  */
	 void Stop();

	/*
		breif :发送数据函数
		param :pBuffer 数据内容
		param :len 数据字节长度
		param :remoteAddr 接收方的IP
		param :remotePort 接收方的端口号
		param :bAsync 是否使用异步发送模式
		return :发送成功则返回发送的字节数，失败返回-1
	*/
	int  SendData(const char *pBuffer,int len, const char* remoteAddr, int remotePort,bool bAsync=false);

 private:
	 UdpClient_Helper *m_pDataHelper;
	 NetSdkListener *m_pNetSdkListener;
	 friend class  AsioUdpClient;
 };
 
 
}

}




#endif  //UDPCLIENTMODEL_H_