
#include "Client.h"
#include "String.h"
#include "../AppEngine/Output/Console.h"

namespace Wormhole
{
	Client::Client()
	{
		broadcasting = false;
		broadcastThread = NULL;
	}

	Client::~Client()
	{
		if(broadcasting)
		{
			stopBroadcast();
		}
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
		if(broadcasting)
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
}
