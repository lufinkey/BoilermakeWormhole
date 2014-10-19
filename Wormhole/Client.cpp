
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

    void Client::sendFile(unsigned short port, ArrayList<String> recipients, String path)
    {
        if (sendingFile)
		{
			stopSendFile();
		}

		sending = true;
		sendFilePort = port;
        this->path = path;
        sendFileThread = new sf::Thread(&Client::sendFileThreadCallback, recipients);
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

    void Client::sendFileThreadCallback(ArrayList<String> recipients)
    {
		for (int i = 0; i < recipients.size(); i++)
		{
            sendFileSocket.connect((char*)recipients.get(i), sendFilePort);
            sendFileSocket.send((const char*)path, path.length() + 1);
            sendFileSocket.disconnect();
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
