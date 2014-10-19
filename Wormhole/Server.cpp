
#include "../AppEngine/Output/Console.h"
#include "Server.h"

namespace Wormhole
{
	Server::TcpNode::TcpNode(Server*server, unsigned short port)
	{
		acceptThread = NULL;
		receivedDataPollingThread = NULL;
		acceptingConnections = false;
		pollingReceivedData = false;
		this->server = server;
		this->port = port;
		listener.listen(port);
	}

	Server::TcpNode::~TcpNode()
	{
		acceptingConnections = false;
		pollingReceivedData = false;
		listener.close();
		disconnect();
	}

	void Server::TcpNode::accept()
	{
		if(acceptingConnections)
		{
			return;
		}

		acceptingConnections = true;
		acceptThread = new sf::Thread(&Wormhole::Server::TcpNode::acceptThreadCallback, this);
		acceptThread->launch();
	}

	void Server::TcpNode::acceptThreadCallback()
	{
		while(acceptingConnections)
		{
			sf::Socket::Status status = listener.accept(socket);
			if(status == sf::Socket::Done)
			{
				acceptingConnections = false;
				if(server->peerConnectedCallback != NULL)
				{
					server->peerConnectedCallback(socket.getRemoteAddress().toString());
				}
			}
		}
	}

	void Server::TcpNode::pollReceivedData()
	{
		if(pollingReceivedData)
		{
			return;
		}

		pollingReceivedData = true;
		receivedDataPollingThread = new sf::Thread(&Server::TcpNode::receivedDataPollingThreadCallback, this);
		receivedDataPollingThread->launch();
	}

	void Server::TcpNode::receivedDataPollingThreadCallback()
	{
		while(pollingReceivedData)
		{
			String ipAddress = socket.getRemoteAddress().toString();
			sf::Packet packet;
			sf::Socket::Status status = socket.receive(packet);
			if(status == sf::Socket::Done)
			{
				if(server->dataReceivedCallback != NULL)
				{
					server->dataReceivedCallback(ipAddress, packet.getData(), packet.getDataSize());
				}
			}
		}
	}

	void Server::TcpNode::disconnect()
	{
		acceptingConnections = false;
		pollingReceivedData = false;
		socket.disconnect();
		if(receivedDataPollingThread != NULL)
		{
			delete receivedDataPollingThread;
			receivedDataPollingThread = NULL;
		}
		if(acceptThread != NULL)
		{
			delete acceptThread;
			acceptThread = NULL;
		}
	}

	bool Server::TcpNode::isConnected()
	{
		if(socket.getRemoteAddress() == sf::IpAddress::None)
		{
			return false;
		}
		return true;
	}

	bool Server::TcpNode::isPollingReceivedData()
	{
		return pollingReceivedData;
	}

	String Server::TcpNode::getIP()
	{
		return socket.getRemoteAddress().toString();
	}

	Server::Server()
	{
		polling = false;
		pollingThread = NULL;
		discoveryPort = (unsigned short)80081;
		nodesPort = (unsigned short)80082;
		pollingFrequency = 1000;

		peerDiscoveredCallback = NULL;
		peerLostCallback = NULL;
		peerConnectedCallback = NULL;
		dataReceivedCallback = NULL;
	}

	Server::~Server()
	{
		if(polling)
		{
			stopPolling();
		}
	}

	void Server::startPolling(unsigned short discoveryPort, long pollingFrequency)
	{
		if(polling)
		{
			stopPolling();
		}

		polling = true;
		this->discoveryPort = discoveryPort;
		this->pollingFrequency = pollingFrequency;

		pollingSocket.bind(discoveryPort);
		pollingThread = new sf::Thread(&Server::pollingThreadCallback, this);
		pollingThread->launch();
	}

	void Server::stopPolling()
	{
		if(polling)
		{
			polling = false;
			pollingSocket.unbind();
			delete pollingThread;
			pollingThread = NULL;
		}
	}

	void Server::pollingThreadCallback()
	{
		timeData.restart();

		while(polling)
		{
			char buffer[20];
			unsigned int size = 0;

			sf::IpAddress sender;

			sf::Socket::Status status = pollingSocket.receive(buffer, sizeof(buffer), size, sender, discoveryPort);

			String selfIP = sf::IpAddress::getLocalAddress().toString();

			IPList_mutex.lock();

			//checking for expired IPs
			long currentTime = timeData.getElapsedTime().asMilliseconds();
			for(int i = (IPList.size()-1); i >= 0; i--)
			{
				IPData data = IPList.get(i);
				if((currentTime - data.lastHeardTime) > 8000)
				{
					IPList.remove(i);

					if(peerLostCallback != NULL)
					{
						peerLostCallback(data.ipAddress);
					}
				}
			}

			//checking recieved ip
			if(status != sf::Socket::Disconnected && status != sf::Socket::Error && polling)
			{
				bool containsIP = false;

				String senderString = sender.toString();

				for(int i = 0; i < IPList.size(); i++)
				{
					IPData data = IPList.get(i);
					if(data.ipAddress.equals(senderString))
					{
						containsIP = true;

						data.lastHeardTime = timeData.getElapsedTime().asMilliseconds();
						IPList.set(i, data);

						i = IPList.size();
					}
				}

				if(!containsIP)
				{
					if(!senderString.equals(selfIP))
					{
						IPData data;
						data.ipAddress = senderString;
						data.lastHeardTime = timeData.getElapsedTime().asMilliseconds();
						IPList.add(data);
						if(peerDiscoveredCallback != NULL)
						{
							peerDiscoveredCallback(senderString);
						}
					}
				}
			}

			IPList_mutex.unlock();

			if(polling)
			{
				sf::sleep(sf::milliseconds(pollingFrequency));
			}
		}

		IPList.clear();
	}

	void Server::openNode(unsigned short port)
	{
		nodes_mutex.lock();

		TcpNode* node = new TcpNode(this, port);
		nodes.add(node);
		node->accept();

		nodes_mutex.unlock();
	}

	bool Server::isPolling()
	{
		return polling;
	}

	ArrayList<String> Server::getIPList()
	{
		IPList_mutex.lock();
		ArrayList<String> IPs;

		for (int i = 0; i < IPList.size(); i++)
		{
			IPs.add(IPList.get(i).ipAddress);
		}

		IPList_mutex.unlock();

		return IPs;
	}

	void Server::setPeerDiscoveredCallback(WormholePeerDiscoveredCallback callback)
	{
		peerDiscoveredCallback = callback;
	}

	void Server::setPeerLostCallback(WormholePeerLostCallback callback)
	{
		peerLostCallback = callback;
	}

	void Server::setPeerConnectedCallback(WormholePeerConnectedCallback callback)
	{
		peerConnectedCallback = callback;
	}

	void Server::setDataReceivedCallback(WormholeDataReceivedCallback callback)
	{
		dataReceivedCallback = callback;
	}
}
