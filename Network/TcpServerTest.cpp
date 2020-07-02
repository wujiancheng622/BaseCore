#include <cstdio>
#include <iostream>
#include <string.h>
#include <vector>
#include "TcpServerModel.h"

using namespace std;

using namespace BaseCore::Net;


class ServerTest:public NetSdkListener
{
public:
	ServerTest()
	{
		m_pSer=new TcpServer(this);
		b=false;
	}


	int Start(char * ip,int nPort)
	{
		m_pSer->SetPackageHeaderTrailer("GATE_DATA_BEGIN",strlen("GATE_DATA_BEGIN"),"GATE_DATA_END",strlen("GATE_DATA_END"));
		return m_pSer->Start(ip, nPort);//192.168.1.178
	}


	int Stop()
	{
		m_pSer->Stop();
		return 0;
	}

	int OnData( const char * pBuffer, int len, int hSocket,int listenPort)
	{
		static int total=0;
		total+=len;
		printf("\n OnData len:%d  \n",len);
		return 0;
	}

	void OnClose( int hSocket, int error ,int listenPort)
	{
		printf("\n OnClose handle:%d \n",hSocket);
	}


	bool OnAccept(int newClient1, const char * remoteAddr, int remotePort,int listenPort)
	{

		printf("client ip:%s port:%d connected  listenPort£º:%d \n",remoteAddr,remotePort,listenPort);

		b=true;
		newClient=newClient1;
		return true;
	}


	int sendData()
	{	
		//if (!b)
		//{
		//	return 0;
		//}
		const int size=3000000;
		char *data=new char[size];
		memset(data,'a',size);
		printf("sendData   begin \n ");
		int ret= m_pSer->SendData(data,size,newClient,false);
		printf("sendData   ret:%d \n ",ret);
		while(ret==-1)
		{
			ret= m_pSer->SendData(data,size,newClient,false);
			//printf("sendData   ret:%d \n ",ret);
		}
	}



private:
	TcpServer *m_pSer;	
	bool b;
	int newClient;
};

int main()
{	
	ServerTest bser;
	int ret=bser.Start("192.168.3.173",6688);

	//printf("\n new sssssssss  ff \n");
	//sleep(5);
	//for(int i=0;i<5;++i)
	//{
	//	//printf("\n begin send \n");
	//	bser.sendData();
	//	//printf("\n end send \n");
	//	//sleep(5);
	//}
	sleep(10000);
	return 0;
}
