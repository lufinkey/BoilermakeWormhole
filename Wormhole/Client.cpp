
#include "Client.h"
#include "String.h"
#include "../AppEngine/Output/Console.h"

namespace Wormhole
{
	ArrayList<sf::TcpSocket*> Client::sockets = ArrayList<sf::TcpSocket*>();

    void Client::startBroadcast()
    {
        if (broadcasting)
        {
            broadcastSocket.bind(8008);

            broadcastThread = new sf::Thread(&Client::threadBroadcast, this);
            broadcastThread.launch();
        }
        else
        {
            Console::WriteLine("Already broadcasting");
        }
    }

    void Client::threadBroadcast()
    {
        while (true)
        {
            sf::sleep(sf::millisecond(15000));
            String identity = sf::IpAddress::getLocalAddress().toString();
            broadcastSocket.send((const char*)identity, identity.length() + 1, sf::IpAddress::Broadcast, 8009);
        }
    }

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
