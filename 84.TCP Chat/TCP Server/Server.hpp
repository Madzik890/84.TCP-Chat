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
		std::string nickname = "default";//nickname user
		bool nickname_was_set = false;
		bool disconnected = false;
	public:
		Clients() :socket(new sf::TcpSocket) { socket->setBlocking(false);/*disable blocking socket*/ };//constructor
		Clients(Clients&& source) :socket(std::move(source.socket)) { socket->setBlocking(false); /*disable blocking socket*/  };//move constructor
		Clients& operator= (Clients&& source) { socket = std::move(source.socket); socket->setBlocking(false); /*disable blocking socket*/ return *this; };// Move assignment operator

		sf::Clock clock;//clock for checking away from keyboard client | if user is ask longer than 5 minute,server disconnecting him 
		std::unique_ptr<sf::TcpSocket> socket;//unique_ptr of socket
		std::string getNickname() { return nickname; }//returning nickname
		bool nickWasSet() { return nickname_was_set; }//returning status of nickname
		bool wasDisconnected() { return disconnected; };//returning status of connection
		int  getAFK() { return afk_minute; }//returning number minute afk
		void disconnect() { char temp[] = "$#@!disconnect"; socket->send(temp, sizeof(temp)); socket->disconnect(); disconnected = true; }//disconnect client from server
		void setNickname(std::string nickname) { this->nickname = nickname; nickname_was_set = true; }//setting new nickname
		void addMinuteAFK() { ++afk_minute; };//increase minute of afk
		void zeroMinuteAFK() { afk_minute = 0; }//reset variable afk_minute
	private:
		unsigned int afk_minute = 0;//minute of non message
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