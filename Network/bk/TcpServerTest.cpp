#include <cstdio>
#include <iostream>
#include "TcpServerModel.h"
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
		m_pSer=new TcpServer(this);
	}
	~ServerTest()
	{
		
	}


	int Start(char * ip,int nPort)
	{
		printf("\nStart fdsfdsf  no ff\n");
		//m_pSer->SetPackageHeaderTrailer("TIANSHITONG_DATA_BEGIN(",strlen("TIANSHITONG_DATA_BEGIN("),")TIANSHITONG_DATA_END",strlen(")TIANSHITONG_DATA_END"));
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
		return 0;
	}

	void Test()
	{
		m_pSer->CloseClient(vi[0]);
		vi.clear();
		printf("\n  run hr\n");
	}

	void OnClose( int hSocket, int error )
	{
		printf("server OnClose hSocket:%d \n ",hSocket);

		vector<int>::iterator it=vi.begin();  
		vector<int>::iterator itEnd=vi.end();  
		while(it!=itEnd)
		{

			if (*it==hSocket)
			{
				vi.erase(it);
				return;
			}
			++it;
		}
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
			printf("ret:%d\n",ret);
		}
	}
	
private:
	TcpServer *m_pSer;
	vector<int>  vi;
	
};

int main()
{	
	ServerTest bser;
	int ret=bser.Start("192.168.3.173",6810);
	cout<<"start ret "<<ret<<endl; 
	
	while(true)
	{
		bser.sendData();
		sleep(1);
	}
	
	return 0;
}
