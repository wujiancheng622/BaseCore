#include <iostream>
#include <ctime>
#include <boost/array.hpp>
#include<boost/array.hpp>
#include<boost/system/system_error.hpp>
#include <boost/asio.hpp>



	using namespace boost::asio::ip;
	const int MaxSize = 1024;

	void udp_sy_client()
	{
		try
		{
			boost::asio::io_service io;
			udp::resolver resolver(io);
			udp::resolver::query query(udp::v4(), "localhost", "6677");//protocol type , ip , port
			udp::endpoint resolver_endpoint(address::from_string("192.168.1.178"), 6677);

			std::cout<<"1"<<std::endl;

			udp::socket socket(io);
			socket.open(udp::v4());
			boost::array<char, 1> buf = { { 0 } };
			socket.send_to(boost::asio::buffer(buf), resolver_endpoint);

			std::cout<<"2"<<std::endl;

			boost::array<char, MaxSize> recive_buf;
			char tmp[256]={0};
			udp::endpoint send_endpoint;

			std::cout<<"3"<<std::endl;


			size_t len = socket.receive_from(boost::asio::buffer(tmp,256), send_endpoint);

			std::cout<<"tmp:"<<tmp<<std::endl;

			std::cout<<"4"<<std::endl;


			std::cout.write(recive_buf.data(), len);
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}



int main()
{
	udp_sy_client();
	return 0;
}

