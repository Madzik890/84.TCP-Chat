#include "Server.hpp"

sf::Mutex mutex;//default mutex for server thread

Server::Server(unsigned long long port):port(port)
{
	main_th = new sf::Thread(&main);//creating new thread 
}

Server::Server()
{
	main_th = new sf::Thread(&main);//creating new thread 
}

Server::~Server()
{
	delete main_th;//exemption memory
}

void Server::main()//server stuff
{
	mutex.lock;
	
	mutex.unlock();
}

