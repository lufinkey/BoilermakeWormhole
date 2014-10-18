
#include "Client.h"
#include "String.h"
#include "../AppEngine/Output/Console.h"

namespace Wormhole
{
	Client::Client()
	{
		broadcasting = false;
		broadcastThread = NULL;
		sendingFile = false;
		sendFileThread = NULL;
	}

	Client::~Client()
	{
		if(broadcasting)
		{
			stopBroadcast();
		}

		if(sendingFile)
		{
            stopSendFile();
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

    void Client::sendFile(unsigned short port, String path)
    {
        if (sendingFile)
		{
			stopSendFile();
		}

		sending = true;
		sendFilePort = port;
        this->path = path;
        sendFileThread = new sf::Thread(&Client::sendFileThreadCallback, this);
        sendFileThread->launch();
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

	void Client::stopSendFile()
	{
		if (sendingFile)
		{
			sendingFile = false;
			delete sendFileThread;
			sendFileThread = NULL;
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

    void Client::sendFileThreadCallback()
    {

    }

    void Client::connect(ArrayList<String> IPs)
    {
        for (int i = 0; i < IPs.size(); i++)
		{
			sf::TcpSocket recipient;
			recipient.connect((char*)IPs.get(i), sendFilePort);
			recipients.add(recipient);
		}
    }

	bool Client::isBroadcasting()
	{
		return broadcasting;
	}

	bool Client::isSendingFile()
	{
		return sendingFile;
	}
}
