// DRMDropTarget.cpp: implementation of the CDRMDropTarget class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\INCLUDE\DRMDropTarget.h"
#include "..\include\global.h"
#include "..\include\defines.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDRMDropTarget::CDRMDropTarget()
{
	m_pImageList=NULL;
}

CDRMDropTarget::~CDRMDropTarget()
{

}

DROPEFFECT CDRMDropTarget::OnDragEnter( CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point )
{
	if( (!pDataObject->IsDataAvailable( g_nFormatArchive ) ) && (!pDataObject->IsDataAvailable( g_nFormatLineUp ) ) )
		return DROPEFFECT_NONE;

	HGLOBAL hData=pDataObject->GetGlobalData(g_nFormatArchive);
	LPDRAGITEMDATA lpDragItem=(LPDRAGITEMDATA)::GlobalLock(hData);
	m_pImageList = lpDragItem->pDragImage;

	m_pImageList->DragEnter(pWnd,point);

	return DROPEFFECT_COPY;
}

DROPEFFECT CDRMDropTarget::OnDragOver( CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point )
{	
	if( (!pDataObject->IsDataAvailable( g_nFormatArchive ) ) && (!pDataObject->IsDataAvailable( g_nFormatLineUp ) ) )
		return DROPEFFECT_NONE;
	
	DROPEFFECT result;

	HGLOBAL hData=pDataObject->GetGlobalData(g_nFormatArchive);
	LPDRAGITEMDATA lpDragItem=(LPDRAGITEMDATA)::GlobalLock(hData);

	lpDragItem->DropPoint = point;
	lpDragItem->pDragImage->DragMove(point);

	if( pWnd->SendMessage(UM_CANDROP,0,(LPARAM)lpDragItem) )
		if( dwKeyState & MK_SHIFT )
			result = DROPEFFECT_MOVE;
		else
			result = DROPEFFECT_COPY;
	else
		result = DROPEFFECT_NONE;

	return( result );
};

BOOL CDRMDropTarget::OnDrop( CWnd* pWnd, COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point )
{
	if( pDataObject->IsDataAvailable( g_nFormatArchive ) )
	{
		HGLOBAL hData=pDataObject->GetGlobalData(g_nFormatArchive);
		LPDRAGITEMDATA lpDragItem=(LPDRAGITEMDATA)::GlobalLock(hData);
		lpDragItem->pDragImage->DragLeave(pWnd);
		lpDragItem->pDragImage->EndDrag();
		lpDragItem->DropPoint=point;
		pWnd->SendMessage(UM_DROP,dropEffect,(DWORD)lpDragItem);
	}
/*
	if( pDataObject->IsDataAvailable( g_nFormatLineUp ) )
	{
		HGLOBAL hData=pDataObject->GetGlobalData(g_nFormatLineUp);
		typeDRAG_ITEM* lpDragItem=(typeDRAG_ITEM *)::GlobalLock(hData);
		lpDragItem->DropPoint=point;
		pWnd->SendMessage(UM_DROP,0,(DWORD)lpDragItem);
	} */

	return TRUE;
}

void CDRMDropTarget::OnDragLeave( CWnd *pWnd)
{
	if( m_pImageList!=NULL )
	{
		m_pImageList->DragLeave(pWnd);
		m_pImageList=NULL;
		pWnd->SendMessage(UM_DRAGLEAVE);
	}
}