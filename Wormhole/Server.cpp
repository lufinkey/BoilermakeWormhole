
#include "../AppEngine/Output/Console.h"
#include "Server.h"

namespace Wormhole
{
	Server::Server()
	{
		polling = false;
		discoveryPollingThread = NULL;
		transferPollingThread = NULL;
		discoveryPort = 8009;
		transferPort = 8010;
		pollingFrequency = 1000;
		peerDiscoveredCallback = NULL;
	}

	Server::~Server()
	{
		if(polling)
		{
			stopPolling();
		}
	}

	void Server::startPolling(unsigned short discoveryPort, unsigned short transferPort, long pollingFrequency)
	{
		if(polling)
		{
			stopPolling();
		}

		polling = true;
		this->discoveryPort = discoveryPort;
		this->transferPort = transferPort;
		this->pollingFrequency = pollingFrequency;

		pollingSocket.bind(discoveryPort);
		discoveryPollingThread = new sf::Thread(&Server::discoveryPollingThreadCallback, this);
		discoveryPollingThread->launch();

		transferPollingThread = new sf::Thread(&Server::transferPollingThread, this);
		transferPollingThread->launch();
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

	void Server::discoveryPollingThreadCallback()
	{
		timeData.restart();

		while(polling)
		{
			char buffer[20];
			unsigned int size = 0;

			sf::IpAddress sender;

			sf::Socket::Status status = pollingSocket.receive(buffer, sizeof(buffer), size, sender, port);

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

	void Server::transferPollingThreadCallback()
	{
		while (polling)
		{
			char buffer[1024];
			std::size_t received = 0;
			transferSocket.receive(buffer, sizeof(buffer), received);
			paths.add(buffer);
		}
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
}
