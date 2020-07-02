#include <cstdio>
#include <iostream>
#include "UdpServerModel.h"
#include <unistd.h>
#include <string.h>
#include <vector>

using namespace std;

using namespace BaseCore::Net;




class ServerTest:public NetSdkListener
{
public:
	ServerTest()
	{
		m_pSer=new UdpServer(this);
	}
	~ServerTest()
	{

	}

	int Start(char * ip,int nPort)
	{
		return m_pSer->Start(ip, nPort);//192.168.1.178
	}

	void Stop()
	{
		m_pSer->Stop();
	}

	int OnData( const char * pBuffer, int len, const char* remoteAddr, int remotePort )
	{
		printf("ondata len:%d  \n",len);

		m_pSer->SendData("Test",strlen("Test"),remoteAddr,remotePort,false);	

		return 0;
	}

	void sendData(int port)
	{
		m_pSer->SendData("Test",strlen("Test"),"192.168.3.173",port,false);	
		
	}

private:
	UdpServer *m_pSer;

};




int main()
{	
	ServerTest bser;
	int ret=bser.Start("192.168.3.173",5666);
	cout<<"start ret "<<ret<<endl; 

	for(int i=0;i<10;++i)
	{
		sleep(1);
	}
	printf(" Stop begin \n");
	bser.Stop();
	printf(" Stop End \n");


	sleep(5);

	ret=bser.Start("192.168.3.173",5667);

	cout<<"start ret 1"<<ret<<endl; 

	for(int i=0;i<10;++i)
	{
		sleep(1000);
	}
	printf(" Stop begin1 \n");
	bser.Stop();
	printf(" Stop End1 \n");


	while(true)
	{
		sleep(1);
	}
	return 0;
}
