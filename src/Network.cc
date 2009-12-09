#include "Network.h"
#include <time.h>
#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;

Connection::pointer Connection::create(boost::asio::io_service& io_service)
{
	return pointer(new Connection(io_service));
}

tcp::socket& Connection::socket()
{
	return socket_;
}

void Connection::start()
{
	message_ = "Welcome!\n";
	
	boost::asio::async_read_until(socket_, response_, "\n",
		boost::bind(&Connection::handle_read, shared_from_this(),
		boost::asio::placeholders::error));
	
	boost::asio::async_write(socket_, boost::asio::buffer(message_),
		boost::bind(&Connection::handle_write, shared_from_this(),
		boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred));
	
	boost::asio::async_write(socket_, boost::asio::buffer("> "),
   		boost::bind(&Connection::handle_write, shared_from_this(),
   		boost::asio::placeholders::error,
   		boost::asio::placeholders::bytes_transferred));
}
	
Connection::Connection(boost::asio::io_service& io_service)
	: socket_(io_service),
	  strand_(io_service)
{
}

void Connection::handle_write(const boost::system::error_code& /*error*/,
	size_t /*bytes_transferred*/)
{
}

void Connection::handle_read(const boost::system::error_code&)
{	
	Network::callback(response_);
	boost::asio::async_read_until(socket_, response_, "\n",
	        strand_.wrap(boost::bind(&Connection::handle_read, shared_from_this(),
	        boost::asio::placeholders::error)));
}

void Connection::send() {
	boost::asio::async_write(socket_, boost::asio::buffer("Weeeeeeeeeeeeeeeeeee!"),
   		strand_.wrap(boost::bind(&Connection::handle_write, shared_from_this(),
   		boost::asio::placeholders::error,
   		boost::asio::placeholders::bytes_transferred)));
}

Server::Server(boost::asio::io_service& io_service)
	: acceptor_(io_service, tcp::endpoint(tcp::v4(), 12345)),
	  strand_(io_service)
{
	start_accept();
}

Connection::pointer Server::connection() {
	return new_connection;
}

void Server::start_accept()
{
	Connection::pointer new_connection =
		Connection::create(acceptor_.io_service());

	acceptor_.async_accept(new_connection->socket(),
		strand_.wrap(boost::bind(&Server::handle_accept, this, new_connection,
		boost::asio::placeholders::error)));
}

void Server::handle_accept(Connection::pointer new_connection,
	const boost::system::error_code& error)
{
	if (!error)
	{
		new_connection->start();
		start_accept();
	}
}

/*
* Antingen lyssnar eller ansluter man
*/

/* Konstruktor för Network */
Network::Network() {
	boost::asio::io_service io_service_;
	Connection::pointer connection_;
}

Network::~Network() {}

bool Network::connect(const string hostname, const string port)
{
	try {
	}
	catch (exception& e)
	{
		cerr << e.what() << "\n";
	}

	return true;
}

void Network::listen(const string port)
{
	try
	{
		cout << "Listening on " << port << "\n";

		Server server(io_service_);		
		
		boost::thread t1(boost::bind(&boost::asio::io_service::run, &io_service_));
		boost::thread t2(boost::bind(&send, &server));
		
	  	io_service_.run();
		t1.join();
		t2.join();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}


bool Network::disconnect()
{
	return true;
}

bool Network::is_active()
{
	return true;
}

void Network::send(Server* server)
{
	cout << "SEND! MOTHAFUCKA!\n";
}

void Network::callback(boost::asio::streambuf &response_)
{
	std::istream response_stream(&response_);
	std::string msg;
	std::getline(response_stream, msg);
	std::cout << msg << "\n";
}
