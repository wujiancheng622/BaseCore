#include <vector>
#include <string>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include "TcpClientModel.h"
#include "ThreadCoreBase.h"
#include "TcpCommon.h"

 
 using namespace boost::asio;
 using namespace boost;
 using namespace boost::system;
 using namespace BaseCore::Threads;

 using std::string;
 using std::endl;
 using std::cout;
 using std::vector;

	
namespace BaseCore
{

namespace Net
{
	
 // class TcpClient;
 class Client;

 class TcpClient_Helper:public BaseCore::Threads::ThreadCoreBase
 {
 public:
	 TcpClient_Helper(TcpClient *pOutHandler);
	 virtual ~TcpClient_Helper();
	 int Start(const char* ip,int nPort,bool bConnectAsync,bool bAutoReconnect,int hHandle=0);

	 int SetPackageHeaderTrailer(const char *pHeader,int headerLen,const char *pTrailer,int trailerLen);

	 void Stop();
	 void Run();	

	 Client *GetClient() 
	 {
		 
		 MutexGuard mutexLock(m_mutex());
		 return m_client; 
	 }

 private:
	 Client *m_client;
	 TcpClient *m_pOutHander;

	  Mutex m_mutex;
 };




 class  Client:public BaseCore::Threads::ThreadCoreBase
 {
	
	  typedef Client		this_type;
	  typedef ip::tcp::endpoint endpoint_type;
	  typedef ip::address 	address_type;
	  typedef ip::tcp::socket socket_type;
	  typedef boost::shared_ptr<socket_type> sock_pt;
	  typedef vector<char>			buffer_type;
	
	
 public:
	 Client(TcpClient *pListener);
	 ~Client();

	
	 void run_io_server();
	 int connect(std::string serverIp,int serverPort,bool bConnectAsync,bool bAutoReconnect);
	 int disconnect();

	 void conn_handle(const boost::system::error_code& error,sock_pt sock);
	 int sendData(const char *pBuffer,int len,bool bAsync);
	 void read_handle(const boost::system::error_code& ec,std::size_t bytes_transferred,sock_pt sock);
	 void write_handler(const boost::system::error_code& error, size_t bytes_transferred,sock_pt sock);

	 int SetPackageHeaderTrailer(const char *pHeader,int headerLen,const char *pTrailer,int trailerLen);

	 void setHandle(int hHandle);

	 int getHandle();

	 virtual void Run()
	 {

		int dataBegin=0;
		int dataEnd=0;
		int dataLen=0;

		std::string strData;


		

		MutexGuard bufferLock((*(m_spMutex))());
		dataBegin=m_recvDataBuffer.find(m_packetHeader);
		dataEnd=m_recvDataBuffer.find(m_packetTrailer);
		dataLen=dataEnd-dataBegin-m_packetHeaderLen;
		if (!m_recvDataBuffer.empty())
		{
			//std::cout<<"dataBegin "<<dataBegin<<" dataEnd "<<dataEnd<<std::endl;
			//std::cout<<"m_recvDataBuffer "<<m_recvDataBuffer<<"size "<<m_recvDataBuffer.size()<<" dataLen "<<dataLen<<std::endl;

			//std::cout<<"last "<<&m_recvDataBuffer[dataEnd]<<std::endl;

			//for (int i=0;i<m_recvDataBuffer.size();++i)
			//{
			//	std::cout<<i<<" "<<m_recvDataBuffer[i]<<std::endl;
			//}

		}

		//std::cout<<"Run enter  dataLen"<<dataLen<<std::endl;
		while(dataBegin!=-1&&dataEnd!=-1&&dataLen!=0)
		{
			if (0<dataLen)
			{
				strData=m_recvDataBuffer.substr(dataBegin+m_packetHeaderLen,dataLen);//22是BOOST_ASIO_DATA_BEGIN(的长度
				m_recvDataBuffer.erase(dataBegin,(dataEnd-dataBegin)+m_packetTailerLen);
				m_pListener->m_pNetSdkListener->OnData(strData.c_str(),strData.size(),m_hHandle);
				dataBegin=m_recvDataBuffer.find(m_packetHeader);
				dataEnd=m_recvDataBuffer.find(m_packetTrailer);
				dataLen=dataEnd-dataBegin-m_packetHeaderLen;
			}else{
				m_recvDataBuffer.erase(0,dataEnd+m_packetTailerLen);
				dataBegin=m_recvDataBuffer.find(m_packetHeader);
				dataEnd=m_recvDataBuffer.find(m_packetTrailer);
				dataLen=dataEnd-dataBegin-m_packetHeaderLen;
			}
		}

		//std::cout<<"Run leave"<<std::endl;

	 }
	 
