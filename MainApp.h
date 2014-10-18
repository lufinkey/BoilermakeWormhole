
#include "AppEngine/Application.h"
#include "Wormhole/Client.h"
#include "Wormhole/Server.h"

#pragma once

using namespace AppEngine;

class MainApp : public AppEngine::Application
{
private:
	Wormhole::Server server;
	Wormhole::Client client;

public:
	MainApp();
	virtual ~MainApp();

	virtual void Initialize();
	virtual void LoadContent();
	virtual void UnloadContent();
	virtual void Update(long appTime);
	virtual void Draw(Graphics2D&g, long appTime);
};
