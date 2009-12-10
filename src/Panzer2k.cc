#include "GameEngine.h"
#include "Network.h"
#include <boost/thread.hpp>


void start_network() {
	Network server;
	server.listen("12346");
}

int main(int argc, char* args[])
{
	boost::thread t1(boost::bind(&start_network));
	GameEngine GE;
	GE.run();
	t1.join();
	return 0;
}
