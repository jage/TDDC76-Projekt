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
		std::string message_;
		boost::asio::streambuf response_; // NOT IN USE!
		boost::asio::strand strand_;
};

class Server {
	public:
		Server(boost::asio::io_service& io_service, const string port);
		Connection::pointer connection();
		void send();
	private:
		void start_accept();
		void handle_accept(Connection::pointer new_connection, const boost::system::error_code&);
		boost::asio::ip::tcp::acceptor acceptor_;
		boost::asio::strand strand_;
		Connection::pointer new_connection;
};
#endif

class Network {
	public:
		Network();
		~Network();
		bool connect(const string, const string);
		void listen(const string);
		bool disconnect();
		bool is_active();
		static void send(const string, const string, const string);
#ifdef WITH_NETWORK
		static void callback(boost::asio::streambuf&);
	private:
		// void start_accept();
		// void handle_accept(Connection::pointer);
		boost::asio::io_service io_service_;
		boost::thread connection_thread_;
		Connection::pointer connection_;
		boost::asio::ip::tcp::iostream stream_;
		string hostname_;
		string port_;
#endif
};

#endif
