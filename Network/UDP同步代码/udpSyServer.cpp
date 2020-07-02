#include <iostream>
#include <ctime>
#include <boost/array.hpp>
#include<boost/array.hpp>
#include<boost/system/system_error.hpp>
#include <boost/asio.hpp>


	using namespace boost::asio::ip;

	void udp_sy_server()
	{
		try
		{
			boost::asio::io_service io;
			udp::socket socket(io, udp::endpoint(udp::v4(), 6677));

			for (;;)
			{
				boost::array<char, 1> rec_buf;
				boost::system::error_code error;
				udp::endpoint remote_endpoint;
				std::cout << " run here " << std::endl;
				socket.receive_from(boost::asio::buffer(rec_buf), remote_endpoint, 0, error);//
				std::cout << " run here 1" << std::endl;
				if (error && error != boost::asio::error::message_size)
					throw boost::system::system_error(error);

				time_t now = std::time(0);
				std::string message = std::ctime(&now);
				boost::system::error_code ignore_error;
				socket.send_to(boost::asio::buffer(message), remote_endpoint, 0, ignore_error);
			}
		}
		catch (std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}


int main()
{
	udp_sy_server();
	return 0;
}

