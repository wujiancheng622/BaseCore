#include <cstdio>
#include <unistd.h>
#include <string.h>
#include "TcpClientModel.h"
#include "TcpServerModel.h"

using namespace BaseCore::Net;

class ClientServerTest:public NetSdkListener
{
public:
	ClientServerTest()
	{
		m_pclit=new TcpClient(this);
		m_pSer=new TcpServer(this);
		m_pclit->Start("192.168.64.169",6808, true,true);
		m_pSer->Start("192.168.19.4", 6808);
	}
	
	int OnData( const char * pBuffer, int len, int hSocket)
	{
		printf("OData  len:%d\n ",len);
		m_pclit->SendData(pBuffer,len,true);
		return 0;
	}
	void OnClose( int hSocket, int error )
	{
		printf("OnClose  hSocket:%d",hSocket);
	}
	void OnConnect(const char * remoteAddr, int remotePort)
	{
		printf(" OnConnect remoteAddr:%s  remotePort:%d \n ",remoteAddr,remotePort);
	}
	
private:
	TcpClient *m_pclit;
	TcpServer *m_pSer;
	
};



int main()
 {

	ClientServerTest ct;
	


	while(true)
	{
		sleep(500);
	}

	 return 0;
 }
