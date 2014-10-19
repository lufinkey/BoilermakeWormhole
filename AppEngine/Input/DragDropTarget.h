
#include <oleidl.h>
#include "../forwards.h"

#pragma once

namespace AppEngine
{
	class DragDropTarget : public IDropTarget
	{
	private:
		unsigned long FReferences;
		bool FAcceptFormat;

		Application* app;

	public:
		DragDropTarget(Application* app);
		~DragDropTarget();

		virtual STDMETHODIMP QueryInterface(REFIID riid, void **ppv);
		virtual STDMETHODIMP_(ULONG) AddRef();
		STDMETHODIMP_(ULONG) Release();

		virtual STDMETHODIMP DragEnter(IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect);
		virtual STDMETHODIMP DragLeave();
		virtual STDMETHODIMP DragOver(DWORD grfKeyState, POINTL pt, DWORD *pdwEffect);
		virtual STDMETHODIMP Drop(IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD*pdwEffect);
	};
}