#include <iostream>
#include <ctime>
#include <vector>
#include <boost/array.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/system/system_error.hpp>
#include <boost/asio.hpp>
#include "ThreadCoreBase.h"
#include "UdpClientModel.h"






namespace BaseCore
{

	namespace Net
	{



		using namespace boost::asio;
		using namespace boost;
		using namespace boost::asio::ip;
		using namespace std;



		class UdpClient;
		class AsioUdpClient;

		class UdpClient_Helper:public BaseCore::Threads::ThreadCoreBase
		{
		public:
			UdpClient_Helper(UdpClient *pUdpClient);
			~UdpClient_Helper();
			AsioUdpClient *GetClient() {return m_pClient;}


			void Run();	
		private:
			AsioUdpClient *m_pClient;
		};



		class  AsioUdpClient
		{

			typedef AsioUdpClient		this_type;
			typedef ip::udp::endpoint endpoint_type;
			typedef ip::udp::socket socket_type;
			typedef boost::shared_ptr<socket_type> sock_pt;
			typedef vector<char>			buffer_type;


		public:
			AsioUdpClient(UdpClient*pListener);
			~AsioUdpClient();


			void Run_io_server();
			int SendData( const char *pBuffer,int len,const char *remoteIp, int remptePort,bool bAsync );
			void Hand_receive(const boost::system::error_code& error, std::size_t bytes_received);
			void Write_handler(const boost::system::system_error& error, std::size_t size);


			int StopIoService();
		private:
			boost::shared_ptr<io_service> 	 	m_spIO_Server;
			boost::shared_ptr<socket_type>		m_spSocket;
			boost::shared_ptr<vector<char> > m_spDataBuffer;
			endpoint_type	m_remot_endpoint;
			UdpClient *m_pListener;
		}; 	

		AsioUdpClient::AsioUdpClient( UdpClient*pListener ):m_spIO_Server(new io_service),m_spSocket(new socket_type(*m_spIO_Server)),m_spDataBuffer(new vector<char>(40960,0))
		{
			m_pListener=pListener;
			m_spSocket->open(udp::v4());
			m_spSocket->async_receive_from(boost::asio::buffer(*m_spDataBuffer), m_remot_endpoint,
				boost::bind(&this_type::Hand_receive, this,boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
		}

		AsioUdpClient::~AsioUdpClient()
		{
			if (m_spIO_Server)
			{
				m_spIO_Server->stop();
				m_spIO_Server.reset();
			}
			if (m_spSocket)
			{
				m_spSocket->close();
				m_spSocket.reset();
			}
		}

		void AsioUdpClient::Run_io_server()
		{
			if (m_spIO_Server)
			{
				m_spIO_Server->run();
			}
		}


		int AsioUdpClient::SendData( const char *pBuffer,int len,const char *remoteIp, int remptePort,bool bAsync )
		{
			if (m_spSocket)
			{



				if (bAsync)
				{
					m_spSocket->async_send_to(boost::asio::buffer(pBuffer,len), udp::endpoint(address::from_string(remoteIp), remptePort),
						boost::bind(&this_type::Write_handler, this, boost::asio::placeholders::error,boost::asio::placeholders::bytes_transferred));
					return 0;
				}else{
					boost::system::error_code send_error;
					int ret=m_spSocket->send_to(boost::asio::buffer(pBuffer,len), udp::endpoint(address::from_string(remoteIp), remptePort), 0, send_error);

					
					m_spSocket->async_receive_from(boost::asio::buffer(*m_spDataBuffer), m_remot_endpoint,
						boost::bind(&this_type::Hand_receive, this,boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));

					return ret;
				}
			}else{
				return -1;
			}
		}



		void AsioUdpClient::Hand_receive( const boost::system::error_code& error, std::size_t bytes_received )
		{

			if (!error || error != boost::asio::error::message_size)
			{
				if (0==bytes_received)
				{
					return ;
				}

				m_pListener->m_pNetSdkListener->OnData(&((*m_spDataBuffer)[0]),bytes_received,m_remot_endpoint.address().to_string().c_str(),m_remot_endpoint.port());
				m_spSocket->async_receive_from(boost::asio::buffer(*m_spDataBuffer), m_remot_endpoint,
					boost::bind(&this_type::Hand_receive, this,boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));

			}
		}

		void AsioUdpClient::Write_handler( const boost::system::system_error& error, std::size_t size )
		{
			m_spSocket->async_receive_from(boost::asio::buffer(*m_spDataBuffer), m_remot_endpoint,
				boost::bind(&this_type::Hand_receive, this,boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
		}

		int AsioUdpClient::StopIoService()
		{
			if (m_spIO_Server&&!m_spIO_Server->stopped())
			{
				m_spIO_Server->stop();
			}
			return 0;
		}



		UdpClient_Helper::UdpClient_Helper( UdpClient *pUdpClient )
		{
			m_pClient=new AsioUdpClient(pUdpClient);
		}


		UdpClient_Helper::~UdpClient_Helper()
		{
			if (m_pClient)
			{
				delete m_pClient;
				m_pClient=NULL;
			}
		}


		void UdpClient_Helper::Run()
		{
			m_pClient->Run_io_server();
		}


		UdpClient::UdpClient( NetSdkListener *pListener )
		{
			m_pDataHelper=new UdpClient_Helper(this);
			m_pNetSdkListener=pListener;
		}

		UdpClient::~UdpClient( void )
		{
			Stop();	
			delete m_pDataHelper;
			m_pDataHelper=NULL;
		}

		int UdpClient::SendData( const char *pBuffer,int len, const char* remoteAddr, int remotePort,bool bAsync/*=false*/ )
		{
			return m_pDataHelper->GetClient()->SendData(pBuffer,len,remoteAddr,remotePort,bAsync);
		}

		void UdpClient::Start(std::string desc)
		{
			if (!m_pDataHelper->Is_Started())
			{
				char tmp[128]={0};
				sprintf(tmp,"udp client_helper:%s ",desc.c_str());
				m_pDataHelper->SetDesc(tmp);
				m_pDataHelper->Start();
			}
		}

		void UdpClient::Stop()
		{
			if (m_pDataHelper->Is_Started())
			{
				m_pDataHelper->GetClient()->StopIoService();
				m_pDataHelper->Stop();
			}
		}


	}

}

