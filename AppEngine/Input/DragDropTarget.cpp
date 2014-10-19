
#include "DragDropTarget.h"
#include "../Application.h"

namespace AppEngine
{
	DragDropTarget::DragDropTarget(Application* app)
	{
		this->app = app;
	}

	STDMETHODIMP DragDropTarget::QueryInterface(REFIID riid, void **ppv)
	{
		return S_OK;
	}

	STDMETHODIMP_(ULONG) DragDropTarget::AddRef()
	{
		return S_OK;
	}

	STDMETHODIMP_(ULONG) DragDropTarget::Release()
	{
		return S_OK;
	}

	STDMETHODIMP DragDropTarget::DragEnter(IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
	{
		*pdwEffect = app->onDropEnter(pDataObj, Vector2<long>(pt.x, pt.y));
		return S_OK;
	}

	STDMETHODIMP DragDropTarget::DragLeave()
	{
		app->onDropLeave();
		return S_OK;
	}

	STDMETHODIMP DragDropTarget::DragOver(DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
	{
		*pdwEffect = app->onDropDragOver(Vector2<long>(pt.x, pt.y));
		return S_OK;
	}

	STDMETHODIMP DragDropTarget::Drop(IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD*pdwEffect)
	{
		*pdwEffect = app->onDrop(pDataObj, Vector2<long>(pt.x, pt.y));
		return S_OK;
	}
}