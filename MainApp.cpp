
#include "MainApp.h"
#include "AppEngine/Output/Console.h"
#include "Wormhole\Broadcaster.h"
#include "Wormhole\IpPoller.h"

Wormhole::Broadcaster broadcaster;
Wormhole::IpPoller poller;

void onPeerDiscovered(const String& ipAddress)
{
	Console::WriteLine((String)"Discovered ip: " + ipAddress);
}

void onPeerLost(const String& ipAddress)
{
	Console::WriteLine((String)"Lost ip: " + ipAddress);
}

void onDataReceived(const String& ipAddress, const void* data, unsigned int size)
{
	String str = (const char*)data;
	Console::WriteLine((String)"Data Received from ip: " + ipAddress + " : " + str);
}

MainApp::MainApp()
{
	//
}

MainApp::~MainApp()
{
	//
}

void MainApp::startServerClient()
{
	Console::WriteLine((String)"Local ip: " + sf::IpAddress::getLocalAddress().toString());
	broadcaster.startBroadcast(8009, 1000);
	poller.startPolling(8009, 1000);
	poller.setPeerDiscoveredCallback(&onPeerDiscovered);
	poller.setPeerLostCallback(&onPeerLost);
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
	//
}

void MainApp::Draw(Graphics2D&g, long appTime)
{
	
}

DWORD MainApp::onDropEnter(IDataObject* dataObj, Vector2<long> point)
{
	return DROPEFFECT_LINK;
}

void MainApp::onDropLeave()
{
	//
}

DWORD MainApp::onDropDragOver(Vector2<long> point)
{
	return DROPEFFECT_LINK;
}

DWORD MainApp::onDrop(IDataObject* dataObj, Vector2<long> point)
{
	static FORMATETC fmtetc_file = { CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
	static FORMATETC fmtetc_utxt = {CF_UNICODETEXT, 0, DVASPECT_CONTENT, -1, TYMED_HGLOBAL};
	static FORMATETC fmtetc_txt = {CF_TEXT, 0, DVASPECT_CONTENT, -1, TYMED_HGLOBAL};

	STGMEDIUM stgm;
	if (SUCCEEDED(dataObj->GetData(&fmtetc_file, &stgm)))
	{
		HDROP hdrop = reinterpret_cast<HDROP>(stgm.hGlobal);
		UINT cFiles = DragQueryFile(hdrop, 0xFFFFFFFF, NULL, 0);
		for (UINT i = 0; i < cFiles; i++)
		{
			TCHAR szFile[MAX_PATH];
			UINT cch = DragQueryFile(hdrop, i, szFile, MAX_PATH);
			if (cch > 0 && cch < MAX_PATH)
			{
				String fileName = szFile;
				onFileDropped(fileName);
			}
		}
		ReleaseStgMedium(&stgm);
	}
	else if(SUCCEEDED(dataObj->GetData(&fmtetc_utxt, &stgm)))
	{
		PVOID pvData = NULL;
		pvData = GlobalLock(stgm.hGlobal);
		//AssertPtr(pvData);
		size_t cbSize = GlobalSize(pvData);
		String text = (LPWSTR)pvData;
		onTextDropped(text);
		ReleaseStgMedium(&stgm);
	}
	else if(SUCCEEDED(dataObj->GetData(&fmtetc_txt, &stgm)))
	{
		PVOID pvData = NULL;
		pvData = GlobalLock(stgm.hGlobal);
		//AssertPtr(pvData);
		size_t cbSize = GlobalSize(pvData);
		String text = (LPCSTR)pvData;
		onTextDropped(text);
		ReleaseStgMedium(&stgm);
	}
	return DROPEFFECT_LINK;
}

void MainApp::onFileDropped(const String& str)
{
	//
}

void MainApp::onTextDropped(const String& str)
{
	//
}
