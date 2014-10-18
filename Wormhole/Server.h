
#include <SFML/Network.hpp>
#include "../AppEngine/Util/String.h"
#include "../AppEngine/Util/ArrayList.h"
#include <mutex>

#pragma once

namespace Wormhole
{
	typedef void(*WormholePeerDiscoveredCallback)(const String&);

	class Server
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

		sf::Clock timeData;

		unsigned short port;
		long pollingFrequency;
		bool polling;

		void pollingThreadCallback();

		WormholePeerDiscoveredCallback peerDiscoveredCallback;

	public:
		Server();
		~Server();

		void startPolling(unsigned short port, long pollingFrequency=1000);
		void stopPolling();

		bool isPolling();
		ArrayList<String> getIPList();
		void setPeerDiscoveredCallback(WormholePeerDiscoveredCallback callback);
	};
}
