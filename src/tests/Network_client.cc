#include "../Network.h"
#include <string>
#include <iostream>

using namespace std;

int main() {	
	Network client;
	
	if(client.connect("localhost", "12345"))
		client.send("tutuuuuuuut");
	else
		cout << "Connection failed\n";
		
	client.disconnect();
	
	return 0;
}