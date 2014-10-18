
#include "MainApp.h"
#include "Wormhole/Client.h"
#include "Wormhole/Server.h"

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

int main(int argc, char* argv[])
{
	//TODO add bending of space and time
	MainApp* mainApp = new MainApp();

	Wormhole::Server::start(8009, 16);
	Wormhole::Client::startBroadcast();

	int retVal = mainApp->run(300,300);
	delete mainApp;
	return retVal;
}
