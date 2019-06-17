#include "stdafx.h"
#include "OnAirDropTarget.h"
#include "ExternalObjects.h"

COnAirDropTarget::COnAirDropTarget()
{
}

COnAirDropTarget::~COnAirDropTarget()
{
}

DROPEFFECT COnAirDropTarget::OnDragEnter( CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point )
{
	if( (!pDataObject->IsDataAvailable( g_nFormatArchive ) ) && (!pDataObject->IsDataAvailable( g_nFormatLineUp ) ) )
		return DROPEFFECT_NONE;

	return DROPEFFECT_COPY;
}

DROPEFFECT COnAirDropTarget::OnDragOver( CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point )
{	
	if( (!pDataObject->IsDataAvailable( g_nFormatArchive ) ) && (!pDataObject->IsDataAvailable( g_nFormatLineUp ) ) )
		return DROPEFFECT_NONE;

	if( pWnd->SendMessage(UM_CANDROP) )
		return DROPEFFECT_COPY;
	else
		return DROPEFFECT_NONE;
};

BOOL COnAirDropTarget::OnDrop( CWnd* pWnd, COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point )
{
	BOOL bResult;
	if( pDataObject->IsDataAvailable( g_nFormatArchive ) )
	{
		HGLOBAL hData=pDataObject->GetGlobalData(g_nFormatArchive);
		typeDRAG_ITEM* lpDragItem=(typeDRAG_ITEM *)::GlobalLock(hData);
		lpDragItem->DropPoint=point;
		bResult = (pWnd->SendMessage(UM_DROP,0,(DWORD)lpDragItem)!=DROPEFFECT_NONE);
	}

	if( pDataObject->IsDataAvailable( g_nFormatLineUp ) )
	{
		HGLOBAL hData=pDataObject->GetGlobalData(g_nFormatLineUp);
		typeDRAG_ITEM* lpDragItem=(typeDRAG_ITEM *)::GlobalLock(hData);
		lpDragItem->DropPoint=point;
		bResult = (pWnd->SendMessage(UM_DROP,0,(DWORD)lpDragItem) != DROPEFFECT_NONE);
	}
	return bResult;
}