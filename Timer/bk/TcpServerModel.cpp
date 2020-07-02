#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/thread/lock_factories.hpp>
#include "TcpServerModel.h"
#include "ThreadCoreBase.h"
#include "TcpCommon.h"

using namespace boost::asio;
using namespace boost;
using namespace boost::system;
using namespace std;
using namespace BaseCore::Threads;


	
namespace BaseCore
{

namespace Net
{
	


class TcpServer;
class Server;


class TcpServer_Helper:public BaseCore::Threads::ThreadCoreBase
{
public:
	TcpServer_Helper(TcpServer *pOutHandler);
	virtual ~TcpServer_Helper();

	int SetPackageHeaderTrailer(const char *pHeader,int headerLen,const char *pTrailer,int trailerLen);

	int Start(const char *ip,int nPort);
	void Stop();
	void Run();	

	Server *GetServer() { return m_server; }

private:
	Server *m_server;
	TcpServer *m_pOutHander;
};


class  Server:public BaseCore::Threads::ThreadCoreBase
{
	
	 typedef Server				this_type;
	 typedef ip::tcp::acceptor acceptor_type;
	 typedef ip::tcp::endpoint endpoint_type;
	 typedef ip::tcp::socket socket_type;
	 typedef shared_ptr<socket_type> sock_ptr;
	
private:
	shared_ptr<io_service> 	 	m_spIO_Server;

	shared_ptr<acceptor_type> 	m_spAcceptor;

	
	sock_ptr m_newSock;//用来保存最近一次连接的客户端
	
	map<stream_socket_service<ip::tcp>::native_handle_type,sock_ptr > m_clientSocketMap;
	
	map<stream_socket_service<ip::tcp>::native_handle_type,pair<string,shared_ptr<Mutex> > >	m_clientBufferMap;//存放每个客户端发送过来的数据的缓存区，是去除包头包尾的数据

	map<stream_socket_service<ip::tcp>::native_handle_type,boost::shared_ptr<vector<char> > >	m_clientOriginalDataMap;//存放每个客户端发送过来的数据的缓存区，没有去除包头包尾
	
	shared_ptr<Mutex> m_spBufferMutex;//用来保护客户端的数据缓存区

	shared_ptr<Mutex> m_spSocketMutex;//用来保护m_clientSocketMap对象
	

	TcpServer *m_pListener;

	endpoint_type	m_ep;
	
	string m_packetHeader;//包头
	int m_packetHeaderLen;//包头长度
	string m_packetTrailer;//包尾
	int m_packetTailerLen;//包尾长度
	bool m_bGroupPackage;//是否组包
	
public:
	Server(TcpServer *pListener/*, const char *ip, int nPort*/):
		m_spIO_Server(new io_service),
		m_spAcceptor(new acceptor_type(*m_spIO_Server)),
		m_spBufferMutex(new Mutex),
		m_spSocketMutex(new Mutex),
		m_bGroupPackage(false),
		m_packetHeaderLen(0),
		m_packetTailerLen(0)
	{
		m_pListener=pListener;
		
	}

	void Stop()
	{
		if (Is_Started())
		{
			
			m_spAcceptor->close();
			m_spIO_Server->stop();
			
			
		{
			MutexGuard mutexLock((*m_spSocketMutex)());
			map<stream_socket_service<ip::tcp>::native_handle_type,sock_ptr >::iterator iter=m_clientSocketMap.begin();
			map<stream_socket_service<ip::tcp>::native_handle_type,sock_ptr >::iterator iterEnd=m_clientSocketMap.end();
			while(iter!=iterEnd)
			{
				(iter->second)->close();
				(iter->second).reset();
				++iter;
			}
			m_clientSocketMap.clear();
		}


		{
			MutexGuard mutexLock((*m_spBufferMutex)());
			map<stream_socket_service<ip::tcp>::native_handle_type,pair<string,shared_ptr<Mutex> > >::iterator iter=m_clientBufferMap.begin();
			map<stream_socket_service<ip::tcp>::native_handle_type,pair<string,shared_ptr<Mutex> > >::iterator iterEnd=m_clientBufferMap.end();
			while(iter!=iterEnd)
			{
				(iter->second).second.reset();
				++iter;
			}
			m_clientBufferMap.clear();
		}
		
		
			
			m_spIO_Server.reset();
			m_spIO_Server.reset(new io_service);
			m_spAcceptor.reset();
			m_spAcceptor.reset(new acceptor_type(*m_spIO_Server));
			BaseCore::Threads::ThreadCoreBase::Stop();//停止线程
			cout<<" stop server success "<<endl;
		}
	
	}

