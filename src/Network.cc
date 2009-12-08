#include "Network.h"
#include <string>
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;

/*
 * Antingen lyssnar eller ansluter man
 */

/* Konstruktor för Network */
Network::Network() {
	boost::asio::io_service io_service_;
	tcp::iostream stream_;
}

bool Network::connect(const string hostname, const string port)
{
	try {
		cout << "C: Connecting to " << hostname << ":" << port << "\n";
		tcp::iostream stream_(hostname, port);
		
		if (!stream_)
			return false;
			
		cout << "C: Sending " << "Ping?" << "\n";
		stream_ << "Ping?" << "\n";
		stream_.close();	
	}
	catch (exception& e)
	{
		cerr << e.what() << "\n";
	}
	
	return true;
}

void Network::listen(const string port)
{
	cout << "S: Listing on " << port << "\n";
	
	try {
    	tcp::endpoint endpoint(tcp::v4(), atoi(port.c_str()));
    	tcp::acceptor acceptor(io_service_, endpoint);
		
		for (;;)
		{
			acceptor.accept(*stream_.rdbuf());
			string response_line;
			while(getline(stream_, response_line));
				cout << "S: Recieving " << response_line << "\n";
			stream_.close();
		}
	}
	catch (exception& e)
	{
		cerr << e.what() << "\n";
	}
}

bool Network::disconnect()
{
	stream_.close();
	return true;
}

bool Network::is_active()
{
	return stream_.good();
}

void Network::send(const string message)
{
	if(this->is_active())
	{
		cout << "C: Sending " << message << "\n";
		stream_ << message << "\n";
		stream_.flush();
		stream_.close();
	} 
	else
	{
		cerr << "Stream not good" << "\n";
	}
}

void Network::callback()
{
	
}