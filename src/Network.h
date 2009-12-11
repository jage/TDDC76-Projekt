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
		static boost::shared_ptr<Connection> create(boost::asio::io_service& io_service);
		boost::asio::ip::tcp::socket& socket();
		void start();
	private:
		Connection(boost::asio::io_service& io_service);
		void handle_write(const boost::system::error_code&, size_t);
		void handle_read(const boost::system::error_code&);
		boost::asio::ip::tcp::socket socket_;
		boost::asio::streambuf response_;
		boost::asio::strand strand_;
};

class Server {
	public:
		Server(boost::asio::io_service& io_service, const string port);
		void send();
	private:
		void start_accept();
		void handle_accept(Connection::pointer new_connection, const boost::system::error_code&);
		boost::asio::ip::tcp::acceptor acceptor_;
		boost::asio::strand strand_;
};
#endif

class Network {
	public:
		Network();
		~Network();
		void listen(const string);
		static void send(const string, const string, const string);
#ifdef WITH_NETWORK
		static void callback(boost::asio::streambuf&);
	private:
		boost::asio::io_service io_service_;
		boost::thread connection_thread_;
		Connection::pointer connection_;
		boost::asio::ip::tcp::iostream stream_;
#endif
};

#endif