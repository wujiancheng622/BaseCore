#include <cstdio>
#include <iostream>
#include "TcpServerModel.h"
#include <unistd.h>
#include <string.h>
#include <vector>

using namespace std;

using namespace BaseCore::Net;


union U{
	float v;
	unsigned char c[4];
	int i;
}uu;


class ServerTest:public NetSdkListener
{
public:
	ServerTest()
	{
		m_pSer=new TcpServer(this);
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

	int OnData( const char * pBuffer, int len, int hSocket)
	{
		static int num=1;
		printf("server OData  num:%d   len:%d  vi size:%d \n",num++,len,vi.size());
		if (len==101)
		{
			printf("gongneng ma %02x \n",pBuffer[0]);
			printf("gongneng ma %02x \n",pBuffer[1]);
			printf("gongneng ma %02x \n",pBuffer[2]);
			
			for (int i=0;i<19;++i)
			{
				uu.c[3]=pBuffer[2+19*i+1];
				uu.c[2]=pBuffer[2+19*i+2];
				uu.c[1]=pBuffer[2+19*i+3];
				uu.c[0]=pBuffer[2+19*i+4]; 
				printf("data[%d] %x %x %x %x \n",i+1,pBuffer[2+19*i+1],pBuffer[2+19*i+2],pBuffer[2+19*i+3],pBuffer[2+19*i+4],uu.v);
			}
			printf("id:");
			for (int i=1;i<=20;++i)
			{
				printf("%0x",pBuffer[2+19*4+i]);
			}
			printf("\nCRC %02x %02x\n",pBuffer[99],pBuffer[100]);
		}


	}

	void Test()
	{
		m_pSer->CloseClient(vi[0]);
		vi.clear();
		printf("\n  run hr\n");
	}

	void OnClose( int hSocket, int error )
	{
		printf("server OnClose \n ");
	}
	void OnConnect( int hSocket, const char * remoteAddr, int remotePort)
	{
		printf("OnConnect \n ");
	}
	
	void OnAccept(int newClient, const char * remoteAddr, int remotePort)
	{
		vi.push_back(newClient);
		printf("OnAccept \n ");
	}
	
	void sendData()
	{
		char data[8]={0};
		data[0]=0x01;
		data[1]=0x03;
		data[2]=0x05;
		data[3]=0x01;
		data[4]=0x00;
		data[5]=0x10;
		data[6]=0x15;
		data[7]=0x0a;
		for(int i=0;i<vi.size();++i)
		{
			int ret=m_pSer->SendData(data,8,vi[i],true);	
			//printf("ret:%d \n",ret);
		}
		//printf("\n run sendData \n");
	}
	
private:
	TcpServer *m_pSer;
	vector<int>  vi;
	
};




class Test
{
public:
	Test(int i)
	{
		cout<<"Tests"<<" m"<<m<<endl;
		m=i;
	}
	~Test()
	{
		cout<<"~Test"<<" data"<<m<<endl;
	}
private:
	int m; 	
};




int main()
{	
	//uu.c[3]=0x31;
	//uu.c[2]=0x34;
	//uu.c[1]=0x34;
	//uu.c[0]=0x30; 
	//printf(" %.16f %x",uu.v,uu.i);
	//return 0;


	ServerTest bser;
	int ret=bser.Start("192.168.3.173",6810);
	cout<<"start ret "<<ret<<endl; 
	//if(ret!=0)
	//{
	//	ret=bser.Start("127.0.0.1",6808);
	//}
	//cout<<"start ret "<<ret<<endl; 
	//bser.Stop();
	//ret=bser.Start("192.168.17.2",6808);
	//cout<<"start ret "<<ret<<endl; 
	//if(ret!=0)
	//{
	//	ret=bser.Start("192.168.3.173",6808);
	//}
	//cout<<"start ret "<<ret<<endl; 
	//
	//sleep(10);
	//bser.Test();
	
	
	while(true)
	{
		bser.sendData();
		sleep(1);
		//sleep(500);
	}
	
	// //sleep(60);
	// bser.Stop();
	// bser.Start(9700);
	// while(true)
	// {
		// sleep(500);
	// }
	

	// // //sleep(15);

	// // for (int i=0;i<10;++i)
	// // {
		// // //printf("main\n ");
		// // sleep(2);  
		// // bser.sendData();
	// // }
	
	// bser.Stop();
	// sleep(15);
	// bser.Start(9655);
	// for (int i = 0; i<10; )
	// {
		// //printf("main\n ");
		// sleep(2);
		// //bser.sendData();
	// }

		
	// while(true)
	// {
		// sleep(5);
		// printf("client main\n");
	// }
	
	
	return 0;
}
