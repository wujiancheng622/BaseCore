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
	}
	~ClientTest()
	{

	}


	int OnData( const char * pBuffer, int len, const char* remoteAddr, int remotePort )
	{
		static int num=1;
		printf("server OData  num:%d   len:%d  remoteAddr:%s  remotePort:%d \n ",num++,len,remoteAddr,remotePort);
	}

	void sendData()
	{


		char buffer[2048]={0};
		memset(buffer,65,2048);
		int ret=m_pClient->SendData(buffer,2048,"192.168.3.173",5666,true);	
		printf("\n ret:%d \n",ret);
		
	}

private:
	UdpClient *m_pClient;

};




int main()
{	
	ClientTest client;
	while(true)
	{
	   sleep(1);
	   client.sendData();
	}

	while(true)
	{
		sleep(500);
	}

	return 0;
}
