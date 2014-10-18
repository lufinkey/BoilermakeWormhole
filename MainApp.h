
#include "AppEngine\Application.h"

#pragma once

using namespace AppEngine;

class MainApp : public AppEngine::Application
{
public:
	MainApp();
	virtual ~MainApp();

	virtual void Initialize();
	virtual void LoadContent();
	virtual void UnloadContent();
	virtual void Update(long appTime);
	virtual void Draw(Graphics2D&g, long appTime);
};