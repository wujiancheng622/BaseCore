#ifndef TCPCLIENTMODEL_H_
#define TCPCLIENTMODEL_H_


#include "CrossPlatform.h"
#include "NetSdkListener.h"





	
namespace BaseCore
{
	
namespace Net
{

/*  客户端基础库
	使用方法：
	1：使用者需定义一个类该类派生自NetSdkListener，并将该类指针传递给TcpServer的构造函数
	2：调用Start函数启动服务
	3: 调用Stop函数停止服务

*/



class TcpClient_Helper; 
class Client;
class DLL_CLASS TcpClient
{

	friend class  Client;
 public:
	 TcpClient(NetSdkListener *pListener);
	 virtual ~TcpClient(void);

	 /*
	 	breif : 启动链接服务
	 	param : ip 服务器所在的ip地址
	 	param : nPort 服务器使用的端口
	 	param : bConnectAsync 是否使用异步连接
		param : bAutoReconnect 与服务端断开连接后是否自动进行重连
		param : hHandle用来标识当前tcp client的句柄值，默认为0
	 	return : void
	 */
	 int  Start(const char* ip,int nPort,bool bConnectAsync=false,bool bAutoReconnect=true,int hHandle=0);

	 /** 获取当前tcp client的句柄
	  return : int :当前tcp client的句柄
	  */
	 int GetHandle();

	 /*
	 	breif :停止服务
	 	return :void
	 */
	 void Stop();


	 /*
	 	breif : 发送数据函数
	 	param : pBuffer 数据内容
	 	param : len 数据长度
	 	param : bSendAsync 是否异步传输
	 	return :如果异步传输成功则返回0，否则返回失败，如果同步传输成功则返回实际发送的字节数，否则返回-1
	 */
	 int  SendData(const char *pBuffer,int len,bool bSendAsync=false);


	 /*
		breif :设置在接受和发送TCP流时的组包模式，根据包头和包尾来组成一个完整的数据包，如果不设置则不进行组包，
		注意这个函数必须在Start函数之前调用否则调用无效
		param :pHeader 包头内容
		param :headerLen 包头长度
		param :pTrailer 包尾内容
		param :trailerLen 包尾长度
		return :设置成功返回0，否则返回-1
	*/
	int SetPackageHeaderTrailer(const char *pHeader,int headerLen,const char *pTrailer,int trailerLen);



	
 private:
	 TcpClient_Helper *m_pDataHelper;
	 NetSdkListener *m_pNetSdkListener;
 };
 
 
}

}



#endif  //TCPCLIENTMODEL_H_





