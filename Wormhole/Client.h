
#include <SFML/Network.hpp>
#include <SFML/System/Thread.hpp>
#include "../AppEngine/Util/ArrayList.h"

#pragma once

namespace Wormhole
{
	class Client
	{
	private:
		static ArrayList<sf::TcpSocket*> sockets;
		static sf::UdpSocket broadcastSocket;
		static sf::Thread* broadcastThread;
		static bool broadcasting;
		static void threadBroadcast();

	public:
	    static void broadcast();
		static sf::Socket::Status connect(const sf::IpAddress& ipAddress, unsigned short port);
	};
}
