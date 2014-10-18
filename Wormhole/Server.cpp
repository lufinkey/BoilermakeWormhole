
#include "../AppEngine/Output/Console.h"
#include "Server.h"

namespace Wormhole
{
	//TcpNode

	Server::TcpNode::TcpNode(unsigned short port)
	{
		this->port = port;
		listener.listen(port);
		acceptThread = new sf::Thread(&Wormhole::Server::TcpNode::acceptThreadCallback, this);
		acceptThread->launch();
	}

	Server::TcpNode::~TcpNode()
	{
		if(socket.getRemoteAddress() != sf::IpAddress::None)
		{
			socket.disconnect();
		}
		listener.close();
		delete acceptThread;
	}

	void Server::TcpNode::acceptThreadCallback()
	{
		listener.accept(socket);
	}

	bool Server::TcpNode::connected()
	{
		if(socket.getRemoteAddress() == sf::IpAddress::None)
		{
			return false;
		}
		return true;
	}



	//Server

	ArrayList<Server::TcpNode*> Server::nodes = ArrayList<Server::TcpNode*>();
	ArrayList<String> Server::ips = ArrayList<String>();
	sf::UdpSocket Server::listenSocket;
	sf::Thread* Server::listenThread;
	unsigned short Server::port = 8008;
	unsigned short Server::range = 16;
	bool Server::started = false;

	void Server::threadListen()
	{
        while (true)
		{
			char buffer[1024];
			std::size_t received = 0;
			sf::IpAddress sender;
			unsigned short port;
			listenSocket.receive(buffer, sizeof(buffer), received, sender, port);

			if (!ips.contains(sender.toString()))
			{
				ips.add(sender.toString());
			}

			for (int i = 0; i < ips.size(); i++)
			{
				AppEngine::Console::WriteLine(ips.get(i));
			}

			sf::sleep(sf::milliseconds(1000));
		}
	}

	void Server::start(unsigned short port, unsigned short range)
	{
		if(started)
		{
			return;
		}
		started = true;

		listenSocket.bind(port);

		listenThread = new sf::Thread(&Wormhole::Server::threadListen);
		listenThread->launch();

		Server::port = port;
		Server::range = range;
		unsigned short endPort = port + range;

		for(unsigned short i = port; i < endPort; i++)
		{
			TcpNode* node = new TcpNode(i);
			nodes.add(node);
		}
	}

	void Server::close()
	{
		if(!started)
		{
			return;
		}

		for(int i = (nodes.size()-1); i >= 0; i--)
		{
			TcpNode* node = nodes.get(i);
			delete node;
			nodes.remove(i);
		}

		started = false;
	}
}
