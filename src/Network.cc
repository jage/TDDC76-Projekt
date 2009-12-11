#include "Network.h"
#include <time.h>
#include <iostream>
#include <string>
#ifdef WITH_NETWORK
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include "SDLInclude.h"

using boost::asio::ip::tcp;
#endif

using namespace std;

#ifdef WITH_NETWORK
/* Connection */

/*
 * Creates a new connection, returns the pointer
 */
Connection::pointer Connection::create(boost::asio::io_service& io_service)
{
	return pointer(new Connection(io_service));
}

/*
 * Returns the socket for the connection
 */
tcp::socket& Connection::socket()
{
	return socket_;
}

/*
 * Handles new connections
 * Reads the data, puts it in response_ and lets Connection::handle_read take care of it
 * Sends a connect_message to the client
 */
void Connection::start()
{
	string connect_message = "Welcome to the Panzer2k remote console\n";
	
	boost::asio::async_read_until(socket_, response_, "\n",
		boost::bind(&Connection::handle_read, shared_from_this(),
		boost::asio::placeholders::error));
	
	boost::asio::async_write(socket_, boost::asio::buffer(connect_message),
		boost::bind(&Connection::handle_write, shared_from_this(),
		boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred));
	
}
	
/*
 * Connection construction, sets io_service
 */
Connection::Connection(boost::asio::io_service& io_service)
	: socket_(io_service),
	  strand_(io_service) {}

/*
 * Nothing to to really, no new messages to push out
 */
void Connection::handle_write(const boost::system::error_code&, size_t) {}

/*
 * Passes the response on to the static callback function
 */
void Connection::handle_read(const boost::system::error_code&)
{	
	Network::callback(response_);
}

/* Server */

/*
 * Server Constructor
 */
Server::Server(boost::asio::io_service& io_service, const string port)
	: acceptor_(io_service, tcp::endpoint(tcp::v4(), atoi(port.c_str()))),
	  strand_(io_service)
{
	start_accept();
}

/*
 * Start accepting a connection
 */
void Server::start_accept()
{
	Connection::pointer new_connection = 
		Connection::create(acceptor_.io_service());

	acceptor_.async_accept(new_connection->socket(),
		strand_.wrap(boost::bind(&Server::handle_accept, this, new_connection,
		boost::asio::placeholders::error)));
}

/*
 * Handle a new connection, then run start_accept again for the next connection
 */
void Server::handle_accept(Connection::pointer new_connection,
	const boost::system::error_code& error)
{
	if (!error)
	{
		new_connection->start();
		start_accept();
	}
}
#endif

/*
 * Network, abstraction for server and client.
 * Server uses the Connection class for each new connection
 * The client is just a simple iostream, connects, sends the message, disconnects
 */

/* Constructior for Network */
Network::Network() {
#ifdef WITH_NETWORK
	boost::asio::io_service io_service_;
	Connection::pointer connection_;
	tcp::iostream stream_;
#endif
}

Network::~Network() {}

/* 
 * Listen on på 0.0.0.0:<port>
 */
void Network::listen(const string port)
{
#ifdef WITH_NETWORK
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
#endif
}

/*
 * Connects to <hostname>:<port>, sends <msg> and disconnects
 */
void Network::send(const string hostname, const string port, const string msg)
{
#ifdef WITH_NETWORK
    tcp::iostream s(hostname, port);
	s << msg;
	s.flush();
	s.close();
#endif
}

#ifdef WITH_NETWORK
/*
 * Callback for each message recieved by Server
 * Translate strings to SDL_Events, simple and stupid.
 */
void Network::callback(boost::asio::streambuf &response_)
{
	std::istream response_stream(&response_);
	std::string msg;
	std::getline(response_stream, msg);
	std::cout << msg << "\n";
	
	// Översätter strängmeddelande till SDL_Event, emulerar tangentbord
	
	if (msg == "quit") { // Quit the opponents client. :-)
		SDL_Event event;
		event.type = SDL_QUIT;
		SDL_PushEvent(&event);
	} else if (msg == "up") { // Up arrow
		SDL_Event event;
		event.type = SDL_KEYDOWN;
		event.key.which = 0;
		event.key.state = SDL_PRESSED;
		event.key.keysym.sym = SDLK_UP;
		SDL_PushEvent(&event);
	} else if (msg == "down") { // Down arrow
		SDL_Event event;
		event.type = SDL_KEYDOWN;
		event.key.which = 0;
		event.key.state = SDL_PRESSED;
		event.key.keysym.sym = SDLK_DOWN;
		SDL_PushEvent(&event);
	} else if (msg == "enter_pressed") { // Retur, pressed
		SDL_Event event;
		event.type = SDL_KEYDOWN;
		event.key.which = 0;
		event.key.state = SDL_PRESSED;
		event.key.keysym.sym = SDLK_RETURN;
		SDL_PushEvent(&event);
	} else if (msg == "enter_released") { // Retur, released
		SDL_Event event;
		event.type = SDL_KEYUP;
		event.key.which = 0;
		event.key.state = SDL_RELEASED;
		event.key.keysym.sym = SDLK_RETURN;
		SDL_PushEvent(&event);
	}
}
#endif
