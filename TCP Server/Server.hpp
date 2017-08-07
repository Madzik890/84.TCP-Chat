#pragma once
#include <SFML\Network.hpp>
#include <string>
#include <deque>

#ifndef SERVER_HPP
#define SERVER_HPP

#define default_port 1024;

class Server
{
protected:
	sf::Thread * main_th;//thread for main server function
	sf::TcpListener listener;//listener for socket
	sf::TcpSocket socket;//tcp socket 
	const int datasize = 100; //data block size
	char data[100] = "..."; // create data block
	unsigned int received;//int of recived blocks

public:
	Server(unsigned long long port);//constructor
	Server();//default constructor
	~Server();//destructor

	void Main() { main_th->launch(); }

	void setPort(unsigned long long port) { this->port = port; }
	unsigned long long getPort() { return port; }
private:
	struct Clients
	{
	protected:
		std::string ip;//if of client
		std::string nickname;//nickname
		unsigned long long port = default_port;//port of client
	public:
		Clients(std::string ip, unsigned long long port, std::string nickname) :ip(ip), nickname(nickname), port(port) {};//constructor
		std::string getIP() { return ip; }
		std::string getNickname() { return nickname; }
	};

	unsigned long long port = default_port;//port of server

	std::deque<Clients>clients;

	void main();//main stuff function
};

#endif