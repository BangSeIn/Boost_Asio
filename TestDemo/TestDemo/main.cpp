#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;

int main() {
	try {
		//Basically, Boost Asio program has one IO Service Object
		boost::asio::io_service io_service;
		//Use Resolver to change Domain's name as TCP Iterator
		tcp::resolver resolver(io_service);
		//Use localhost as Server, and daytime protocol as Servie
		tcp::resolver::query query("localhost", "daytime");
		//Get IP address and Port number through DNS
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
		//Initiate Socket and connect to Server
		tcp::socket socket(io_service);
		boost::asio::connect(socket, endpoint_iterator);
		while (1) {
			//Define Buffer and Error process variable
			boost::array<char, 128> buf;
			boost::system::error_code error;
			//Receive Data from Server using buffer
			size_t len = socket.read_some(boost::asio::buffer(buf), error);
			if (error == boost::asio::error::eof)
				break;
			else if (error)
				throw boost::system::system_error(error);
			//Show data in buffer on scereen
			cout.write(buf.data(), len);
		}
	}
	catch (exception & e) {
		cerr << e.what() << endl;
	}
	system("pause");
	return 0;
}