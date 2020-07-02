#ifndef UDPSERVERMODEL_H_
#define UDPSERVERMODEL_H_

#include "CrossPlatform.h"
#include "NetSdkListener.h"

namespace BaseCore
{


namespace Net
{

class UdpServer_Helper;

class DLL_CLASS UdpServer
{
public:
	UdpServer(NetSdkListener *pListener);
	~UdpServer();


	/*
		breif :开启服务
		param :ip 服务端的ip地址
		param  :nPort 服务端的端口地址
		return :int 启动成功返回0，失败返回-1
	*/
	int Start(const char *ip,int nPort);



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


	/*
		breif :停止服务
		return :void
	*/
	void Stop();



private:
	UdpServer_Helper *m_pDataHelper;
	NetSdkListener *m_pNetSdkListener;
	friend class  AsioUdpServer;
};



}
}



#endif  //UDPSERVERMODEL_H_


