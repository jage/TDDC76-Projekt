#ifndef NETWORK_H_
#define NETWORK_H_

#include <string>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

using namespace std;


// class Connection
// : public boost::enable_shared_from_this<Connection>
// {
// 	public:
// 		typedef boost::shared_ptr<Connection> pointer;
// 		static boost::shared_ptr<Connection> create(boost::asio::io_service& io_service);
// 		boost::asio::ip::tcp::socket& socket();
// 		void start();
// 	private:
// 		Connection(boost::asio::io_service& io_service);
// 		void handle_write(const boost::system::error_code&, size_t);
// 		void handle_read(const boost::system::error_code&);
// 		boost::asio::ip::tcp::socket socket_;
// 		std::string message_;
// 		boost::asio::streambuf response_; // NOT IN USE!
// 		boost::asio::strand strand_;
// };

// class Server {
// 	public:
// 		Server(boost::asio::io_service& io_service);
// 	private:
// 		void start_accept();
// 		void handle_accept(Connection::pointer);
// 		boost::asio::ip::tcp::acceptor acceptor_;
// 		boost::asio::strand strand_;
// };


class Network {
	public:
		Network();
		~Network();
		bool connect(const string, const string);
		void listen(const string);
		bool disconnect();
		bool is_active();
		void send(const string);
		void callback();
	private:
		// void start_accept();
		// void handle_accept(Connection::pointer);
		boost::asio::io_service io_service_;
		boost::thread connection_thread_;
};

#endif