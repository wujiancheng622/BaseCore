#include "NetSdkListener.h"

namespace BaseCore
{
	
namespace Net
{




class TcpServer_Helper; 
class Server;


/*  服务端基础库
	使用方法：
	1：使用者需定义一个类该类派生自NetSdkListener，并将该类指针传递给TcpServer的构造函数
	2：调用Start函数启动服务
	3: 调用Stop函数停止服务

*/
class TcpServer 
{
	friend class  Server;
public:
	TcpServer(NetSdkListener *pListener);
	virtual ~TcpServer(void);



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
		param :hHandle 发送给哪个客户端，如果hHandle为0则表示发送给最近的一个客户端
		param :bAsync true表示使用异步发送,false表示同步发送
		return :同步发送发送成功则返回发送的字节数，异步发送成功返回0， 同步和异步发送失败时都返回-1
	*/
	int  SendData(const char *pBuffer,int len,int hHandle=0,bool bAsync=false);


	/*
		breif :停止服务
		return :void
	*/
	void Stop();

	/*
		breif :设置在接受和发送TCP流时的组包模式，根据包头和包尾来组成一个完整数据包，如果不设置则不进行组包，
		注意这个函数必须在Start函数之前调用否则调用无效
		param :pHeader 包头内容
		param :headerLen 包头长度
		param :pTrailer 包尾内容
		param :trailerLen 包尾长度
		return :设置成功返回0，否则返回-1
	*/
	int SetPackageHeaderTrailer(const char *pHeader,int headerLen,const char *pTrailer,int trailerLen);



private:
	TcpServer_Helper *m_pDataHelper;
	NetSdkListener *m_pNetSdkListener;
};


}

}
 
