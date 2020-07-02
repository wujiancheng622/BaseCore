#include <cstdio>
#include <unistd.h>
#include <string.h>
#include "TcpClientModel.h"


using namespace BaseCore::Net;


bool conntrue=false;

class ClientTest:public NetSdkListener
{
public:
	ClientTest()
	{
		m_pclit=new TcpClient(this);
	
	}
	~ClientTest()
	{
		
	}

	void Start(const char *ip,int port)
	{
		printf("ClientTest fdsf Start  start no ss\n");
		//m_pclit->SetPackageHeaderTrailer("TIANSHITONG_DATA_BEGIN(",strlen("TIANSHITONG_DATA_BEGIN("),")TIANSHITONG_DATA_END",strlen(")TIANSHITONG_DATA_END"));
		m_pclit->Start(ip,port, true,true);
	}
	
	void Stop()
	{
		m_pclit->Stop();
	}

	int OnData( const char * pBuffer, int len, int hSocket)
	{
		static int num=1;
		printf("OData num:%d   len:%d\n ",num++,len);
		return 0;
	}
	void OnClose( int hSocket, int error )
	{
		printf("OnClose  hSocket:%d",hSocket);
	}
	void OnConnect(const char * remoteAddr, int remotePort)
	{
		printf("OnConnect remoteAddr:%s  remotePort:%d \n ",remoteAddr,remotePort);
		conntrue=true;
	}
	
	int sendData()
	{	
		char data[20]={67};
		memset(data,65,20);
		return m_pclit->SendData(data,sizeof(data),true);
	}
	
private:
	TcpClient *m_pclit;
	
};


int main()
 {
	ClientTest ct;	
	ct.Start("192.168.3.173",6810);
	while(!conntrue)
	{
		sleep(3);    // 这种更好用 
	}

	static int num=0;
	for (int i=0;i<20000;++i)
	{
		sleep(1);    // 这种更好用 
		printf("num :%d  send ret:%d\n",++num,ct.sendData());
	}
	while(true)
	{
		sleep(500);
	}

	 return 0;
 }
