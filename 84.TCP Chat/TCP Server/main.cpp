#include <SFML\Network.hpp>
#include <iostream>
#include "Server.hpp"

#define START_PORT 1024

int main(int argc, char *argv[])
{
	Server server(START_PORT);
	server.InIt(true);
	while (true)
	{	
		server.Main();
	}
	return 0;
}