	int Start(const char *ip, int nPort,bool reuse_addr = true)
	{
		if (!Is_Started())
		{
			cout << "server ip:" << ip << " port:" << nPort << endl;
			m_ep = endpoint_type(ip::address::from_string(ip), nPort);
			m_spAcceptor->open(m_ep.protocol());
			if (reuse_addr)
				m_spAcceptor->set_option(socket_base::reuse_address(true));
			
			boost::system::error_code ec;
			m_spAcceptor->bind(m_ep,ec);
			if(ec==0)
			{
				cout<<"bind success"<<endl;
			}else{
				cout<<"Server Start bind failed error: "<<ec<<endl;
				cout<<"error msg"<<ec.message()<<endl;	
				m_spAcceptor->close();
				return -1;
			}
			m_spAcceptor->listen();
			cout << "listen success" << endl;
			accept();
			BaseCore::Threads::ThreadCoreBase::Start();//启动线程
			return 0;
		}else{
			return -1;	
		}
	}



	int SetPackageHeaderTrailer(const char *pHeader,int headerLen,const char *pTrailer,int trailerLen)
	{
		if (!Is_Started())
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

			m_packetHeader=headStr;
			m_packetTrailer=tailerStr;
			m_packetHeaderLen=headerLen;
			m_packetTailerLen=trailerLen;
			m_bGroupPackage=true;
			return 0;
		}else{
			return -1;
		}
	}
	
	~Server()
	{

		{
			MutexGuard mutexLock((*m_spSocketMutex)());
			map<stream_socket_service<ip::tcp>::native_handle_type,sock_ptr >::iterator iter=m_clientSocketMap.begin();
			map<stream_socket_service<ip::tcp>::native_handle_type,sock_ptr >::iterator iterEnd=m_clientSocketMap.end();
			while(iter!=iterEnd)
			{
				(iter->second)->close();
				(iter->second).reset();
				++iter;
			}
			m_clientSocketMap.clear();
		}


		{
			MutexGuard mutexLock((*m_spBufferMutex)());
			map<stream_socket_service<ip::tcp>::native_handle_type,pair<string,shared_ptr<Mutex> > >::iterator iter=m_clientBufferMap.begin();
			map<stream_socket_service<ip::tcp>::native_handle_type,pair<string,shared_ptr<Mutex> > >::iterator iterEnd=m_clientBufferMap.end();
			while(iter!=iterEnd)
			{
				(iter->second).second.reset();
				++iter;
			}
			m_clientBufferMap.clear();
		}


		if (m_newSock)
		{
			m_newSock.reset();
		}
		if (m_spBufferMutex)
		{
			m_spBufferMutex.reset();
		}

		if (m_spSocketMutex)
		{
			m_spSocketMutex.reset();
		}
		
		
	}


