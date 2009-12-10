#include "Network.h"
#include <time.h>
#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include "SDLInclude.h"

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
}

Server::Server(boost::asio::io_service& io_service, const string port)
	: acceptor_(io_service, tcp::endpoint(tcp::v4(), atoi(port.c_str()))),
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
	tcp::iostream stream_;
}

Network::~Network() {}

// Ansluter inte i den här implementationen med iostream, 
//   utan sätter bara hostname och port
bool Network::connect(const string hostname, const string port)
{
	hostname_ = hostname;
	port_ = port;

	return true;
}

// Lyssnar på 0.0.0.0:<port>
void Network::listen(const string port)
{
	try
	{
		cout << "Listening on " << port << "\n";
		Server server(io_service_, port);		
	  	io_service_.run();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}


// Används inte i den här implementationen med tcp::iostream
bool Network::disconnect()
{
	return true;
}

// Används inte i den här implementationen med tcp::iostream
bool Network::is_active()
{
	return true
}

// Ansluter till <hostname> och <port>, skickar <msg> och kopplar sedan från
void Network::send(const string hostname, const string port, const string msg)
{
    tcp::iostream s(hostname, port);
	s << msg;
	s.flush();
	s.close();
}

// Funktion som körs för varje meddelande servern tar emot
void Network::callback(boost::asio::streambuf &response_)
{
	std::istream response_stream(&response_);
	std::string msg;
	std::getline(response_stream, msg);
	std::cout << msg << "\n";
	
	// Översätter strängmeddelande till SDL_Event, emuleror tangentbord
	
	if (msg == "quit") { // Om man håller på och förlorar, skicka en quit till motståndaren! :-)
		SDL_Event event;
		event.type = SDL_QUIT;
		SDL_PushEvent(&event);
	} else if (msg == "up") {
		SDL_Event event;
		event.type = SDL_KEYDOWN;
		event.key.which = 0;
		event.key.state = SDL_PRESSED;
		event.key.keysym.sym = SDLK_UP;
		SDL_PushEvent(&event);
	} else if (msg == "down") {
		SDL_Event event;
		event.type = SDL_KEYDOWN;
		event.key.which = 0;
		event.key.state = SDL_PRESSED;
		event.key.keysym.sym = SDLK_DOWN;
		SDL_PushEvent(&event);
	} else if (msg == "enter") {
		SDL_Event event;
		event.type = SDL_KEYDOWN;
		event.key.which = 0;
		event.key.state = SDL_PRESSED;
		event.key.keysym.sym = SDLK_RETURN;
		SDL_PushEvent(&event);
		event.type = SDL_KEYUP;
		event.key.which = 0;
		event.key.state = SDL_RELEASED;
		event.key.keysym.sym = SDLK_RETURN;
		SDL_PushEvent(&event);
	}
}
