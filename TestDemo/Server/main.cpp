#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;

//return Server's date and time information
string make_daytime_string() {
	time_t now = time(0);
	return ctime(&now);
}

int main() {
	try {
		//Basically, Boost Asio program has one IO Service object
		boost::asio::io_service io_service;
		//Create passive socket recieves connection from 13th port of TCP protocol
		tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 13));
		//Repeat infinitely for all clients
		while (1) {
			//Create socket and wait connection
			tcp::socket socket(io_service);
			acceptor.accept(socket);	
			//When Connection success, Create message to send to client.
			string message = make_daytime_string();
			//Send message to client
			boost::system::error_code ignored_error;
			boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
		}
	}
	catch(exception & e) { 
		//If error occurs, Show error message
		cerr << e.what() << endl;
	}
	return 0;
}