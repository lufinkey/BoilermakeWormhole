
#include "Broadcaster.h"
#include "../AppEngine/Output/Console.h"

namespace Wormhole
{
	Broadcaster::Broadcaster()
	{
		broadcasting = false;
		broadcastThread = NULL;
		broadcastPort = 8008;
		broadcastFrequency = 1000;
	}

	Broadcaster::~Broadcaster()
	{
		if(broadcasting)
		{
			stopBroadcast();
		}
	}

	void Broadcaster::startBroadcast(unsigned short port, long broadcastFrequency)
    {
		if(broadcasting)
		{
			stopBroadcast();
		}

		broadcasting = true;
		broadcastPort = port;
		this->broadcastFrequency = broadcastFrequency;
		//broadcastSocket.bind(port);
		broadcastThread = new sf::Thread(&Broadcaster::broadcastThreadCallback, this);
		broadcastThread->launch();
    }

	void Broadcaster::stopBroadcast()
	{
		if (broadcasting)
		{
			broadcasting = false;
			//broadcastSocket.unbind();
			delete broadcastThread;
			broadcastThread = NULL;
		}
	}

	void Broadcaster::broadcastThreadCallback()
    {
        while (broadcasting)
        {
			String data = "<3 Nafe";
			//AppEngine::Console::WriteLine((String)"sending broadcast on port " + (int)broadcastPort);
            broadcastSocket.send((const char*)data, data.length() + 1, sf::IpAddress::Broadcast, broadcastPort);
			if(broadcasting)
			{
				sf::sleep(sf::milliseconds(broadcastFrequency));
			}
        }
    }

	bool Broadcaster::isBroadcasting()
	{
		return broadcasting;
	}
}