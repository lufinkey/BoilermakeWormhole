
#include <SFML/Network.hpp>
#include <SFML/System/Thread.hpp>
#include "../AppEngine/Util/ArrayList.h"
#include "../AppEngine/Util/String.h"

#pragma once

namespace Wormhole
{
	class Broadcaster
	{
	private:
		unsigned short broadcastPort;
		long broadcastFrequency;

		sf::UdpSocket broadcastSocket;
		sf::Thread* broadcastThread;
		bool broadcasting;

		void broadcastThreadCallback();

	public:
		Broadcaster();
		~Broadcaster();

		void startBroadcast(unsigned short port, long broadcastFreqency = 1000);
		void stopBroadcast();

		bool isBroadcasting();
	};
}