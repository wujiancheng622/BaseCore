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
		printf("ClientTest Start\n");
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

		//读数据命令
		char data[8]={0};
		data[0]=0x01;
		data[1]=0x03;
		data[2]=0x05;
		data[3]=0x01;
		data[4]=0x00;
		data[5]=0x10;
		data[6]=0x15;
		data[7]=0x0a;

		if (len==8)
		{
			if (!strncmp(data,pBuffer,8))//读数据命令匹配
			{
				


				char srcdata[]={0x01,0x03,0x60,0x3F,0x0C,0x50,0x00,0x43,0x61,0xCC,0xCD,0x3A,0xC1,0xF0,0x7C,0x3A,0xC1,0xF0,0x7C,0x3A,0xC1
							,0xF0,0x7C,0x3A,0xC1,0xF0,0x7C,0x00,0x00,0x00,0x00,0x3F,0x80,0x00,0x00,0x43,0x2E,0x99,0x9A,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
						,0x41,0xA0,0x00,0x00,0x42,0x24,0x66,0x66,0x43,0x89,0x26,0x66,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F
						,0x01,0x0F,0x10,0x1A,0x16,0x31,0x34,0x34,0x30,0x2D,0x30,0x30,0x32,0x38,0x2D,0x73,0x63,0x6C,0x77,0x2D,0x32,0x31,0x35,0x33,0x00,0x8E
						,0xC5};
				
				int len=sizeof(srcdata);
				printf("  recv read data cmd,and replay %d bytes back\n ",len);
				return m_pclit->SendData(srcdata,len,true);

			}
		}
		return 0;
	}
	void OnClose( int hSocket, int error )
	{
		printf("OnClose  hSocket:%d",hSocket);
		//int ret=m_pclit->Start("127.0.0.1",9655,true);
		//printf(" restart ret:%d",ret);
	}
	void OnConnect(const char * remoteAddr, int remotePort)
	{
		printf("OnConnect remoteAddr:%s  remotePort:%d \n ",remoteAddr,remotePort);
		conntrue=true;
	}
	
	int sendData()
	{	
		char data[8196]={67};
		memset(data,67,8196);
		return m_pclit->SendData(data,sizeof(data),true);
	}

	
private:
	TcpClient *m_pclit;
	
};



int main()
 {



	ClientTest ct;
	
	ct.Start("192.168.3.170",6810);

	while(!conntrue)
	{
		sleep(3);    // 这种更好用 
	}
	
	//
	static int num=0;
	for (int i=0;i<20000;++i)
	{
		//printf("client main \n ");
		sleep(1);    // 这种更好用 
		printf("num :%d  send ret:%d\n",++num,ct.sendData());
	}
	while(true)
	{
		sleep(500);
	}
	
	
	ct.Stop();
	sleep(10);
	ct.Start("192.168.1.179",9700);
	for (int i=0;i<1000;)
	{
		//printf("client main \n ");
		//sleep(1);    // 这种更好用 
		printf("num :%d  send ret:%d\n",++num,ct.sendData());
	}
	
	
	
	
	ct.Stop();
	sleep(15);    // 这种更好用 
	ct.Start("192.168.1.179", 9700);
	
//		printf("send ret:%d\n",ct.sendData());
//	return 0;
//

	for (int i=0;i<200;)
	{
		//printf("client main \n ");
		sleep(1);    // 这种更好用 
		printf("num :%d  send ret:%d\n",++num,ct.sendData());
	}

	while(true)
	{
		sleep(5);
		printf("client main\n");
	}
	


	 return 0;
 }