 private:
	 boost::shared_ptr<io_service> 	 	m_spIO_Server;
	 boost::shared_ptr<vector<char> > m_buf;
	 endpoint_type	m_ep;
	 sock_pt m_sock; //用来和服务端进行交互使用的
	 
	 TcpClient *m_pListener;

	 boost::shared_ptr<Mutex> m_spMutex; 
	 boost::shared_ptr<Mutex> m_spMutexConn; 

	 string m_recvDataBuffer;//接受服务端发送过来的数据缓存区

	 bool m_bAutoReconnect;//当与服务端断开后是否进行自动重连

	 bool m_bConnected;

	 int m_hHandle;//用来标识当前tcp client的句柄

	 string m_packetHeader;//包头
	 int m_packetHeaderLen;//包头长度
	 string m_packetTrailer;//包尾
	 int m_packetTailerLen;//包尾长度
	 bool m_bGroupPackage;//是否组包

	  
 }; 	

 
	 Client::Client(TcpClient *pListener):m_buf(new vector<char>(MAX_RECV_BYTES_ONE_TIME, 0)),
	 m_spIO_Server(new io_service),
	 m_pListener(pListener),
	 m_spMutex(new Mutex),
	 m_spMutexConn(new Mutex),
	 m_bConnected(false),
	 m_bGroupPackage(false),
	 m_bAutoReconnect(true),
	 m_hHandle(0)
	 {
		 Start();
	 }
	 
	 Client::~Client()
	 {		 
		 if (m_sock)
		 {
			 m_sock->close();
			 m_sock.reset();
		 }
		 if (m_spMutex)
		 {
			 m_spMutex.reset();
		 }
		 
	 }
	 
	 
	 void Client::run_io_server()
	 {
		 if(m_spIO_Server)
		 {
			(*m_spIO_Server).run();	 
		 }
	 }
	  int Client::connect(std::string serverIp,int serverPort,bool bConnectAsync,bool bAutoReconnect)
	  {

		  if (!m_bConnected)
		  {

			  std::cout << "Client::connect" << endl;

			  m_ep=endpoint_type(address_type::from_string(serverIp.c_str()),serverPort);
			  m_bAutoReconnect=bAutoReconnect;

			  sock_pt sock(new boost::asio::ip::tcp::socket(*m_spIO_Server));  
			  if(bConnectAsync)
			  {
				  m_bConnected=false;
				  //std::cout<<"connect begin"<<std::endl;
				  sock->async_connect(m_ep, boost::bind(&Client::conn_handle, this,  
					  boost::asio::placeholders::error, sock));  
				  //std::cout<<"connect end"<<std::endl;
				  return 0;
			  }else{
				  try
				  {
					  sock->connect(m_ep);
				  }catch(...)
				  {
					  std::cout<<"connect failed"<<std::endl;
					  return	-1;
				  }
				  std::cout<<"connect success"<<std::endl;


				  //// 异步读取数据  
				  sock->async_read_some(boost::asio::buffer(*m_buf), boost::bind(&Client::read_handle,  
					  this,   
					  boost::asio::placeholders::error,
					  boost::asio::placeholders::bytes_transferred,
					  sock));  
				  m_bConnected=true;
				  m_sock=sock;

				  std::cout<<"remote server:";
				  std::cout<<sock->remote_endpoint().address()<<":"<<sock->remote_endpoint().port()<<std::endl;



				  m_pListener->m_pNetSdkListener->OnConnect(sock->remote_endpoint().address().to_string().c_str(), sock->remote_endpoint().port());

				  return 0;

			  }
		  }else{
			  return 0;
		  }
	  }
	
