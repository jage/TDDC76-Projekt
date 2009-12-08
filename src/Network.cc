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

class Connection
	: public boost::enable_shared_from_this<Connection>
{
public:
	typedef boost::shared_ptr<Connection> pointer;

	static pointer create(boost::asio::io_service& io_service)
	{
		return pointer(new Connection(io_service));
	}

	tcp::socket& socket()
	{
		return socket_;
	}

	void start()
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
	
	void send(string msg)
	{
		boost::asio::async_write(socket_, boost::asio::buffer(msg),
	   		boost::bind(&Connection::handle_write, shared_from_this(),
	   		boost::asio::placeholders::error,
	   		boost::asio::placeholders::bytes_transferred));
	}

private:
	Connection(boost::asio::io_service& io_service)
		: socket_(io_service),
		  strand_(io_service)
	{
	}

	void handle_write(const boost::system::error_code& /*error*/,
		size_t /*bytes_transferred*/)
	{
	}

	void handle_read(const boost::system::error_code&)
	{
		std::istream response_stream(&response_);
		std::string msg;
		std::getline(response_stream, msg);
		
		if(msg != "quit") {
			std::cout << msg << "\n";
			boost::asio::async_read_until(socket_, response_, "\n",
				strand_.wrap(boost::bind(&Connection::handle_read, shared_from_this(),
				boost::asio::placeholders::error)));
			boost::asio::async_write(socket_, boost::asio::buffer("> "),
		   		strand_.wrap(boost::bind(&Connection::handle_write, shared_from_this(),
		   		boost::asio::placeholders::error,
		   		boost::asio::placeholders::bytes_transferred)));
		}
		else
		{
			boost::asio::async_write(socket_, boost::asio::buffer("Bye!\n"),
		   		strand_.wrap(boost::bind(&Connection::handle_write, shared_from_this(),
		   		boost::asio::placeholders::error,
		   		boost::asio::placeholders::bytes_transferred)));
			
		}
	}

	tcp::socket socket_;
	std::string message_;
	boost::asio::streambuf response_;
	boost::asio::strand strand_;
};

class Server
{
public:
	Server(boost::asio::io_service& io_service)
		: acceptor_(io_service, tcp::endpoint(tcp::v4(), 12345)),
		  strand_(io_service)
	{
		start_accept();
	}

private:
	void start_accept()
	{
		Connection::pointer new_connection =
			Connection::create(acceptor_.io_service());

		acceptor_.async_accept(new_connection->socket(),
			strand_.wrap(boost::bind(&Server::handle_accept, this, new_connection,
			boost::asio::placeholders::error)));
	}

	void handle_accept(Connection::pointer new_connection,
		const boost::system::error_code& error)
	{
		if (!error)
		{
			new_connection->start();
			start_accept();
		}
	}

	tcp::acceptor acceptor_;
	boost::asio::strand strand_;
};

/*
* Antingen lyssnar eller ansluter man
*/

/* Konstruktor för Network */
Network::Network() {
	boost::asio::io_service io_service_;
	tcp::iostream stream_;
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
		boost::bind(&boost::asio::io_service::run, &io_service_);
	  	io_service_.run();
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

void Network::send(const string msg)
{
}

void Network::callback()
{

}
