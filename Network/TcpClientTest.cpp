//#include <cstdio>
//#include <unistd.h>
//#include <string.h>
//#include <iostream>
//#include <boost/asio.hpp>
//#include "TcpClientModel.h"
//using boost::asio::ip::tcp;
//using namespace std;
//
//
//using namespace BaseCore::Net;
//
//
//bool conntrue=false;
//
//class ClientTest:public NetSdkListener
//{
//public:
//	ClientTest()
//	{
//		m_pclit=new TcpClient(this);
//	
//	}
//	~ClientTest()
//	{
//		delete m_pclit;
//	}
//
//	void Start(const char *ip,int port)
//	{
//		printf("ClientTest Start  here \n");
//		m_pclit->SetPackageHeaderTrailer("GATE_DATA_BEGIN",strlen("GATE_DATA_BEGIN"),"GATE_DATA_END",strlen("GATE_DATA_END"));
//		printf("ClientTest Start\n");
//		int ret=m_pclit->Start(ip,port, false,true);
//		if (ret==-1)
//		{
//			printf("ClientTest Start 1\n");
//			m_pclit->Start(ip,port, true,true);
//		}
//	}
//	
//	void Stop()
//	{
//		m_pclit->Stop();
//
//	}
//
//	int OnData( const char * pBuffer, int len, int hSocket)
//	{
//		static int num=0;
//		num+=len;
//		printf("\n OData num:%d   len:%d \n",num,len);
//		
//		return 0;
//	}
//	void OnClose(int error )
//	{
//		printf("\n OnClose  error:%d \n",error);	}
//	void OnConnect(const char * remoteAddr, int remotePort)
//	{
//		printf("OnConnect remoteAddr:%s  remotePort:%d \n ",remoteAddr,remotePort);
//		conntrue=true;
//	}
//	
//	int sendData()
//	{	
//		const int size=15000000;
//		char *data=new char[size];
//		memset(data,'a',size);
//		printf("sendData   begin \n ");
//		int ret= m_pclit->SendData(data,size,false);
//		printf("sendData   ret:%d \n ",ret);
//	}
//
//	
//private:
//	TcpClient *m_pclit;
//	
//};
//
//
//
//int main()
// {
//
//	printf("test new    sdsd\n");
//
//	boost::asio::io_service io_service;
//	tcp::resolver resolver(io_service);
//	tcp::resolver::query query(boost::asio::ip::host_name(), "");
//	tcp::resolver::iterator iter = resolver.resolve(query);
//	tcp::resolver::iterator end; // End marker.
//	while (iter != end)
//	{
//		tcp::endpoint ep = *iter++;
//		std::cout << ep << std::endl;
//	}
//
//	printf("test new    end  \n");
//
//	ClientTest ct;
//	
//	ct.Start("192.168.3.189",6688);
//
//	while(!conntrue)
//	{
//		sleep(3);    // 这种更好用 
//	}
//	printf("client main 2\n ");
//	static int num=0;
//	for (int i=0;i<50;++i)
//	{
//		printf("client main \n ");
//		ct.sendData();
//		printf("num :%d  send \n",++num);
//		sleep(5);    // 这种更好用 
//	}
//	return 0;
// }


#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <stdlib.h>

using namespace std;

string getLocalIP(char *eth) 
{
	int inet_sock;
	struct ifreq ifr;
	char ip[32] = { NULL };
	inet_sock = socket(AF_INET, SOCK_DGRAM, 0);
	strcpy(ifr.ifr_name, eth);
	ioctl(inet_sock, SIOCGIFADDR, &ifr);
	strcpy(ip, inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
	return string(ip);
}


vector<pair<string,string> > GetAllLocalIP()
{
	vector< pair<string, string> > ipvec;
	int sockfd;
	struct ifconf ifconf;
	struct ifreq *ifreq;
	char buf[512];//缓冲区
				  //初始化ifconf
	ifconf.ifc_len = 512;
	ifconf.ifc_buf = buf;
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("socket");
		exit(1);
	}
	ioctl(sockfd, SIOCGIFCONF, &ifconf); //获取所有接口信息
	//接下来一个一个的获取IP地址
	ifreq = (struct ifreq*)ifconf.ifc_buf;
	printf("ifconf.ifc_len:%d\n", ifconf.ifc_len);
	printf("sizeof (struct ifreq):%d\n", sizeof(struct ifreq));

	for (int i = (ifconf.ifc_len / sizeof(struct ifreq)); i > 0; i--)
	{
		if (ifreq->ifr_flags == AF_INET) 
		{ //for ipv4
			printf("name =[%s]\n", ifreq->ifr_name);
			printf("local addr = [%s]\n", inet_ntoa(((struct sockaddr_in*)&(ifreq->ifr_addr))->sin_addr));
			ipvec.push_back(pair<string, string>(ifreq->ifr_name, inet_ntoa(((struct sockaddr_in*)&(ifreq->ifr_addr))->sin_addr)));
			ifreq++;
		}
	}
	return ipvec;
}



int main(int argc, char* argv[])
{
	std::string eth0=getLocalIP("eth0");
	std::string eth1 = getLocalIP("eth1");
	std::string eth2 = getLocalIP("eth2");
	printf(" eth0:%s  eth1:%s  eth2:%s  \n", eth0.c_str(), eth1.c_str(), eth2.c_str());
	vector<pair<string, string> >  ipvec=GetAllLocalIP();
	vector<pair<string, string> >::iterator iter = ipvec.begin();
	while (iter != ipvec.end())
	{
		printf(" new  :%s :%s  \n", iter->first.c_str(), iter->second.c_str());
		++iter;
	}


	getchar();//system("pause");//not used in linux 
	return 0;
}