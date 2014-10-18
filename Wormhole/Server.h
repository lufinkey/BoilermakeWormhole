
#include <SFML/Network.hpp>
#include "../AppEngine/Util/String.h"
#include "../AppEngine/Util/ArrayList.h"

#pragma once

namespace Wormhole
{
	class Server
	{
	private:
		class TcpNode
		{
		private:
			sf::TcpListener listener;
			sf::TcpSocket socket;
			sf::Thread* acceptThread;
			unsigned short port;

			void acceptThreadCallback();

		public:
			TcpNode(unsigned short port);
			~TcpNode();
			bool connected();
		};

		static ArrayList<TcpNode*> nodes;
		static ArrayList<String> ips;
		static sf::UdpSocket listenSocket;
		static sf::Thread* listenThread;
		static unsigned short port;
		static unsigned short range;
		static bool started;

		static void threadListen();
	public:
		static void start(unsigned short port, unsigned short range);
		static void close();
	};
}
