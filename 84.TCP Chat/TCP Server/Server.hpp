#pragma once
#include <SFML\System.hpp>
#include <SFML\Network.hpp>
#include <string>
#include <list>//for list of clients
#include <memory>//for unique_ptr for socket

#ifndef SERVER_HPP
#define SERVER_HPP

#define default_port 1025;

class Server
{
protected:
	sf::TcpSocket socket;
	sf::TcpListener listener;//listener for socket
public:
	Server(unsigned long long port);//constructor
	Server();//default constructor
	~Server();//destructor

	bool InIt(bool try_find);//set up TCP architecture 
	void Main() { mutex.lock(); main(); find_connection(); mutex.unlock(); }

	void setPort(unsigned long long port) { this->port = port; }
	const unsigned long long getPort() { return port; }
private:
	struct Clients
	{
	protected:
		std::string ip;//if of client
		std::string nickname = "default";//nickname user
		unsigned long long port = port;//port of client
		bool nickname_was_set = false;
	public:
		Clients(std::string ip, unsigned long long port) :socket(new sf::TcpSocket), ip(ip), port(port) { socket->setBlocking(false); /*disable blocking socket*/ };//constructor
		Clients() :socket(new sf::TcpSocket) { socket->setBlocking(false);/*disable blocking socket*/ };//copy constructor
		Clients(Clients&& source) :socket(std::move(source.socket)) { socket->setBlocking(false); /*disable blocking socket*/  };//move constructor
		Clients& operator= (Clients&& source) { socket = std::move(source.socket); socket->setBlocking(false); /*disable blocking socket*/ return *this; };// Move assignment operator

		
		std::unique_ptr<sf::TcpSocket> socket;//unique_ptr of socket
		const std::string getIP() { return ip; }//returning port
		std::string getNickname() { return nickname; }//returning nickname
		bool nickWasSet() { return nickname_was_set; }//returning status of nickname
		unsigned long long getPort() { return port; }//returning port
		void setIP(std::string string) { this->ip = string; }//setting new ip
		void setPort(unsigned long long port) { this->port = port; }//setting new port
		void setNickname(std::string nickname) { this->nickname = nickname; nickname_was_set = true; }//setting new nickname
	};

	unsigned long long port = default_port;//port of server
	std::list<Clients>clients;//list of clients
	sf::Mutex mutex;//default mutex for server thread
	void main();//main stuff function
	void send_to_other(char data[100],Clients &client);//function used to send received data to other users
	void find_connection();//function awaiting for new connection
	bool port_find();//function searching a free port and setuping TCP listener
	bool port_setup();//setuping TCP listener
};

#endif