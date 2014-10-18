
#include <SFML/Network.hpp>
#include <SFML/System/Thread.hpp>
#include "../AppEngine/Util/ArrayList.h"

#pragma once

namespace Wormhole
{
	class Client
	{
	private:
		sf::UdpSocket broadcastSocket;
		sf::Thread* broadcastThread;
		bool broadcasting;
		unsigned short broadcastPort;
		long broadcastFrequency;

		void broadcastThreadCallback();

	public:
		Client();
		~Client();

	    void startBroadcast(unsigned short port, long broadcastFreqency = 1000);
		void stopBroadcast();

		bool isBroadcasting();
	};
}
