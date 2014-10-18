
#include "Client.h"

namespace Wormhole
{
	ArrayList<sf::TcpSocket*> Client::sockets = ArrayList<sf::TcpSocket*>();

	sf::Socket::Status Client::connect(const sf::IpAddress& ipAddress, unsigned short port)
	{
		sf::TcpSocket* socket = new sf::TcpSocket();
		sf::Socket::Status status = socket->connect(ipAddress, port, sf::milliseconds(10000));
		if(status == sf::Socket::Done)
		{
			sockets.add(socket);
		}
		else
		{
			delete socket;
		}
		return status;
	}


}