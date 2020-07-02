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

	cout << "client begin" << endl;

	io_service ios;

	ip::tcp::socket sock(ios);

	ip::tcp::endpoint ep(ip::address::from_string("192.168.1.179"), 6688);

	sock.connect(ep);

	vector<char> str(100, 0);

	sock.read_some(buffer(str));

	cout << "recive from " << sock.remote_endpoint().address();

	cout << endl << &str[0] << endl;


	return 0;
}