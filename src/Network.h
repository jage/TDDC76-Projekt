#ifndef NETWORK_H_
#define NETWORK_H_

#include <string>
#include <boost/asio.hpp>

using namespace std;

class Network {
	public:
		Network();
		bool connect(const string, const string);
		void listen(const string);
		bool disconnect();
		bool is_active();
		void send(const string message);
		void callback();
	private:
		boost::asio::io_service io_service_;
		boost::asio::ip::tcp::iostream stream_;	
};


#endif