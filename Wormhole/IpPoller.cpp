
#include "IpPoller.h"
#include "../AppEngine/Output/Console.h"

namespace Wormhole
{
	IpPoller::IpPoller()
	{
		polling = false;
		pollingThread = NULL;
		discoveryPort = 8008;
		pollingFrequency = 1000;

		peerDiscoveredCallback = NULL;
		peerLostCallback = NULL;
	}

	IpPoller::~IpPoller()
	{
		if(polling)
		{
			stopPolling();
		}
	}

	void IpPoller::startPolling(unsigned short discoveryPort, long pollingFrequency)
	{
		if(polling)
		{
			stopPolling();
		}

		polling = true;
		this->discoveryPort = discoveryPort;
		this->pollingFrequency = pollingFrequency;

		pollingSocket.bind(discoveryPort);
		pollingThread = new sf::Thread(&IpPoller::pollingThreadCallback, this);
		pollingThread->launch();
	}

	void IpPoller::stopPolling()
	{
		if(polling)
		{
			polling = false;
			pollingSocket.unbind();
			delete pollingThread;
			pollingThread = NULL;
		}
	}

	void IpPoller::pollingThreadCallback()
	{
		timeData.restart();

		while(polling)
		{
			sf::Packet senderData;
			sf::IpAddress sender;
			unsigned short senderPort = 0;

			sf::Socket::Status status = pollingSocket.receive(senderData, sender, senderPort);

			String selfIP = sf::IpAddress::getLocalAddress().toString();

			ArrayList<String> lostPeers;

			IPList_mutex.lock();

			//checking for expired IPs
			long currentTime = timeData.getElapsedTime().asMilliseconds();
			for(int i = (IPList.size()-1); i >= 0; i--)
			{
				IPData data = IPList.get(i);
				if((currentTime - data.lastHeardTime) > 4000)
				{
					IPList.remove(i);

					lostPeers.add(data.ipAddress);
				}
			}

			ArrayList<String> discoveredPeers;

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
						discoveredPeers.add(senderString);
					}
				}
			}

			IPList_mutex.unlock();

			for(int i = 0; i < lostPeers.size(); i++)
			{
				if(peerLostCallback!=NULL)
				{
					peerLostCallback(lostPeers.get(i));
				}
			}

			//AppEngine::Console::WriteLine((String)"on sender port " + senderPort);
			for(int i = 0; i < discoveredPeers.size(); i++)
			{
				if(peerDiscoveredCallback!=NULL)
				{
					peerDiscoveredCallback(discoveredPeers.get(i));
				}
			}

			if(polling)
			{
				sf::sleep(sf::milliseconds(pollingFrequency));
			}
		}

		IPList.clear();
	}

	bool IpPoller::isPolling()
	{
		return polling;
	}

	ArrayList<String> IpPoller::getIPList()
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

	void IpPoller::setPeerDiscoveredCallback(WormholePeerDiscoveredCallback callback)
	{
		peerDiscoveredCallback = callback;
	}

	void IpPoller::setPeerLostCallback(WormholePeerLostCallback callback)
	{
		peerLostCallback = callback;
	}
}