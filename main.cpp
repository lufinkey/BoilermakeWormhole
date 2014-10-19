
#include "MainApp.h"
#include "Wormhole/Client.h"
#include "Wormhole/Server.h"
#include "AppEngine/Output/Console.h"

#undef main

#if defined(SFML_STATIC) && defined(_MSC_VER)
#pragma comment(lib, "glew.lib")
#pragma comment(lib, "freetype.lib")
#pragma comment(lib, "jpeg.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "ws2_32.lib")
#endif // SFML_STATIC &&_ MSVC

void peerConnected(const String& ipAddress)
{
	AppEngine::Console::WriteLine((String)"peer connected with ip " + ipAddress);
}

int main(int argc, char* argv[])
{
	Wormhole::Server server;
	Wormhole::Client client;
	server.startPolling((unsigned short)80085, 1000);
	client.startBroadcast((unsigned short)80085, 1000);

	MainApp* mainApp = new MainApp();
	int retVal = mainApp->run(300,300);
	delete mainApp;
	return retVal;
}