	virtual void Run()
	{
		
		MutexGuard mutexLock((*m_spBufferMutex)());
		map<stream_socket_service<ip::tcp>::native_handle_type,pair<string,shared_ptr<Mutex> > >::iterator iter=m_clientBufferMap.begin();
		map<stream_socket_service<ip::tcp>::native_handle_type,pair<string,shared_ptr<Mutex> > >::iterator iterEnd=m_clientBufferMap.end();
		int dataBegin=0;
		int dataEnd=0;
		int dataLen=0;

		//cout<<"size "<<m_clientBufferMap.size()<<endl;

		while(iter!=iterEnd)
		{
		//	cout<<"mutex : "<<iter->second.second.get()<<endl;
			pair<string,shared_ptr<Mutex> > &pairTmp=iter->second;
			string &dataBuffer=pairTmp.first;
		//	cout<<" run here run"<<endl;
			MutexGuard bufferLock((*(pairTmp.second))());

			std::string strData;


			dataBegin=dataBuffer.find(m_packetHeader);
			dataEnd=dataBuffer.find(m_packetTrailer);
			dataLen=dataEnd-dataBegin-m_packetHeaderLen;
			
			while(dataBegin!=-1&&dataEnd!=-1)
			{

				if (0<dataLen)
				{
					strData=dataBuffer.substr(dataBegin+m_packetHeaderLen,dataLen);//22是BOOST_ASIO_DATA_BEGIN(的长度
					{

						dataBuffer.erase(dataBegin,(dataEnd-dataBegin)+m_packetTailerLen);
					}

					m_pListener->m_pNetSdkListener->OnData(strData.c_str(),strData.size(),iter->first);

					dataBegin=dataBuffer.find(m_packetHeader);
					dataEnd=dataBuffer.find(m_packetTrailer);
					dataLen=dataEnd-dataBegin-m_packetHeaderLen;
				}else{
					dataBuffer.erase(0,dataEnd+m_packetTailerLen);
					dataBegin=dataBuffer.find(m_packetHeader);
					dataEnd=dataBuffer.find(m_packetTrailer);
					dataLen=dataEnd-dataBegin-m_packetHeaderLen;
				}
				
			}
			++iter;
		}

	}



	void run_io_server()
	{
		if(m_spIO_Server)
		{
			m_spIO_Server->run();
		}
		
	}


	void onClose(sock_ptr sock)
	{

	}


