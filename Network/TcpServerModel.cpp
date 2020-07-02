#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
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
using namespace BaseCore::Threads;


using std::string;
using std::queue;
using std::endl;
using std::cout;
using std::vector;
using std::map;
using std::pair;

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

			int CloseClient(int hHandle);

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

			map<stream_socket_service<ip::tcp>::native_handle_type,string >	 m_clientSendBuffer; //客户端当前异步发送时用的数据缓冲区
			map<stream_socket_service<ip::tcp>::native_handle_type,queue<string> >	 m_clientSendBufferQueue; //客户端异步发送时用的数据缓冲区队列



			shared_ptr<Mutex> m_spBufferMutex;//用来保护客户端的数据缓存区

			//boost::shared_ptr<Mutex> m_spMutexService; 

			shared_ptr<Mutex> m_spSocketMutex;//用来保护m_clientSocketMap对象


			TcpServer *m_pListener;

			endpoint_type	m_ep;

			string m_packetHeader;//包头
			int m_packetHeaderLen;//包头长度
			string m_packetTrailer;//包尾
			int m_packetTailerLen;//包尾长度
			bool m_bGroupPackage;//是否组包

			int m_listenPort;

		public:
			Server(TcpServer *pListener/*, const char *ip, int nPort*/):
			  m_spIO_Server(new io_service),
				  m_spAcceptor(new acceptor_type(*m_spIO_Server)),
				  m_spBufferMutex(new Mutex),
				  m_spSocketMutex(new Mutex),
				  m_bGroupPackage(false),
				  m_packetHeaderLen(0),
				  m_packetTailerLen(0),
				  m_listenPort(0)
			  {
				  m_pListener=pListener;

			  }

			  void Stop()
			  {
				  if (Is_Started())
				  {

					  m_spAcceptor->close();



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


					  //cout<<"Stop MutexGuard mutexLock enter"<<endl;
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
					  //cout<<"Stop MutexGuard mutexLock leave"<<endl;


					  {
						  //MutexGuard mutexLock((*m_spMutexService)());
						  m_spIO_Server->stop();
						  m_spIO_Server.reset();
						  m_spIO_Server.reset(new io_service);
					  }

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
					  m_listenPort=nPort;
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
					  char tmp[64]={0};
					  sprintf(tmp,"tcp server ip:%s port:%d ",ip,nPort);
					  BaseCore::Threads::ThreadCoreBase::SetDesc(tmp);
					  BaseCore::Threads::ThreadCoreBase::Start();//启动线程
					  return 0;
				  }else{
					  return -1;	
				  }
			  }


			  int CloseClient(int hHandle)
			  {

				  if(m_clientSocketMap.find(hHandle)!=m_clientSocketMap.end())
				  {
					  m_clientSocketMap[hHandle]->close();
				  }
				  return 0;
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
				  ThreadCoreBase::Stop();

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


				  {
					  //MutexGuard mutexLock((*m_spMutexService)());
					  if (m_spIO_Server)
					  {
						  m_spIO_Server->stop();
						  m_spIO_Server.reset();
					  }
				  }

			  }


			  virtual void Run()
			  {
				  //printf("\n Run enter  locked:%d \n",m_spBufferMutex->IsLocked());
				  {
					  MutexGuard mutexLock((*m_spBufferMutex)());
					  //printf("\n Run enter  locked:%d  dd\n",m_spBufferMutex->IsLocked());
					  map<stream_socket_service<ip::tcp>::native_handle_type,pair<string,shared_ptr<Mutex> > >::iterator iter=m_clientBufferMap.begin();
					  map<stream_socket_service<ip::tcp>::native_handle_type,pair<string,shared_ptr<Mutex> > >::iterator iterEnd=m_clientBufferMap.end();
					  int dataBegin=0;
					  int dataEnd=0;
					  int dataLen=0;

					  //cout<<"size "<<m_clientBufferMap.size()<<endl;

					  while(iter!=iterEnd)
					  {
						  //cout<<"mutex : "<<iter->second.second.get()<<endl;
						  pair<string,shared_ptr<Mutex> > &pairTmp=iter->second;
						  string &dataBuffer=pairTmp.first;
						  //cout<<" run here run"<<endl;
						  MutexGuard bufferLock((*(pairTmp.second))());

						  std::string strData;


						  dataBegin=dataBuffer.find(m_packetHeader);
						  dataEnd=dataBuffer.find(m_packetTrailer);
						  dataLen=dataEnd-dataBegin-m_packetHeaderLen;

						  //printf("\n dataBuffer:%s \n",dataBuffer.c_str());
						  //cout<<"dataBuffer "<<dataBuffer.c_str()<<" dataBuffer size"<<dataBuffer.size()<<"dataBegin "<<dataBegin<<" dataEnd"<<dataEnd<<" dataLen"<<dataLen<<endl;

						  //printf(" run 3\n");
						  while(dataBegin!=-1&&dataEnd!=-1&&dataLen!=0&&m_packetTailerLen!=0&&m_packetHeaderLen!=0)
						  {
							  //printf(" run 4 dataLen:%d \n",dataLen);
							  if (0<dataLen)
							  {

								  strData=dataBuffer.substr(dataBegin+m_packetHeaderLen,dataLen);//22是BOOST_ASIO_DATA_BEGIN(的长度

								  {
									  dataBuffer.erase(dataBegin,(dataEnd-dataBegin)+m_packetTailerLen);
								  }


								  m_pListener->m_pNetSdkListener->OnData(strData.c_str(),strData.size(),iter->first,m_listenPort);

								  dataBegin=dataBuffer.find(m_packetHeader);
								  dataEnd=dataBuffer.find(m_packetTrailer);
								  dataLen=dataEnd-dataBegin-m_packetHeaderLen;
							  }
							  else{
								  //printf(" run 4 dataLen:%d 11\n",dataLen);
								  dataBuffer.erase(0,dataEnd+m_packetTailerLen);
								  dataBegin=dataBuffer.find(m_packetHeader);
								  dataEnd=dataBuffer.find(m_packetTrailer);
								  dataLen=dataEnd-dataBegin-m_packetHeaderLen;
							  }
							  //printf(" run 4 dataLen:%d dataBegin:%d  dataEnd:%d \n",dataLen,dataBegin,dataEnd);
						  }
						  //printf(" run 5\n");
						  ++iter;
					  }
					  //printf(" run 6\n");
				  }
				  //printf("\n Run leave \n");

			  }


			  int stopIoService()
			  {
				  if (m_spIO_Server&&!m_spIO_Server->stopped())
				  {
					  //printf("\n test 1 \n");
					  m_spIO_Server->stop();
					  //printf("\n test 2 \n");
				  }
				  return 0;
			  }


			  void run_io_server()
			  {
				  //MutexGuard mutexLock((*m_spMutexService)());
				  //printf("\n run_io_server 1 \n");
				  if(m_spIO_Server)
				  {
					  m_spIO_Server->poll();
				  }
				  //printf("\n run_io_server 2 \n");

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

						  string data;
						  for (int i=0;i<m_packetHeaderLen;++i)
						  {
							  data.push_back(m_packetHeader[i]);
						  }
						  for (int i=0;i<len;++i)
						  {
							  data.push_back(pBuffer[i]);
						  }
						  for (int i=0;i<m_packetTailerLen;++i)
						  {
							  data.push_back(m_packetTrailer[i]);
						  }	


						  if(bAsync)
						  {
							  string &tmpBuffer=m_clientSendBuffer[sock_tmp->native_handle()];

							  {
								  MutexGuard mutexLock((*m_spBufferMutex)());
								  if (tmpBuffer.length()!=0)
								  {
									  queue<string> &sendQueue=m_clientSendBufferQueue[sock_tmp->native_handle()];
									  sendQueue.push(data);
									  return 0;
								  }
								  for ( int i=0;i<data.length();++i)
								  {
									  tmpBuffer.push_back(data[i]);
								  }
							  }

								boost::asio::async_write(*sock_tmp,
									boost::asio::buffer(tmpBuffer.c_str(),tmpBuffer.length()),
									boost::bind(&this_type::write_handler, this,
									boost::asio::placeholders::error,boost::asio::placeholders::bytes_transferred,sock_tmp)); 
							 
							  return 0;
						  }else{
								string tmpBuffer;
								for ( int i=0;i<data.length();++i)
								{
									tmpBuffer.push_back(data[i]);
								}

								int ret=0;

								try
								{
									ret=boost::asio::write(*sock_tmp,buffer(tmpBuffer.c_str(),tmpBuffer.size()));
								}
								catch(...)
								{
									printf("send synchronous data failed handle:%d data len:%d \n",hHandle,len);
									return -1;
								}
								
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
								printf("send synchronous data success handle:%d data len:%d ret:%d \n", hHandle, len,ret);
								return ret;
						  }
					  }else{
						  if(bAsync)
						  {

							  string &tmpBuffer=m_clientSendBuffer[sock_tmp->native_handle()];
							  {
								  MutexGuard mutexLock((*m_spBufferMutex)());
								  if (tmpBuffer.length()!=0)
								  {
									  queue<string> &sendQueue=m_clientSendBufferQueue[sock_tmp->native_handle()];
									  string data;
									  for (int i=0;i<len;++i)
									  {
										  data.push_back(pBuffer[i]);
									  }
									  sendQueue.push(data);
									  return 0;
								  }
								  for (int i=0;i<len;++i)
								  {
									  tmpBuffer.push_back(pBuffer[i]);
								  }
							  }

							  boost::asio::async_write(*sock_tmp,
								  boost::asio::buffer(tmpBuffer.c_str(),tmpBuffer.length()),
								  boost::bind(&this_type::write_handler, this,
								  boost::asio::placeholders::error,boost::asio::placeholders::bytes_transferred,sock_tmp)); //服务器端将收到的消息送给所有的客户端（广播的方式）
							  return 0;
						  }else{

							  int ret=0;
							  try
							  {
								  ret=boost::asio::write(*sock_tmp,buffer(pBuffer,len));
							  }
							  catch(...)
							  {
								  return -1;
							  }
							  
							  return ret;
						  }
					  }
				}
				else
				{
					printf("no this client handle:%d cur client size:%d \n", hHandle, m_clientSocketMap.size());
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
				  accept();

				  int ret=m_pListener->m_pNetSdkListener->OnAccept(sock->native_handle(),sock->remote_endpoint().address().to_string().c_str(),sock->remote_endpoint().port(),m_listenPort);
				  if (ret==false)//拒绝接受该连接
				  {
					  sock->close();
					  return;
				  }

				  cout<<"remote client:";
				  cout<<sock->remote_endpoint().address()<<":"<<sock->remote_endpoint().port()<<endl;

				  m_newSock=sock;//设置最新连接的客户端为sock


				  {
					  MutexGuard mutexLock((*m_spSocketMutex)());
					  m_clientSocketMap[sock->native_handle()]=sock;
					  cout<<"accept_handler handle:"<<sock->native_handle()<<endl;
				  }

				  //cout<<"accept_handler enter"<<endl;
				  {
					  MutexGuard mutexLock((*m_spBufferMutex)());
					  m_clientBufferMap[sock->native_handle()].second.reset(new Mutex);
					  m_clientOriginalDataMap[sock->native_handle()].reset(new vector<char>(MAX_RECV_BYTES_ONE_TIME, 0));
					  m_clientSendBuffer[sock->native_handle()];
					  m_clientSendBufferQueue[sock->native_handle()];
				  }
				  //cout<<"accept_handler leave"<<endl;

				  

				  //accept();

				  sock->async_read_some(boost::asio::buffer(*(m_clientOriginalDataMap[sock->native_handle()])), boost::bind(&Server::read_handle,  
					  this,   
					  boost::asio::placeholders::error
					  ,boost::asio::placeholders::bytes_transferred,
					  sock));  

			  }


			  void read_handle(const system::error_code& ec,std::size_t bytes_transferred,sock_ptr sock)
			  {
				 // static int size=0;
				 // size+=bytes_transferred;
				  //printf("\n read len:%d size:%d   m_bGroupPackage:%d \n",bytes_transferred,size,m_bGroupPackage);

				  //sock->async_read_some(boost::asio::buffer(*(m_clientOriginalDataMap[sock->native_handle()])), boost::bind(&Server::read_handle,  
					 // this,   
					 // boost::asio::placeholders::error
					 // ,boost::asio::placeholders::bytes_transferred,
					 // sock));  

				  //return ;


				  //cout<<"read_handle "<<&((*(m_clientOriginalDataMap[sock->native_handle()]))[0])<<" hanele :"<<sock->native_handle()<<" bytes_transferred "<<bytes_transferred<<endl;
				  if(ec)
				  {
					  std::cout<<"read_handle have error:"<<ec.value()<<" error msg"<<ec.message()<<std::endl;

					  //if(2==ec.value()||125==ec.value()||104==ec.value())//error msgEnd of file
					  {
						  int socketHandle=sock->native_handle();
						  //printf("\n run cloise\n");
						  if(m_newSock)
						  {
							  int newSocketHandle=m_newSock->native_handle();
							  if (socketHandle==newSocketHandle)
							  {
								  m_newSock.reset();
							  }
						  }

						  //printf("\n run cloise 1\n");
						  {
							  //printf("\n run cloise 11 \n");
							  MutexGuard mutexLock((*m_spBufferMutex)());
							  //printf("\n run cloise 12\n");
							  if (m_clientBufferMap.find(sock->native_handle())!=m_clientBufferMap.end())
							  {
								  m_clientBufferMap[sock->native_handle()].second.reset();
								  m_clientBufferMap.erase(m_clientBufferMap.find(sock->native_handle()));
							  }
							  //printf("\n run cloise 13\n");
							  if (m_clientOriginalDataMap.find(sock->native_handle())!=m_clientOriginalDataMap.end())
							  {
								  m_clientOriginalDataMap.erase(m_clientOriginalDataMap.find(sock->native_handle()));
							  }
							  //printf("\n run cloise 14\n");

						  }

						  //printf("\n run cloise 2\n");

						  {
							  MutexGuard mutexLock((*m_spSocketMutex)());
							  if(m_clientSocketMap.find(sock->native_handle())!=m_clientSocketMap.end())
							  {
								  m_clientSocketMap.erase(m_clientSocketMap.find(sock->native_handle()));
							  }
						  }


						  cout<<"read_handle ec.value()=="<<ec.value()<<endl;
						  sock->close();
						  //cout<<"read_handle ec.value()== ff"<<ec.value()<<endl;
						  m_pListener->m_pNetSdkListener->OnClose(socketHandle,ec.value(),m_listenPort);

					  }
					  return ;
				  }

				  {
					  //cout<<"read enter "<<m_bGroupPackage<<endl;
					  if (m_bGroupPackage)
					  {
						  MutexGuard mutexLock((*m_spBufferMutex)());
						  //cout<<"read enter "<<m_bGroupPackage<<endl;
						  if (m_clientBufferMap.find(sock->native_handle())!=m_clientBufferMap.end())
						  {
							  pair<string,shared_ptr<Mutex> > &pairTmp=m_clientBufferMap[sock->native_handle()];
							  string &dataBuffer=pairTmp.first;
							  MutexGuard mutexLock((*(pairTmp.second))());
							  if (dataBuffer.size()<=dataBuffer.max_size()/2)
							  {
								  for (int i=0;i<bytes_transferred;++i)
								  {
									  //printf("%d :%d\n",i,(*(m_clientOriginalDataMap[sock->native_handle()]))[i]);
									  dataBuffer.push_back((*(m_clientOriginalDataMap[sock->native_handle()]))[i]);
								  }
							  }
							  //printf("\n pairTmp.first size:%d  dataBuffer:%s \n",pairTmp.first.size(),dataBuffer.c_str());
						  }
					  }else{
						  m_pListener->m_pNetSdkListener->OnData(&((*(m_clientOriginalDataMap[sock->native_handle()]))[0]),bytes_transferred,sock->native_handle(),m_listenPort);
					  }
					  //cout<<"read leave"<<endl;
				  }


				  //m_clientOriginalDataMap[sock->native_handle()]->resize(MAX_RECV_BYTES_ONE_TIME,0);
				  sock->async_read_some(boost::asio::buffer(*(m_clientOriginalDataMap[sock->native_handle()])), boost::bind(&Server::read_handle,  
					  this,   
					  boost::asio::placeholders::error
					  ,boost::asio::placeholders::bytes_transferred,
					  sock));  
			  }


			  void write_handler(const system::error_code& ec,std::size_t bytes_transferred,sock_ptr sock)
			  {
				  MutexGuard mutexLock((*m_spBufferMutex)());
				  if(ec)
				  {
					  cout<<"write_handler read_handle have error:ec"<<ec<<endl;
					  cout<<"error msg"<<ec.message()<<endl;
					  string &strBuf=m_clientSendBuffer[sock->native_handle()];
					  strBuf.clear();
					  queue<string> &sendQueue=m_clientSendBufferQueue[sock->native_handle()];
					  while(sendQueue.size()>0)
					  {
						  sendQueue.pop();
					  }
					  return ;
				  }
				  {
					  
					  string &strBuf=m_clientSendBuffer[sock->native_handle()];
					  int leftBytes=strBuf.length()-bytes_transferred;
					  strBuf=strBuf.substr(bytes_transferred,leftBytes);
					  //std::cout<<"write_handler bytes_transferred size:"<<bytes_transferred<<" strBuf size:"<<strBuf.length()<<" handle:"<<sock->native_handle()<<std::endl;
					  queue<string> &sendQueue=m_clientSendBufferQueue[sock->native_handle()];
					  if (strBuf.length()==0&&!sendQueue.empty())
					  {
						  strBuf=sendQueue.front();
						  sendQueue.pop();

						 // cout<<" write_handler send rest data len:"<<strBuf.length()<<"m_clientSendBufferQueue size:"<<sendQueue.size()<<endl;
						  boost::asio::async_write(*sock,
							  boost::asio::buffer(strBuf.c_str(),strBuf.length()),
							  boost::bind(&this_type::write_handler, this,
							  boost::asio::placeholders::error,boost::asio::placeholders::bytes_transferred,sock)); //服务器端将收到的消息送给所有的客户端（广播的方式）
					  }

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
			if (Is_Started())
			{
				ThreadCoreBase::Stop();
			}

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
					char tmp[64]={0};
					sprintf(tmp,"tcp server_helper ip:%s port:%d ",ip,nPort);
					BaseCore::Threads::ThreadCoreBase::SetDesc(tmp);
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

		}

		void TcpServer_Helper::Stop()
		{
			if (Is_Started())
			{
				m_server->stopIoService();
				ThreadCoreBase::Stop();
				m_server->Stop();
			}
		}

		int TcpServer_Helper::SetPackageHeaderTrailer( const char *pHeader,int headerLen,const char *pTrailer,int trailerLen )
		{
			return m_server->SetPackageHeaderTrailer(pHeader,headerLen,pTrailer,trailerLen);
		}

		int TcpServer_Helper::CloseClient( int hHandle )
		{
			if (Is_Started())
			{
				int ret=m_server->CloseClient(hHandle);
				return ret;
			}else{
				return -1;
			}
		}



		TcpServer::TcpServer(NetSdkListener *pListener)
		{
			std::cout << "tcp server version 2017/10/30/15:10" << endl;
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


		int TcpServer::CloseClient( int hHandle )
		{
			return m_pDataHelper->CloseClient(hHandle);
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
			//std::cout<<"TcpServer SetPackageHeaderTrailer enter"<<std::endl;
			return m_pDataHelper->SetPackageHeaderTrailer(pHeader,headerLen,pTrailer,trailerLen);
		}



	}

}


