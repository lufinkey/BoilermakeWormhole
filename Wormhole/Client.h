
#include <SFML/Network.hpp>
#include <SFML/System/Thread.hpp>
#include "../AppEngine/Util/String.h"
#include "../AppEngine/Util/ArrayList.h"
#include "DataVoid.h"
#include <mutex>

#pragma once

namespace Wormhole
{
	class Client
	{
	private:
		class SendThread : public sf::Thread
		{
		private:
			DataVoid data;
			sf::TcpSocket* socket;
			bool sending;

		public:
			SendThread(DataVoid& data, sf::TcpSocket* socket);
			~SendThread();

			void threadCallback();

			bool isSending();
		};

		class TcpPeer
		{
		private:
			String ipAddress;
			sf::TcpSocket peerSocket;

			std::mutex connectThread_mutex;
			sf::Thread* connectThread;

			std::mutex sendThreads_mutex;
			ArrayList<SendThread*> sendThreads;

			bool sending;
			unsigned short port;

			void connectThreadCallback();

		public:
			TcpPeer(const String& ipAddress);
			~TcpPeer();

			void connect(unsigned short port);
			void disconnect();
			void send(void* data, unsigned int size);
			void send(DataVoid& data);

			bool isConnected();
			const String& getIP();
		};

		//Finding peers
		sf::UdpSocket broadcastSocket;
		sf::Thread* broadcastThread;
		bool broadcasting;
		unsigned short broadcastPort;
		long broadcastFrequency;
		
		std::mutex peers_mutex;
		ArrayList<TcpPeer*> peers;

		void broadcastThreadCallback();

	public:
		Client();
		~Client();

	    void startBroadcast(unsigned short port, long broadcastFreqency = 1000);
		void stopBroadcast();

		void connectPeer(const String& ipAddress, unsigned short port);
		void disconnectPeer(const String& ipAddress);

		void sendToPeers(DataVoid& dataVoid);
		void sendToPeers(void*data, unsigned int size);

		bool isBroadcasting();
	};
}
