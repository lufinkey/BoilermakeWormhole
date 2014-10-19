
#include <SFML/Network.hpp>
#include "../AppEngine/Util/String.h"
#include "../AppEngine/Util/ArrayList.h"
#include "DataVoid.h"
#include <mutex>

#pragma once

namespace Wormhole
{
	typedef void(*WormholePeerDiscoveredCallback)(const String&);
	typedef void(*WormholePeerLostCallback)(const String&);
	typedef void(*WormholePeerConnectedCallback)(const String&);

	typedef void(*WormholeDataReceivedCallback)(const String&, const void*, size_t);

	class Server
	{
	private:
		class TcpNode
		{
		private:
			Server* server;

			sf::TcpListener listener;
			sf::TcpSocket socket;
			sf::Thread* acceptThread;
			bool acceptingConnections;
			unsigned short port;

			sf::Thread* receivedDataPollingThread;
			bool pollingReceivedData;

			void acceptThreadCallback();
			void receivedDataPollingThreadCallback();
			
		public:
			TcpNode(Server*server, unsigned short port);
			~TcpNode();

			void accept();
			void pollReceivedData();
			void disconnect();

			bool isConnected();
			bool isPollingReceivedData();

			String getIP();
		};

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

		std::mutex nodes_mutex;
		ArrayList<TcpNode*> nodes;
		unsigned short nodesPort;

		WormholePeerDiscoveredCallback peerDiscoveredCallback;
		WormholePeerLostCallback peerLostCallback;
		WormholePeerConnectedCallback peerConnectedCallback;
		WormholeDataReceivedCallback dataReceivedCallback;

		void pollingThreadCallback();

	public:
		Server();
		~Server();

		void startPolling(unsigned short discoveryPort, long pollingFrequency=1000);
		void stopPolling();

		void openNode(unsigned short port);
		bool nodeConnected(const String& ipAddress);
		void closeNode(unsigned short port);
		void closeNode(const String& ipAddress);

		bool isPolling();
		ArrayList<String> getIPList();

		void setPeerDiscoveredCallback(WormholePeerDiscoveredCallback callback);
		void setPeerLostCallback(WormholePeerLostCallback callback);
		void setPeerConnectedCallback(WormholePeerConnectedCallback callback);
		void setDataReceivedCallback(WormholeDataReceivedCallback callback);
	};
}
