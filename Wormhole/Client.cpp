
#include "Client.h"
#include "String.h"
#include "../AppEngine/Output/Console.h"

namespace Wormhole
{
	Client::SendThread::SendThread(DataVoid& data, sf::TcpSocket* socket) : sf::Thread(&Client::SendThread::threadCallback, this)
	{
		this->data = data;
		this->socket = socket;
		sending = true;
	}

	Client::SendThread::~SendThread()
	{
		//
	}

	void Client::SendThread::threadCallback()
	{
		socket->send(data.getData(), data.length());
		sending = false;
	}

	bool Client::SendThread::isSending()
	{
		return sending;
	}

	Client::TcpPeer::TcpPeer(const String& ipAddress)
	{
		sending = false;
		port = (unsigned short)80082;
		connectThread = NULL;
		this->ipAddress = ipAddress;
	}

	Client::TcpPeer::~TcpPeer()
	{
		disconnect();
	}

	void Client::TcpPeer::connect(unsigned short port)
	{
		if(isConnected())
		{
			disconnect();
		}

		this->port = port;

		connectThread_mutex.lock();
		if(connectThread != NULL)
		{
			delete connectThread;
			connectThread = NULL;
		}

		connectThread = new sf::Thread(&Client::TcpPeer::connectThreadCallback, this);
		connectThread->launch();
		connectThread_mutex.unlock();
	}

	void Client::TcpPeer::connectThreadCallback()
	{
		sf::Socket::Status status = peerSocket.connect((char*)ipAddress, port, sf::milliseconds(3000));
	}

	void Client::TcpPeer::disconnect()
	{
		peerSocket.disconnect();

		connectThread_mutex.lock();
		if(connectThread != NULL)
		{
			delete connectThread;
			connectThread = NULL;
		}
		connectThread_mutex.unlock();

		sendThreads_mutex.lock();
		for(int i = (sendThreads.size()-1); i >= 0; i--)
		{
			delete sendThreads.get(i);
			sendThreads.remove(i);
		}
		sendThreads_mutex.unlock();
	}

	void Client::TcpPeer::send(void* data, unsigned int size)
	{
		send(DataVoid(data, size));
	}

	void Client::TcpPeer::send(DataVoid& dataVoid)
	{
		sendThreads_mutex.lock();
		for(int i = (sendThreads.size()-1); i >= 0; i--)
		{
			SendThread* sendThread = sendThreads.get(i);
			if(!sendThread->isSending())
			{
				delete sendThread;
				sendThreads.remove(i);
			}
		}

		SendThread* sendThread = new SendThread(dataVoid, &peerSocket);
		sendThreads.add(sendThread);
		sendThreads_mutex.unlock();
		
		sendThread->launch();
	}

	bool Client::TcpPeer::isConnected()
	{
		if(peerSocket.getRemoteAddress() == sf::IpAddress::None)
		{
			return false;
		}
		return true;
	}

	const String& Client::TcpPeer::getIP()
	{
		return ipAddress;
	}

	Client::Client()
	{
		broadcasting = false;
		broadcastThread = NULL;
		broadcastPort = (unsigned short)80081;
		broadcastFrequency = 1000;
	}

	Client::~Client()
	{
		if(broadcasting)
		{
			stopBroadcast();
		}

		peers_mutex.lock();
		for(int i = (peers.size()-1); i >= 0; i--)
		{
			delete peers.get(i);
			peers.remove(i);
		}
		peers_mutex.unlock();
	}

    void Client::startBroadcast(unsigned short port, long broadcastFrequency)
    {
		if(broadcasting)
		{
			stopBroadcast();
		}

		broadcasting = true;
		broadcastPort = port;
		this->broadcastFrequency = broadcastFrequency;
		//broadcastSocket.bind(port);
		broadcastThread = new sf::Thread(&Client::broadcastThreadCallback, this);
		broadcastThread->launch();
    }

	void Client::stopBroadcast()
	{
		if (broadcasting)
		{
			broadcasting = false;
			//broadcastSocket.unbind();
			delete broadcastThread;
			broadcastThread = NULL;
		}
	}

	void Client::broadcastThreadCallback()
    {
        while (broadcasting)
        {
			String data = "suckmydick";
            broadcastSocket.send((const char*)data, data.length() + 1, sf::IpAddress::Broadcast, broadcastPort);
			if(broadcasting)
			{
				sf::sleep(sf::milliseconds(broadcastFrequency));
			}
        }
    }

	bool Client::isBroadcasting()
	{
		return broadcasting;
	}

	void Client::connectPeer(const String& ipAddress, unsigned short port)
	{
		peers_mutex.lock();

		TcpPeer* peer = new TcpPeer(ipAddress);
		peer->connect(port);
		peers.add(peer);

		peers_mutex.unlock();
	}

	void Client::disconnectPeer(const String& ipAddress)
	{
		peers_mutex.lock();

		for(int i = 0; i < peers.size(); i++)
		{
			TcpPeer* peer = peers.get(i);
			if(peer->getIP().equals(ipAddress))
			{
				delete peer;
				peers.remove(i);
				i = peers.size();
			}
		}

		peers_mutex.unlock();
	}

	void Client::sendToPeers(DataVoid& dataVoid)
	{
		peers_mutex.lock();

		for(int i = 0; i < peers.size(); i++)
		{
			peers.get(i)->send(dataVoid);
		}

		peers_mutex.unlock();
	}

	void Client::sendToPeers(void* data, unsigned int size)
	{
		sendToPeers(DataVoid(data, size));
	}
}
