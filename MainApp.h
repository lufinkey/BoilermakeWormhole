
#include "AppEngine/Application.h"

#pragma once

using namespace AppEngine;

class MainApp : public AppEngine::Application
{
public:
	MainApp();
	virtual ~MainApp();

	static void startServerClient();

	virtual void Initialize();
	virtual void LoadContent();
	virtual void UnloadContent();
	virtual void Update(long appTime);
	virtual void Draw(Graphics2D&g, long appTime);

	virtual DWORD onDropEnter(IDataObject* dataObj, Vector2<long> point);
	virtual void onDropLeave();
	virtual DWORD onDropDragOver(Vector2<long> point);
	virtual DWORD onDrop(IDataObject* dataObj, Vector2<long> point);

	virtual void onFileDropped(const String& str);
	virtual void onTextDropped(const String& str);
};
