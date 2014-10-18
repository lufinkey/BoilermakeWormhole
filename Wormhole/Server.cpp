
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
	unsigned short Server::port = 8008;
	unsigned short Server::range = 16;
	bool Server::started = false;

	void Server::start(unsigned short port, unsigned short range)
	{
		if(started)
		{
			return;
		}
		started = true;

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