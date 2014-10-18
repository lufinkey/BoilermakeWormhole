
#include <SFML/Network.hpp>
#include <SFML/System/Thread.hpp>
#include "../AppEngine/Util/String.h"
#include "../AppEngine/Util/ArrayList.h"

#pragma once

namespace Wormhole
{
	class Client
	{
	private:
		//Finding peers
		sf::UdpSocket broadcastSocket;
		sf::Thread* broadcastThread;
		bool broadcasting;
		unsigned short broadcastPort;
		long broadcastFrequency;
		//Sending files
		sf::TcpSocket sendFileSocket;
		ArrayList<sf::TcpSocket> fileRecpients;
		sf::Thread* sendFileThread;
		sf::Thread* connectThread;
		unsigned short sendFilePort;
		String path;
		bool sendingFile;

		void broadcastThreadCallback();
		void sendFileThreadCallback();
		void connectThreadCallback(char* IP);

	public:
		Client();
		~Client();

	    void startBroadcast(unsigned short port, long broadcastFreqency = 1000);
		void stopBroadcast();
		void sendFile(unsigned short port, String path);
		void stopSendFile();
		void connect(ArrayList<String> IPs);

		bool isBroadcasting();
		bool isSendingFile();
	};
}
