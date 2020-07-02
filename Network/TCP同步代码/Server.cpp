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


using namespace boost::asio;
using namespace boost;
using namespace boost::system;
using namespace std;

int main()
{

	cout << "server begin" << endl;

	io_service ios;

	ip::tcp::acceptor acceptor(ios, ip::tcp::endpoint(ip::tcp::v4(), 6688));
	cout << acceptor.local_endpoint().address() << endl;
	while (true)
	{
		ip::tcp::socket sock(ios);

		acceptor.accept(sock);
		cout << "client:";
		cout << sock.remote_endpoint().address() << endl;
		sock.write_some(buffer("hello asio"));
	}


	return 0;
}
