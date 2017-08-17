#include <SFML\Network.hpp>
#include <iostream>
#include <Windows.h>
#include "Server.hpp"

#define START_PORT 1024

int main(int argc, char *argv[])
{
	Server server(START_PORT);
	server.InIt(true);
	while (true)
	{	
		server.Main();
		Sleep(10);
	}
	return 0;
}