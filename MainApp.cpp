
#include "MainApp.h"
#include "AppEngine/Output/Console.h"

MainApp::MainApp()
{
	server.startPolling(800813, 1000);
	client.startBroadcast(800813, 1000);
}

MainApp::~MainApp()
{
	//
}

void MainApp::Initialize()
{
	//
}

void MainApp::LoadContent()
{
	//
}

void MainApp::UnloadContent()
{
	//
}

void MainApp::Update(long appTime)
{
	AppEngine::Console::WriteLine("IP List:");

	for (int i = 0; i < server.getIPList().size(); i++)
	{
		AppEngine::Console::Write(server.getIPList().get(i));
	}
}

void MainApp::Draw(Graphics2D&g, long appTime)
{
	//
}
