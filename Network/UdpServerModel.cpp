#include <iostream>
#include <ctime>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/system/system_error.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "UdpCommon.h"
#include "UdpServerModel.h"
#include "ThreadCoreBase.h"


namespace BaseCore
{


	namespace Net
	{

		using namespace boost::asio::ip;



		class UdpServer;
		class AsioUdpServer;


		class UdpServer_Helper:public BaseCore::Threads::ThreadCoreBase
		{
		public:
			UdpServer_Helper(UdpServer *pOutHandler);
			virtual ~UdpServer_Helper();

			int Start(const char *ip,int nPort);

			void Stop();

			void Run();	

			AsioUdpServer *GetServer() { return m_server; }

		private:
			AsioUdpServer *m_server;
		};


		class AsioUdpServer
		{
		public:
			AsioUdpServer(UdpServer *pListener):m_spIO_Server(new boost::asio::io_service),m_spDataBuffer(new std::vector<char>(/*UDP_DATABUFFER_INITIAL_VALUE*/40960,0))
			{
				m_pListener=pListener;
			}

			~AsioUdpServer()
			{
				Stop();
				m_spDataBuffer.reset();
			}

			int Start(const char *ip, int nPort)
			{
				m_spIO_Server->reset();
				m_spSocket.reset(new udp::socket(*m_spIO_Server, udp::endpoint(address::from_string(ip), nPort)));

				m_spSocket->async_receive_from(boost::asio::buffer(*m_spDataBuffer), m_remot_endpoint,
					boost::bind(&AsioUdpServer::Hand_receive, this,boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));

				return 0;
			}

			int Stop()
			{

				if (m_spSocket)
				{
					m_spSocket->close();
					m_spSocket.reset();
				}
				if (m_spIO_Server)
				{
					m_spIO_Server->stop();
				}
				return 0;
			}


			void Run_io_server()
			{
				if(m_spIO_Server)
				{
					m_spIO_Server->run();
				}

			}

			int StopIoService()
			{
				if (m_spIO_Server&&!m_spIO_Server->stopped())
				{
					m_spIO_Server->stop();
				}
				return 0;
			}

			int SendData(const char *pBuffer,int len,const char *remoteIp, int remptePort,bool bAsync)
			{
				if (m_spSocket)
				{
					if (bAsync)
					{
						boost::system::error_code send_error;
						int ret=m_spSocket->send_to(boost::asio::buffer(pBuffer,len), udp::endpoint(address::from_string(remoteIp), remptePort), 0, send_error);
						return ret;
					}else{
						m_spSocket->async_send_to(boost::asio::buffer(pBuffer,len), udp::endpoint(address::from_string(remoteIp), remptePort),
							boost::bind(&AsioUdpServer::Hand_send, this, boost::asio::placeholders::error,boost::asio::placeholders::bytes_transferred));
						return 0;
					}
				}else
				{
					return -1;
				}
				return 0;
			}

		private:
			void Hand_receive(const boost::system::error_code& error, std::size_t bytes_received)
			{
				if (!error || error != boost::asio::error::message_size)
				{
					if (0==bytes_received)
					{
						return ;
					}
					//std::cout <<"ec:"<<error<<" have data come in m_remot_endpoint:" << m_remot_endpoint.address() << " port:" << m_remot_endpoint.port()<< std::endl;

					m_pListener->m_pNetSdkListener->OnData(&((*m_spDataBuffer)[0]),bytes_received,m_remot_endpoint.address().to_string().c_str(),m_remot_endpoint.port());

					m_spSocket->async_receive_from(boost::asio::buffer(*m_spDataBuffer), m_remot_endpoint,
						boost::bind(&AsioUdpServer::Hand_receive, this,boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));

				}
			}

			void Hand_send(const boost::system::system_error& error, std::size_t size)
			{
				//std::cout << "Hand_send size :" << size << std::endl;
			}

		private:
			boost::shared_ptr<udp::socket>  m_spSocket; 
			boost::shared_ptr<boost::asio::io_service> 	 	m_spIO_Server;
			udp::endpoint m_remot_endpoint;
			boost::shared_ptr<std::vector<char> > m_spDataBuffer;
			UdpServer *m_pListener;
		};




		UdpServer_Helper::UdpServer_Helper( UdpServer *pOutHandler ):m_server(new AsioUdpServer(pOutHandler))
		{

		}

		UdpServer_Helper::~UdpServer_Helper()
		{
			if (m_server)
			{
				delete m_server;
			}
		}

		int UdpServer_Helper::Start( const char *ip,int nPort )
		{

			if (!Is_Started())
			{
				int ret=m_server->Start(ip,nPort);
				if(0==ret)
				{
					char tmp[64]={0};
					sprintf(tmp,"udp server_helper ip:%s port:%d ",ip,nPort);
					BaseCore::Threads::ThreadCoreBase::SetDesc(tmp);
					ThreadCoreBase::Start();
				}
				return ret;
			}else{
				return -1;
			}

		}

		void UdpServer_Helper::Stop()
		{
			if (Is_Started())
			{
				m_server->Stop();
				ThreadCoreBase::Stop();
			}
		}

		void UdpServer_Helper::Run()
		{
			m_server->Run_io_server();
		}




		UdpServer::UdpServer(NetSdkListener *pListener)
		{
			m_pDataHelper=new UdpServer_Helper(this);
			m_pNetSdkListener=pListener;
		}
		UdpServer::~UdpServer()
		{
			if (m_pDataHelper)
			{
				delete m_pDataHelper;
			}
		}


		int UdpServer::Start( const char *ip,int nPort )
		{
			if (!m_pDataHelper->Is_Started())
			{
				return m_pDataHelper->Start(ip,nPort);
			}
			return 0;
		}

		int UdpServer::SendData( const char *pBuffer,int len, const char* remoteAddr, int remotePort,bool bAsync)
		{
			return m_pDataHelper->GetServer()->SendData(pBuffer,len,remoteAddr,remotePort,bAsync);
		}

		void UdpServer::Stop()
		{
			if (m_pDataHelper->Is_Started())
			{
				m_pDataHelper->GetServer()->StopIoService();
				m_pDataHelper->Stop();
			}
		}

	}
}

