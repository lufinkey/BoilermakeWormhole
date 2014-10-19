
#include <SFML/Network.hpp>
#include "../AppEngine/Util/String.h"
#include "../AppEngine/Util/ArrayList.h"
#include <mutex>

#pragma once

namespace Wormhole
{
	typedef void(*WormholePeerDiscoveredCallback)(const String&);
	typedef void(*WormholePeerLostCallback)(const String&);

	class IpPoller
	{
	private:
		typedef struct
		{
			long lastHeardTime;
			String ipAddress;
		} IPData;

		std::mutex IPList_mutex;
		ArrayList<IPData> IPList;

		sf::UdpSocket pollingSocket;
		sf::Thread* pollingThread;
		unsigned short discoveryPort;
		long pollingFrequency;
		bool polling;

		sf::Clock timeData;

		WormholePeerDiscoveredCallback peerDiscoveredCallback;
		WormholePeerLostCallback peerLostCallback;

		void pollingThreadCallback();

	public:
		IpPoller();
		~IpPoller();

		void startPolling(unsigned short discoveryPort, long pollingFrequency=1000);
		void stopPolling();

		bool isPolling();
		ArrayList<String> getIPList();

		void setPeerDiscoveredCallback(WormholePeerDiscoveredCallback callback);
		void setPeerLostCallback(WormholePeerLostCallback callback);
	};
}