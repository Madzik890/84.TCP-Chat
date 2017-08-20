#include <SFML\Network.hpp>
#include <iostream>
#include <Windows.h>
#include "Server.hpp"

#define START_PORT 1024

int main(int argc, char *argv[])
{
	Server server(START_PORT);
	server.InIt(true);
	sf::Clock clock;

	while (true)
	{	
		if (clock.getElapsedTime().asSeconds() >= 1 / 60)//Network service checked every 1/60 sec.
		{
			server.Main();
			clock.restart();
		}
	}
	return 0;
}