#include "../Network.h"
#include <string>

int main() {
	Network server;
	server.listen("12345");

	return 0;
}