	  void Client::conn_handle(const boost::system::error_code& error,sock_pt sock)
	  {
		  //std::cout<<"conn_handle  1"<<endl;
		  MutexGuard bufferLock((*(m_spMutexConn))());
		  //std::cout<<"conn_handle  2"<<endl;
		  static int connectFailedTimes=0;
		  if (error)  
		  {  			 
			// reconnect to server 
			std::cout<<std::endl<<"connect failed ,now reconnect to server ip:"<<m_ep.address()<<" port:"<<m_ep.port()<<std::endl;
			ThreadCoreBase::Sleep(connectFailedTimes*3000);    //
			{
				connectFailedTimes=1;
			}
			sock->async_connect(m_ep, boost::bind(&Client::conn_handle, this,  
			  boost::asio::placeholders::error, sock));  
			  
			 return;  
		  }  
		  

		  std::cout<<"conn_handle  remote server  sd:";
		  std::cout<<sock->remote_endpoint().address()<<":"<<sock->remote_endpoint().port()<<std::endl;
		  std::cout<<"conn_handle  remote server1 "<<endl;
		 
		  {
			  MutexGuard bufferLock((*(m_spMutex))());
			  m_recvDataBuffer.clear();
		  }
		  

		  connectFailedTimes=0;
		  std::cout<<"conn_handle  1"<<endl;

		  // 异步读取数据  
		  sock->async_read_some(boost::asio::buffer(*m_buf), boost::bind(&Client::read_handle,  
			  this,   
			  boost::asio::placeholders::error,
			  boost::asio::placeholders::bytes_transferred,
			  sock));  

		  std::cout<<"conn_handle  2"<<endl;
		  m_bConnected=true;
		  m_sock=sock;
		  std::cout<<"conn_handle  3"<<endl;
		  m_pListener->m_pNetSdkListener->OnConnect(sock->remote_endpoint().address().to_string().c_str(), sock->remote_endpoint().port());
		  std::cout<<endl<<"conn_handle  4"<<endl;
		   
	  }


	  int Client::sendData(const char *pBuffer,int len,bool bAsync)
	  {
		  if (m_bConnected&&m_sock)
		  {
			  if (m_bGroupPackage)
			  {

				  string tmpBuffer;//(/*MAX_SEND_BYTES_ONE_TIME*/64,0);
				  int totalLen=m_packetHeaderLen+m_packetTailerLen+len;
				  //if (totalLen>/*MAX_SEND_BYTES_ONE_TIME*/64)
				  //{
					 // return -1;
				  //}

				  for (int i=0;i<m_packetHeaderLen;++i)
				  {
					  tmpBuffer.push_back(m_packetHeader[i]);
				  }
				  for (int i=0;i<len;++i)
				  {
					  tmpBuffer.push_back(pBuffer[i]);
				  }
				  for (int i=0;i<m_packetTailerLen;++i)
				  {
					  tmpBuffer.push_back(m_packetTrailer[i]);
				  }	


				  //std::cout<<"tmpBuffer "<<tmpBuffer<<std::endl;

				  if (true==bAsync)
				  {
					  m_sock->async_write_some(buffer(tmpBuffer,tmpBuffer.size()),bind(&this_type::write_handler,this,boost::asio::placeholders::error,boost::asio::placeholders::bytes_transferred,m_sock));
					  return 0;
				  }else{
					  //printf("\n tmpBuffer.size():%d  \n",tmpBuffer.size());
					  int ret=m_sock->send(boost::asio::buffer(tmpBuffer, tmpBuffer.size()));
					  //std::cout<<"ret"<<ret<< "m_packetHeaderLen "<<m_packetHeaderLen<<" m_packetTailerLen "<<m_packetTailerLen<<" totalLen"<<totalLen<<std::endl;
					  if (ret>0)
					  {
						  if (ret<=m_packetHeaderLen)
						  {
							  ret=0;
						  }else if (ret<len+m_packetHeaderLen)
						  {
							  ret=ret-m_packetHeaderLen;
						  }else{
							  ret=len;
						  }
					  }
					  return ret;
				  }
			  }else{
				  if (true==bAsync)
				  {
					  m_sock->async_write_some(buffer(pBuffer,len),bind(&this_type::write_handler,this,boost::asio::placeholders::error,boost::asio::placeholders::bytes_transferred,m_sock));
					  return 0;
				  }else{
					  return m_sock->send(boost::asio::buffer(pBuffer, len));
				  }
			  }
			  
		  }else{
			  return -1;
		  }
	  }
	