	int  sendData(const char *pBuffer,int len,int hHandle,bool bAsync)
	{
		sock_ptr sock_tmp;

		
		MutexGuard mutexLock((*m_spSocketMutex)());


		if(m_clientSocketMap.find(hHandle)!=m_clientSocketMap.end())
		{
			sock_tmp=m_clientSocketMap[hHandle];

		}else if(0==hHandle&&m_newSock)
		{
			sock_tmp=m_newSock;
		}

		if(sock_tmp)
		{

			if (m_bGroupPackage)
			{
				string tmpBuffer(MAX_SEND_BYTES_ONE_TIME,0);
				int totalLen=m_packetHeaderLen+m_packetTailerLen+len;
				if (totalLen>MAX_SEND_BYTES_ONE_TIME)
				{
					return -1;
				}
				

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

				//strncat(tmpBuffer,m_packetHeader.c_str(),m_packetHeaderLen);
				//strncat(&tmpBuffer[m_packetHeaderLen],pBuffer,len);
				//strncat(&tmpBuffer[m_packetHeaderLen+len],m_packetTrailer.c_str(),m_packetTailerLen);


				if(bAsync)
				{
					sock_tmp->async_write_some(buffer(tmpBuffer,tmpBuffer.size()),bind(&this_type::write_handler,this,boost::asio::placeholders::error,boost::asio::placeholders::bytes_transferred,sock_tmp));
					return 0;
				}else{
					//cout<<"tmpBuffer "<<tmpBuffer<<" len "<<totalLen<<"pack len "<<m_packetHeaderLen+m_packetTailerLen<<endl;

					//for (int i=0;i<totalLen;++i)
					//{
					//	cout<<i<<" "<<tmpBuffer[i]<<endl;
					//}


					int ret=sock_tmp->send(buffer(tmpBuffer,tmpBuffer.size()));
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
				if(bAsync)
				{
					sock_tmp->async_write_some(buffer(pBuffer,len),bind(&this_type::write_handler,this,boost::asio::placeholders::error,boost::asio::placeholders::bytes_transferred,sock_tmp));
					return 0;
				}else{
					return sock_tmp->send(buffer(pBuffer,len));
				}
			}
		}		
		return -1;

	}


	void accept()
	{
		sock_ptr sock(new socket_type(*m_spIO_Server));
		m_spAcceptor->async_accept(*sock,bind(&this_type::accept_handler,this,boost::asio::placeholders::error,sock));

	}
	
	void accept_handler(const error_code& ec,sock_ptr sock)
	{
		if(ec)
		{
			cout<<"accept_handler have error:ec"<<ec<<endl;
			cout<<"error msg"<<ec.message()<<endl;
			this->onClose(sock);
			return ;
		}
		cout<<"remote client:";
		cout<<sock->remote_endpoint().address()<<":"<<sock->remote_endpoint().port()<<endl;
	
		m_newSock=sock;//设置最新连接的客户端为sock
		
		
		{
			MutexGuard mutexLock((*m_spSocketMutex)());
			m_clientSocketMap[sock->native_handle()]=sock;
			cout<<"accept_handler handle:"<<sock->native_handle()<<endl;
		}


		{
			MutexGuard mutexLock((*m_spBufferMutex)());
		//	cout<<"run here"<<endl;
			m_clientBufferMap[sock->native_handle()].second.reset(new Mutex);
			m_clientOriginalDataMap[sock->native_handle()].reset(new vector<char>(MAX_RECV_BYTES_ONE_TIME, 0));
		//	cout<<"run end"<<endl;
		}
		
		m_pListener->m_pNetSdkListener->OnAccept(sock->native_handle(),sock->remote_endpoint().address().to_string().c_str(),sock->remote_endpoint().port());
				
		accept();
		
		sock->async_read_some(boost::asio::buffer(*(m_clientOriginalDataMap[sock->native_handle()])), boost::bind(&Server::read_handle,  
			this,   
			boost::asio::placeholders::error
			,boost::asio::placeholders::bytes_transferred,
			sock));  
			
	}
	
	
	void read_handle(const system::error_code& ec,std::size_t bytes_transferred,sock_ptr sock)
	{

		
		//cout<<"read_handle "<<&((*(m_clientOriginalDataMap[sock->native_handle()]))[0])<<" hanele :"<<sock->native_handle()<<endl;
		  if(ec)
		  {
			  cout<<"read_handle have error:ec:    "<<ec<<endl;
			  cout<<"error msg:"<<ec.message()<<"   ec value:"<<ec.value()<<endl;
			  
			  if(ec.value()==2)//error msgEnd of file
			  {
				  int socketHandle=sock->native_handle();
				  
				  if(m_newSock)
				  {
					int newSocketHandle=m_newSock->native_handle();
					if (socketHandle==newSocketHandle)
					{
						m_newSock.reset();
					}
				  }


				  {
					  MutexGuard mutexLock((*m_spBufferMutex)());
					  if (m_clientBufferMap.find(sock->native_handle())!=m_clientBufferMap.end())
					  {
						  m_clientBufferMap[sock->native_handle()].second.reset();
						  m_clientBufferMap.erase(m_clientBufferMap.find(sock->native_handle()));
					  }
					  if (m_clientOriginalDataMap.find(sock->native_handle())!=m_clientOriginalDataMap.end())
					  {
						  m_clientOriginalDataMap.erase(m_clientOriginalDataMap.find(sock->native_handle()));
					  }
					  
				  }

				  {
					  MutexGuard mutexLock((*m_spSocketMutex)());
					  if(m_clientSocketMap.find(sock->native_handle())!=m_clientSocketMap.end())
					  {
						  m_clientSocketMap.erase(m_clientSocketMap.find(sock->native_handle()));
					  }
				  }
				  

				  cout<<"read_handle ec.value()==2"<<endl;
				  sock->close();
				  m_pListener->m_pNetSdkListener->OnClose(socketHandle,ec.value());

			  }
			  return ;
		  }
		 
		  {

			  if (m_bGroupPackage)
			  {
				  MutexGuard mutexLock((*m_spBufferMutex)());

				  if (m_clientBufferMap.find(sock->native_handle())!=m_clientBufferMap.end())
				  {
					  pair<string,shared_ptr<Mutex> > &pairTmp=m_clientBufferMap[sock->native_handle()];
					  string &dataBuffer=pairTmp.first;
					  MutexGuard mutexLock((*(pairTmp.second))());
					  if (dataBuffer.size()<=dataBuffer.max_size()/2)
					  {
						  for (int i=0;i<bytes_transferred;++i)
						  {
							  dataBuffer.push_back((*(m_clientOriginalDataMap[sock->native_handle()]))[i]);
						  }
					  }
				  }
			  }else{
				   m_pListener->m_pNetSdkListener->OnData(&((*(m_clientOriginalDataMap[sock->native_handle()]))[0]),bytes_transferred,sock->native_handle());
			  }
		  }
		
		  sock->async_read_some(boost::asio::buffer(*(m_clientOriginalDataMap[sock->native_handle()])), boost::bind(&Server::read_handle,  
			  this,   
			  boost::asio::placeholders::error
			  ,boost::asio::placeholders::bytes_transferred,
			  sock));  
	}
	  
	
	void write_handler(const system::error_code& ec,std::size_t bytes_transferred,sock_ptr sock)
	{
		
		if(ec)
		{
		  cout<<"write_handler read_handle have error:ec"<<ec<<endl;
		  cout<<"error msg"<<ec.message()<<endl;
		  return ;
		}
	}

	
}; 	


TcpServer_Helper::TcpServer_Helper(TcpServer *pOutHandler)
{
	m_server=NULL;
	m_pOutHander=pOutHandler;
	m_server = new Server(m_pOutHander);
}
TcpServer_Helper::~TcpServer_Helper()
{
	if(m_server)
	{
		delete m_server;
		m_server=NULL;
	}
}

int TcpServer_Helper::Start(const char *ip, int nPort)
{
	if (!Is_Started())
	{
		int ret=m_server->Start(ip, nPort);
		if(0==ret)
		{
			ThreadCoreBase::Start();
		}
		return ret;
	}else{
		return -1;
	}
}

void TcpServer_Helper::Run()
{
	m_server->run_io_server();
	ThreadCoreBase::Sleep(100);    // 这种更好用 

}

void TcpServer_Helper::Stop()
{
	if (Is_Started())
	{
		m_server->Stop();
		ThreadCoreBase::Stop();
	}
}

int TcpServer_Helper::SetPackageHeaderTrailer( const char *pHeader,int headerLen,const char *pTrailer,int trailerLen )
{
	return m_server->SetPackageHeaderTrailer(pHeader,headerLen,pTrailer,trailerLen);
}




	TcpServer::TcpServer(NetSdkListener *pListener)
	{
		m_pDataHelper=new TcpServer_Helper(this);
		m_pNetSdkListener=pListener;
	}

	TcpServer::~TcpServer(void)
	{
		if (m_pDataHelper)
		{
			delete m_pDataHelper;
			m_pDataHelper=NULL;
		}
		
	}

	int  TcpServer::SendData(const char *pBuffer,int len,int hHandle,bool bAsync)
	{
		return m_pDataHelper->GetServer()->sendData(pBuffer,len,hHandle,bAsync);
	}
	

	int TcpServer::Start(const char *ip,int nPort)
	{
		return m_pDataHelper->Start(ip,nPort);
	}
	
	void TcpServer::Stop()
	{
		m_pDataHelper->Stop();
	}

	int TcpServer::SetPackageHeaderTrailer( const char *pHeader,int headerLen,const char *pTrailer,int trailerLen )
	{
		return m_pDataHelper->SetPackageHeaderTrailer(pHeader,headerLen,pTrailer,trailerLen);
	}


	
}

}

 
