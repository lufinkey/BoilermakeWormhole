
#include <SFML/Network.hpp>
#include "../AppEngine/Util/ArrayList.h"

#pragma once

namespace Wormhole
{
	class Client
	{
	private:
		static ArrayList<sf::TcpSocket*> sockets;

	public:
		static sf::Socket::Status connect(const sf::IpAddress& ipAddress, unsigned short port);
	};
}