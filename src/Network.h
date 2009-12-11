#ifndef NETWORK_H_
#define NETWORK_H_

#include <string>
#ifdef WITH_NETWORK
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#endif

using namespace std;

#ifdef WITH_NETWORK
class Connection
: public boost::enable_shared_from_this<Connection>
{
	public:
		typedef boost::shared_ptr<Connection> pointer;
		/*
		 * Creates a new connection, returns the pointer
		 */
		static boost::shared_ptr<Connection> create(boost::asio::io_service& io_service);
		/*
		 * Returns the socket for the connection
		 */
		boost::asio::ip::tcp::socket& socket();
		/*
		 * Handles new connections
		 * Reads the data, puts it in response_ and lets Connection::handle_read take care of it
		 * Sends a connect_message to the client
		 */
		void start();
	private:
		/*
		 * Connection construction, sets io_service
		 */
		Connection(boost::asio::io_service& io_service);
		/*
		 * Nothing to to really, no new messages to push out
		 */
		void handle_write(const boost::system::error_code&, size_t);
		/*
		 * Passes the response on to the static callback function
		 */
		void handle_read(const boost::system::error_code&);
		boost::asio::ip::tcp::socket socket_;
		boost::asio::streambuf response_;
		boost::asio::strand strand_;
};

class Server {
	public:
		/*
		 * Server Constructor
		 */
		Server(boost::asio::io_service& io_service, const string port);
	private:
		/*
		 * Start accepting a connection
		 */
		void start_accept();
		/*
		 * Handle a new connection, then run start_accept again for the next connection
		 */
		void handle_accept(Connection::pointer new_connection, const boost::system::error_code&);
		boost::asio::ip::tcp::acceptor acceptor_;
		boost::asio::strand strand_;
};
#endif

/*
 * Network, abstraction for server and client.
 * Server uses the Connection class for each new connection
 * The client is just a simple iostream, connects, sends the message, disconnects
 */
class Network {
	public:
		/* Constructior for Network */
		Network();
		~Network();
		/* 
		 * Listen on på 0.0.0.0:<port>
		 */
		void listen(const string);
		/*
		 * Connects to <hostname>:<port>, sends <msg> and disconnects
		 */
		static void send(const string, const string, const string);
#ifdef WITH_NETWORK
		/*
		 * Callback for each message recieved by Server
		 * Translate strings to SDL_Events, simple and stupid.
		 */
		static void callback(boost::asio::streambuf&);
	private:
		boost::asio::io_service io_service_;
		boost::thread connection_thread_;
		Connection::pointer connection_;
		boost::asio::ip::tcp::iostream stream_;
#endif
};

#endif
