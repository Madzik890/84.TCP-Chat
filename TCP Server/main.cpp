#include <SFML\Network.hpp>
#include <iostream>

#define PORT_IN 1024

int main()
{
	sf::TcpListener listener;
	sf::TcpSocket socket;
	sf::Packet packet;

	if (listener.listen(PORT_IN) != sf::Socket::Done)
		return 1;

	const int datasize = 100; // rozmiar bloku danych
	char data[100] = "..."; // tworzymy blok danych
	unsigned int received;
	while (true)
	{
		if (listener.accept(socket) == sf::Socket::Done)
			std::cout << "Someone connected" << socket.getRemoteAddress() << std::endl;
		if (socket.receive(data, datasize, received) == sf::Socket::Done) // i wysy³amy...
		{
			// nie mo¿na odebraæ danych (prawdopodobnie klient/serwer siê roz³¹czy³)
			//char * test = "";
			//packet >> test;
			std::cout <<"Odebrano " << data <<" od: "<<socket.getRemoteAddress().toString() << std::endl;
		}

	}


	socket.disconnect();
	system("pause");
	return 0;
}