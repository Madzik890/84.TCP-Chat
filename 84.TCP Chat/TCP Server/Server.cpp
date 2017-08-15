#include "Server.hpp"
#include <iostream>
#include <SFML\Network.hpp>
#include <windows.h>

Server::Server(unsigned long long port):port(port)
{
	listener.setBlocking(false);//disable blocking program
	clients.push_back(Clients());
}

Server::Server()
{
	listener.setBlocking(false);//disable blocking program
	clients.push_back(Clients());
}

Server::~Server()
{
	socket.disconnect();//releasing port
}

bool Server::InIt(bool try_find)
{
	if (try_find == true)
		return port_find();
	else
		return port_setup();
}

bool Server::port_find()//function searching a free port and setuping TCP listener
{
	retry://if cannot find port try use ++port
	if (listener.listen(port) == sf::Socket::Done)//if port is free return true else false
	{
		std::cout << "Server started on port: " << port << std::endl;//message about port
		return true;
	}
	else
	{
		++port;//addition for try higher port
		goto retry;//goto
	}
}

bool Server::port_setup()
{
	if (listener.listen(port) == sf::Socket::Done)//if port is free return true else false
	{
		std::cout << "Server started on port: " << port << std::endl;//message about port
		return true;
	}
	else
		return false;
}

void Server::main()//main stuff function
{
	mutex.lock();
	for (auto &it_clients : clients)
	{
		const int datasize = 100; //data block size
		char data[100] = ""; // create data block
		unsigned int received;//int of received blocks
		sf::err().rdbuf(NULL);//turn off SFML waring
		if (it_clients.socket->receive(data, datasize, received) == sf::Socket::Done)//receiving data from client
		{
			std::string temp = data;//temp string only for finding sentence

			if (!it_clients.nickWasSet() && temp.find("$#@!set_nick:") != std::string::npos)//if nick wasn't set and found set nickname command
			{
				it_clients.setNickname(temp.substr(13, temp.size()));//setting nickname for user
				std::cout << "User " << it_clients.socket->getRemoteAddress() << ":" << it_clients.socket->getRemotePort() << " now is " << it_clients.getNickname() << std::endl;//communicate status 
			}
			else
			{
				send_to_other(data,it_clients);//sending to other message
				std::cout << "Received '" << data << "' from: " << it_clients.socket->getRemoteAddress().toString() <<":"<< it_clients.socket->getRemotePort() << std::endl;//drawing message on serve log
			}
		}
	}
	mutex.unlock();
}

void Server::send_to_other(char data[100],Clients &client)//function witch sending message to other users
{
	for (auto &it_client : clients)
	{
		if (it_client.socket->getRemotePort() != client.socket->getRemotePort())//checking whether user isn't this same who send message
		{
			std::string string = client.getNickname() + ":" + data;
			it_client.socket->send(string.c_str(),string.size());
		}
	}
}

void Server::find_connection()//function awaiting for new connection
{
	mutex.lock();
	if (listener.accept(*clients.back().socket) == sf::Socket::Done)
	{
		//creating new user
		clients.back().setIP(clients.back().socket->getRemoteAddress().toString());
		clients.back().setPort(clients.back().socket->getRemotePort());
		std::cout << "Someone connected with ip: " << clients.back().getIP() << " and port: " << clients.back().getPort() << std::endl;
		clients.push_back(Server::Clients());//add new user
	}
	mutex.unlock();
}