	  void Client::write_handler(const boost::system::error_code& ec, size_t bytes_transferred,sock_pt sock) 
	  {
		  if(ec)
		  {
			  std::cout<<"write_handler read_handle have error:ec"<<ec<<std::endl;
			  std::cout<<"error msg"<<ec.message()<<std::endl;
			  return ;
		  }
		  
	  }

	
	  void Client::read_handle(const boost::system::error_code& ec,std::size_t bytes_transferred,sock_pt sock)
	  {
		  std::cout<<"Client::read_handle bytes: "<<bytes_transferred<<" data "<<&((*m_buf)[0])<<std::endl;

		  //for (int i=0;i<bytes_transferred;++i)
		  //{
			 // std::cout<<"i:"<<i<<" "<<(int)(*m_buf)[i]<<std::endl;
		  //}

		  if(ec)
		  {
			  std::cout<<"read_handle have error:"<<ec.value()<<std::endl;
			  std::cout<<"error msg"<<ec.message()<<std::endl;
			  //if(ec.value()==2||125==ec.value()||104==ec.value())//error msgEnd of file
			  {
				  m_sock->close();
				  sock.reset();
				  m_bConnected=false;
				  sock_pt sockNew(new boost::asio::ip::tcp::socket(*m_spIO_Server));  

				  if (m_bAutoReconnect)
				  {
					  sockNew->async_connect(m_ep, boost::bind(&Client::conn_handle, this,  
						  boost::asio::placeholders::error, sockNew));  
				  }
				  m_pListener->m_pNetSdkListener->OnClose(0,ec.value());
			  }
			  return ;
		  }

			std::cout<<"m_bGroupPackage "<<m_bGroupPackage<<endl;
			if (m_bGroupPackage)
			{
				MutexGuard mutexLock((*m_spMutex)());
				
				if (m_recvDataBuffer.size()<=m_recvDataBuffer.max_size()/2)
				{
					for (int i=0;i<bytes_transferred;++i)
					{
						m_recvDataBuffer.push_back((*m_buf)[i]);
					}
				}
			}else{
				  m_pListener->m_pNetSdkListener->OnData(&((*m_buf)[0]),bytes_transferred,m_hHandle);
			}
		  
		  // 异步读取数据  
		  sock->async_read_some(boost::asio::buffer(*m_buf), boost::bind(&Client::read_handle,  
			  this,   
			  boost::asio::placeholders::error,
			  boost::asio::placeholders::bytes_transferred,
			  sock));  


	  }

	  int Client::disconnect()
	  {
		  if (m_bConnected)
		  {
			  std::cout << "Client::disconnect" << endl;
			  m_sock->close();
			  std::cout << "Client::disconnect 1" << endl;
			  m_spIO_Server.reset();
			  std::cout << "Client::disconnect 11" << endl;
			  m_spIO_Server.reset(new io_service);
			  std::cout << "Client::disconnect 2" << endl;
			  m_bConnected = false;
			  m_pListener->m_pNetSdkListener->OnClose(m_hHandle,0);
			  std::cout << "Client::disconnect 3" << endl;
			  return 0;
		  }else{
			  printf("\n Client::disconnect 0\n");
			  return 0;
		  }
	  }

