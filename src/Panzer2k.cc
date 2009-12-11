#include "GameEngine.h"
#include "Network.h"
#ifdef WITH_NETWORK
#include <boost/thread.hpp>

/*
 * Start network, listens in the background in a thread
 */
void start_network() {
	Network server;
	server.listen("12346");
}
#endif

int main(int argc, char* args[])
{
#ifdef WITH_NETWORK
	boost::thread t1(boost::bind(&start_network));
#endif
	GameEngine GE;
	GE.run();
#ifdef WITH_NETWORK
	t1.join();
#endif
	return 0;
}
