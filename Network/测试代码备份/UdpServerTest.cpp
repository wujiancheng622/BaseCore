#include <cstdio>
#include <iostream>
#include "UdpServerModel.h"
// #include "GetLeaderAddressBean.pb.h"
// #include "ModuleType.pb.h"
// #include "DataType.pb.h"
// #include "ParamMessageBean.pb.h"

#include <unistd.h>
#include <string.h>
#include <vector>

using namespace std;

using namespace BaseCore::Net;


// using namespace com::arges::file::proto;

// std::string GetParamMessage(int model,int type,int srcModel,std::string content,std::string brokerUrl="",std::string destUrl="",int code=1,std::string doman="1",std::string sessionId="1")
// {
	// ParamMessage paramMessage;
	// paramMessage.set_model(model);
	// paramMessage.set_type(type);
	// paramMessage.set_srcmodule(srcModel);
	// paramMessage.set_content(content);
	// paramMessage.set_code(code);
	// paramMessage.set_brokerurl(brokerUrl);
	// paramMessage.set_desturl(destUrl);
	// paramMessage.set_doman(doman);
	// paramMessage.set_sessionid(sessionId);
	// std::string message;
	// paramMessage.SerializeToString(&message);
	// return message;
// }



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

		//int ret=m_pSer->SendData("Test",strlen("Test"),remoteAddr,remotePort,true);	
		//printf("\n  ret:%d  \n",ret);
		return 0;

		// std::string message;
		// for (int i=0;i<len;++i)
		// {
			// message.push_back(pBuffer[i]);
		// }

		// ParamMessage paramMessage;
		// paramMessage.ParseFromString(message);

		// int nSrcModel=paramMessage.srcmodule();
		// int nModel=paramMessage.model();
		// int nType=paramMessage.type();

		// printf("CUConsul::OnData  nModel:%d  nSrcModel:%d  nType:%d \n",nModel,nSrcModel,nType);

		// if (nModel==C_SIS_SERVER)
		// {
			// if (11010==nType)
			// {
				// ReqGetLeaderAddress getLeaderAddress;
				// getLeaderAddress.ParseFromString(paramMessage.content());
				

				// RspGetLeaderAddress leaderAddress;
				// leaderAddress.set_leaderip("192.168.1.75",strlen("192.168.1.75"));
				// leaderAddress.set_leaderport(5500);
				// std::string content;
				// leaderAddress.SerializeToString(&content);

				// std::string message=GetParamMessage(C_BPX_SERVER,11010,C_SIS_SERVER,content);
				// int ret=m_pSer->SendData(message.c_str(),message.size(),remoteAddr,remotePort,false);	
				// printf(" run here ret:%d \n",ret);
				
			// }
		// }
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
	int ret=bser.Start("192.168.3.170",5666);
	cout<<"start ret "<<ret<<endl; 

	for(int i=0;i<100;)
	{
		printf("\n sleep \n");
		sleep(1);
	}
	printf(" Stop begin \n");
	bser.Stop();
	printf(" Stop End \n");


	while(true)
	{
		sleep(1);
	}

	return 0;
}
