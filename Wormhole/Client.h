
#include <SFML/Network.hpp>
#include "../ArrayList.h"

#pragma once

namespace Wormhole
{
	class Client
	{
	private:
		static ArrayList<sf::TcpSocket*> sockets;

	public:
		sf::Socket::Status connect(const sf::IpAddress& ipAddress, unsigned short port);
	};
}