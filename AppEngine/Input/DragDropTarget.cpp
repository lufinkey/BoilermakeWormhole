
#include "DragDropTarget.h"
#include "../Application.h"

namespace AppEngine
{
	DragDropTarget::DragDropTarget(Application* app)
	{
		this->app = app;

		FReferences = 1;
		FAcceptFormat = false;
	}

	DragDropTarget::~DragDropTarget()
	{
		//
	}

	STDMETHODIMP DragDropTarget::QueryInterface(REFIID riid, void **ppv)
	{
		*ppv = this;
		AddRef();
		return NOERROR;
	}

	STDMETHODIMP_(ULONG) DragDropTarget::AddRef()
	{
		return ++FReferences;
	}

	STDMETHODIMP_(ULONG) DragDropTarget::Release()
	{
		if (--FReferences == 0) 
		{
			delete this; 
			return 0; 
		} 
		return FReferences;
	}

	STDMETHODIMP DragDropTarget::DragEnter(IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
	{
		*pdwEffect = app->onDropEnter(pDataObj, Vector2<long>(pt.x, pt.y));
		return NOERROR; 
	}

	STDMETHODIMP DragDropTarget::DragLeave()
	{
		app->onDropLeave();
		FAcceptFormat = false;
		return NOERROR;
	}

	STDMETHODIMP DragDropTarget::DragOver(DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
	{
		*pdwEffect = app->onDropDragOver(Vector2<long>(pt.x, pt.y));
		return NOERROR;
	}

	STDMETHODIMP DragDropTarget::Drop(IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD*pdwEffect)
	{
		*pdwEffect = app->onDrop(pDataObj, Vector2<long>(pt.x, pt.y));
		return NOERROR;
	}
}