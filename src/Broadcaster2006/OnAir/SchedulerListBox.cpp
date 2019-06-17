// SchedulerListBox.cpp : implementation file
//

#include "stdafx.h"
#include "onair.h"
#include "SchedulerListBox.h"
#include "OnAirDefines.h"
#include "typeLineUpItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSchedulerListBox

CSchedulerListBox::CSchedulerListBox()
{
}

CSchedulerListBox::~CSchedulerListBox()
{
}


BEGIN_MESSAGE_MAP(CSchedulerListBox, CLineUpListBox)
	//{{AFX_MSG_MAP(CSchedulerListBox)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_MESSAGE( UM_DROP,OnDrop )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSchedulerListBox message handlers

LRESULT CSchedulerListBox::OnDrop(WPARAM,LPARAM lParam)
{
	typeDRAG_ITEM* lpItem=(typeDRAG_ITEM*)lParam;

	BOOL	bOutside=FALSE;
	int		iItemPos=ItemFromPoint(lpItem->DropPoint,bOutside);
	CRect	rect;

	GetItemRect(iItemPos,&rect);
	if(!( (rect.left<lpItem->DropPoint.x) && (rect.right>lpItem->DropPoint.x) && (rect.top<lpItem->DropPoint.y) && (rect.bottom>lpItem->DropPoint.y) ))
		iItemPos=-1;

	if( (lpItem->wType==DRAG_ARCHIVE) )
	{
		SetCurSel(iItemPos);
		///////////////////////////////////////////
		// Insert new item here
		typeArchiveItem *lpNewArchiveItem = (typeArchiveItem *)lpItem->lpItem;
		typeLineUpItem *lpNew = new typeLineUpItem( lpNewArchiveItem->wType,lpNewArchiveItem->lID);
		if( lpNew->m_bItemIsValid )
		{
			InsertString(iItemPos,(LPCTSTR)lpNew);
			GetParent()->SendMessage(UM_DROP);
		}
		else
			delete lpNew;
	}
	else
	{
		InsertString(iItemPos,(LPCTSTR)lpItem->lpItem);
		GetParent()->SendMessage(UM_DROP);
	}

	return 0;
}
