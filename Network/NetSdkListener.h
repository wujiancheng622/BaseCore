#ifndef NETSDKLISTENER_H
#define NETSDKLISTENER_H
#include "CrossPlatform.h"

class DLL_CLASS NetSdkListener
{

public:
	NetSdkListener() {};
	virtual ~NetSdkListener() {};


	///////////////////////
	//UDP
	
	/** UDP数据上报回调函数 
	 * @param[in] pBuffer：数据内容
	 * @param[in] len:数据长度
	 * @param[in] remoteAddr：发送方的ip地址
	 * @param[in] remotePort：发送方的端口地址
	 * return int :
	 */
	virtual int OnData( const char * pBuffer, int len, const char* remoteAddr, int remotePort ){ return 0; }

	//////////////////////



	///////////////////////
	//TCP客户端

	/** TCP 客户端数据上报回调函数 
	 * @param[in] pBuffer：数据
	 * @param[in] len：数据长度
	 * @param[in] remoteAddr：发送方的ip地址
	 * @param[in] remotePort：发送方的端口地址
	 * return int :
	 */
	//virtual int OnData( const char * pBuffer, int len, const char* remoteAddr, int remotePort){ return 0; }

	/** TCP客户端连接被中断回调函数 
	 * @param[out] error：中断错误码
	 * @param[out] serverAddr：连接的服务器ip地址
	 * @param[out] serverListenPort：服务器监听端口
	 * return void
	 */
	virtual void OnClose(int error,const char* serverAddr, int serverListenPort){}


	/** TCP客户端连接上服务端回调函数  TCP客户端类可以重新实现该接口
	 * @param[in] serverAddr：服务端的ip地址
	 * @param[in] serverListenPort：服务端的监听端口
	 * return void
	 */
	virtual void OnConnect( const char * serverAddr, int serverListenPort){}

	///////////////////////





	///////////////////////
	//TCP服务端


	/** TCP 服务端数据上报回调函数 
	 * @param[in] pBuffer：数据
	 * @param[in] len：数据长度
	 * @param[in] hSocket：由哪个连接上报上来的数据，如果当前类是服务器类则可以通过该参数判断是哪个客户端发送过来的
	 * @param[in] listenPort：由监听端口的服务端上报上来的
	 * return int :
	 */
	virtual int OnData( const char * pBuffer, int len, int hSocket,int listenPort){ return 0; }


	/** TCP服务端连接被中断回调函数 
	 * @param[in] hSocket:用来指示哪个连接被中断,如果当前类是服务端hSocket用来指示哪个客户端连接中断
	 * @param[out] error：中断错误码
	 * @param[out] listenPort: 如果是服务端，则返回哪个监听端口
	 * return void
	 */
	virtual void OnClose( int hSocket, int error ,int listenPort){}


	/** TCP服务端接收新连接回调函数   TCP服务端类可以重新实现该接口
	 * @param[out] newClient:新连接的句柄
	 * @param[out] remoteAddr：新连接ip地址
	 * @param[out] remotePort：新连接的端口号
	 * @param[out] listenPort：从哪个监听端口上来的
	 * return bool: 返回真表示接收该连接，返回假表示拒绝该连接也就是断开该连接
	 */
	virtual bool OnAccept( int newClient, const char * remoteAddr, int remotePort,int listenPort){ return true; }

	///////////////////////


};

#endif//NETSDKLISTENER_H

