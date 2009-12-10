#include "../Network.h"
#include <string>
#include <iostream>

using namespace std;

int main() {	
	Network client;
	
	client.connect("localhost", "12345");
	// client.disconnect();
	
	return 0;
}