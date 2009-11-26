#ifndef NETWORK_H_
#define NETWORK_H_

#include <string>

using namespace std;

class Network {
	public:
		Network();
		bool connect(const string, const int);
		void listen(const string, const int);
		bool disconnect();
		bool is_active();
		void send(const string message);
		void callback();
};


#endif