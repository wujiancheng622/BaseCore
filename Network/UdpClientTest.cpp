#include <cstdio>
#include <iostream>
#include "UdpClientModel.h"

#include <unistd.h>
#include <string.h>
#include <vector>

using namespace std;

using namespace BaseCore::Net;


class ClientTest:public NetSdkListener
{
public:
	ClientTest()
	{
		m_pClient=new UdpClient(this);
		m_pClient->Start("udp client Test");
	}
	~ClientTest()
	{

	}

	int OnData( const char * pBuffer, int len, const char* remoteAddr, int remotePort )
	{
		static int num=1;
		printf("server OData  num:%d   len:%d\n ",num++,len);
		return 0;
	}

	void sendData()
	{
		char buffer[2048]={0};
		memset(buffer,65,2048);
		int ret=m_pClient->SendData(buffer,2048,"192.168.3.173",5666,false);	
		printf("\n ret:%d \n",ret);
	}

	void sendData2()
	{
		char buffer[2048]={0};
		memset(buffer,65,2048);
		int ret=m_pClient->SendData(buffer,2048,"192.168.3.173",5667,false);	
		printf("\n ret:%d \n",ret);
	}


public:
	UdpClient *m_pClient;

};




int main()
{	
	ClientTest client;
	

	

	//while(true)
	for(int i=0;i<10;++i)
	{
	   sleep(1);
	   client.sendData();
	}
	
	client.m_pClient->Stop();

	client.m_pClient->Start("test");

	sleep(4);
	printf("\n test last \n");
	//for(int i=0;i<10;++i)
	while(true)
	{
		sleep(1);
		client.sendData2();
	}
	while(true)
	{
		sleep(5);
	}


	return 0;
}