	  int Client::SetPackageHeaderTrailer( const char *pHeader,int headerLen,const char *pTrailer,int trailerLen )
	  {
	
			string headStr;
			string tailerStr;
			if (headerLen<=0||trailerLen<=0)
			{
				return -1;
			}
			for (int i=0;i<headerLen;++i)
			{
				headStr.push_back(pHeader[i]);
			}
			for (int i=0;i<trailerLen;++i)
			{
				tailerStr.push_back(pTrailer[i]);
			}
			if (!headStr.compare(tailerStr))
			{
				return -1;
			}

			if (Is_Started())
			{
				Stop();
				m_packetHeader=headStr;
				m_packetTrailer=tailerStr;
				m_packetHeaderLen=headerLen;
				m_packetTailerLen=trailerLen;
				m_bGroupPackage=true;
				Start();
			}
			return 0;

	  }

	  void Client::setHandle( int hHandle )
	  {
		  m_hHandle=hHandle;
	  }

	  int Client::getHandle()
	  {
		  return m_hHandle;
	  }







	   TcpClient_Helper::TcpClient_Helper(TcpClient *pOutHandler)
	   {
		   m_client=NULL;
		   m_pOutHander=pOutHandler;
		   m_client=new Client(m_pOutHander);
	   }
	   TcpClient_Helper::~TcpClient_Helper()
	   {
			if(m_client)
			{
				delete m_client;
				m_client=NULL;
			}
	   }

	   int TcpClient_Helper::Start(const char* ip,int nPort,bool bConnectAsync,bool bAutoReconnect,int hHandle)
	   {
		 
		   string strIP(ip);
		   std::cout<<"server address ip:"<<ip<<"  port:"<<nPort<<std::endl;
		   m_client->setHandle(hHandle);
		   int ret=m_client->connect(strIP,nPort,bConnectAsync,bAutoReconnect);
		   if(0==ret)
		   {
			 ThreadCoreBase::Stop();   
			 ThreadCoreBase::Start();   
			 return 0;	
		   }else{
			   ThreadCoreBase::Stop();   
			   return -1;
		   }
	   }

	   void TcpClient_Helper::Run()
	   {
		   m_client->run_io_server();
	   }

	   void TcpClient_Helper::Stop()
	   {
		   m_client->disconnect();
		   ThreadCoreBase::Stop();   
	   }

	   int TcpClient_Helper::SetPackageHeaderTrailer( const char *pHeader,int headerLen,const char *pTrailer,int trailerLen )
	   {
		    return m_client->SetPackageHeaderTrailer(pHeader,headerLen,pTrailer,trailerLen);
	   }





	 TcpClient::TcpClient(NetSdkListener *pListener)
	 {
		m_pNetSdkListener=pListener;
		m_pDataHelper=new TcpClient_Helper(this);
	 }
	 TcpClient::~TcpClient(void)
	 {
		if(m_pDataHelper)
		{
			delete m_pDataHelper;
			m_pDataHelper=NULL;
		}
	 }


	 int  TcpClient::SendData(const char *pBuffer,int len,bool bAsync)
	 {
		 return m_pDataHelper->GetClient()->sendData(pBuffer,len,bAsync);
	 }

	 int TcpClient::Start( const char* ip,int nPort ,bool bConnectAsync,bool bAutoReconnect,int hHandle)
	 {
		 //std::cout << "TcpClient::Start" << endl;
		int ret=m_pDataHelper->Start(ip,nPort,bConnectAsync,bAutoReconnect,hHandle);
		return ret;
	 }

	 void  TcpClient::Stop()
	 {
		 m_pDataHelper->Stop();
	 }

	 int TcpClient::SetPackageHeaderTrailer( const char *pHeader,int headerLen,const char *pTrailer,int trailerLen )
	 {
		 return m_pDataHelper->SetPackageHeaderTrailer(pHeader,headerLen,pTrailer,trailerLen);
	 }

	 int TcpClient::GetHandle()
	 {
		return m_pDataHelper->GetClient()->getHandle();
	 }




}

}
