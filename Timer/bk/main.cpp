#include <iostream>
#include <unistd.h>
#include "Timer.h"
#include <cstdio>
#include <iostream>
#include "TcpServerModel.h"
#include <string.h>
#include <vector>

using namespace std;

using namespace BaseCore::Net;

using namespace BaseCore::Clock;






class TimerTest:public TimerListener
{

public:
	TimerTest();
	~TimerTest();

	virtual void OnTimeOut(int h);
public:
	Timer m_timer;

};


TimerTest my;


TimerTest::TimerTest():m_timer(this)
{
	//	m_timer.Start(3000,5);
}

TimerTest::~TimerTest()
{

}

void TimerTest::OnTimeOut(int h)
{

	static int i=0;
	i++;
	cout<<"TimerTest  time out i:"<<i<<endl;
	return;
	//if (i==1)
	//{
	//	cout<<"TimerTest time out i==1"<<endl;
	//	m_timer.Start(3000,3);
	//}else if (i==4)
	//{
	//	cout<<"TimerTest time out i==4"<<endl;
	//	m_timer.Start(1000,5);
	//}else if (i==9)
	//{
	//	cout<<"TimerTest time out i==9"<<endl;
	//	m_timer.Start(500,10);
	//}
	////if (i==6)
	////{
	////	//m_timer.Stop();
	////	m_timer.Start(200,4);
	////}

}



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
		m_pSer->SetPackageHeaderTrailer("TIANSHITONG_DATA_BEGIN(",strlen("TIANSHITONG_DATA_BEGIN("),")TIANSHITONG_DATA_END",strlen(")TIANSHITONG_DATA_END"));
		return m_pSer->Start(ip, nPort);//192.168.1.178
	}

	void Stop()
	{
		m_pSer->Stop();
	}

	int OnData( const char * pBuffer, int len, int hSocket)
	{
		
		static int num=1;
		my.m_timer.Stop();

		printf("server OData  num:%d   len:%d\n ",num++,len);
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
		char data[2048]={67};
		memset(data,67,2048);
		for(int i=0;i<vi.size();++i)
		{
			m_pSer->SendData(data,sizeof(data),vi[i],true);	
		}
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
	using namespace BaseCore::Clock;

	// ServerTest bser;
	// int ret=bser.Start("127.0.0.1",6888);
	// cout<<"start ret "<<ret<<endl; 
	

	//my.m_timer.Start(5000,1);
	//sleep(7);	
	//cout<<"TimerTest time out i==1"<<endl;
	//my.m_timer.Start(3000,3);
	//sleep(10);	
	//cout<<"TimerTest time out i==4"<<endl;
	//my.m_timer.Start(1000,5);
	//sleep(7);	
	//cout<<"TimerTest time out i==9"<<endl;
	//my.m_timer.Start(500,10);
	//std::cout<<" next "<<endl;
	

	my.m_timer.Start(1000,3);//开启Leader广播
	sleep(5);
	my.m_timer.Start(200,10);//开启Leader广播
	sleep(5);
	std::cout<<" next "<<endl;
	my.m_timer.Start(1000,3);//开启Leader广播

	while(true)
	{

	}
	std::cout << "press ENTER to exit..." << std::endl;
	std::cin.sync();


	return 0;
}
