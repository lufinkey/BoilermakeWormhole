
#include <SFML/Network.hpp>
#include "../AppEngine/ArrayList.h"

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
		static unsigned short port;
		static unsigned short range;
		static bool started;

	public:
		static void start(unsigned short port, unsigned short range);
		static void close();
	};
}