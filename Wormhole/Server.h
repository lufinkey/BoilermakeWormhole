
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
		sf::TcpSocket transferSocket;
		sf::Thread* discoveryPollingThread;
		sf::Thread* transferPollingThread;
		ArrayList<String> paths;

		sf::Clock timeData;

		unsigned short discoveryPort;
		unsigned short transferPort;
		long pollingFrequency;
		bool polling;

		void discoveryPollingThreadCallback();
		void transferPollingThreadCallback();

		WormholePeerDiscoveredCallback peerDiscoveredCallback;

	public:
		Server();
		~Server();

		void startPolling(unsigned short discoveryPort, unsigned short transferPort, long pollingFrequency=1000);
		void stopPolling();

		bool isPolling();
		ArrayList<String> getIPList();
		void setPeerDiscoveredCallback(WormholePeerDiscoveredCallback callback);
	};
}
