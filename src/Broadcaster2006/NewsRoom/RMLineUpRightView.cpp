// RMLineUpRightView.cpp : implementation file
//

#include "stdafx.h"
#include "NewsRoom.h"
#include "RMLineUpRightView.h"
#include "..\include\CartwallComponents.h"
#include "..\include\RSViewRMS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern	CString g_strMainConnect;
extern	UINT	g_nFormat;
/////////////////////////////////////////////////////////////////////////////
// CRMLineUpRightView

IMPLEMENT_DYNCREATE(CRMLineUpRightView, CDigitalLeftView)

CRMLineUpRightView::CRMLineUpRightView()
{
}

CRMLineUpRightView::~CRMLineUpRightView()
{
}


BEGIN_MESSAGE_MAP(CRMLineUpRightView, CDigitalLeftView)
	//{{AFX_MSG_MAP(CRMLineUpRightView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRMLineUpRightView drawing

void CRMLineUpRightView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CRMLineUpRightView diagnostics

#ifdef _DEBUG
void CRMLineUpRightView::AssertValid() const
{
	CDigitalLeftView::AssertValid();
}

void CRMLineUpRightView::Dump(CDumpContext& dc) const
{
	CDigitalLeftView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRMLineUpRightView message handlers
void CRMLineUpRightView::SetCartView(long ID)
{
	m_ID = ID;

	CTreeCtrl *pTree=&GetTreeCtrl();
	pTree->DeleteAllItems();

	CString		str;
	HTREEITEM	hItem;
	typeTreeItem *lpItem;

	CCartwallComponents rs( m_strConnect );
	rs.m_strFilter.Format("CartwallID = %d",ID);
	rs.m_strSort="Position";
	rs.Open();
	
	CRSViewRms rsRM( g_strMainConnect );
	
	while( !rs.IsEOF() )
	{
		str.Format("%d -",rs.m_Position+1);
		lpItem = new typeTreeItem;
		lpItem->lID = rs.m_Position;
		lpItem->wType=0;

		if( rs.m_Type == TYPE_RM )
		{
			rsRM.m_strFilter.Format("ID = %d",rs.m_ElementID);
			if( rsRM.IsOpen() )
				rsRM.Requery();
			else
				rsRM.Open();

			if( rsRM.GetRecordCount() )
			{
				rsRM.m_Type.TrimRight();
				str+=(rsRM.m_Type+" - "+rsRM.m_Name);
				str.TrimRight();
			}
		}
		hItem=pTree->InsertItem(str,12,12);
		pTree->SetItemData(hItem,(DWORD)lpItem);

		rs.MoveNext();
	}
}

DROPEFFECT CRMLineUpRightView::OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) 
{
	CDigitalLeftView::OnDragOver(pDataObject, dwKeyState, point);

	CTreeCtrl	*pTree=&GetTreeCtrl();
	UINT		uFlags;

	HTREEITEM hItem=pTree->HitTest(point,&uFlags);
	
	if ((hItem != NULL) && (TVHT_ONITEM & uFlags))
	{
//		pTree->SelectDropTarget(hItem);
		return DROPEFFECT_COPY;
	}
	else
	{
//		pTree->SelectDropTarget(NULL);
		return DROPEFFECT_NONE;
	}
}

DROPEFFECT CRMLineUpRightView::OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) 
{
	if( !pDataObject->IsDataAvailable( g_nFormat ) )
		return DROPEFFECT_NONE;

	HGLOBAL hData=pDataObject->GetGlobalData(g_nFormat);
	m_lpDragItem=(typeTreeDrag *)::GlobalLock(hData);

	if( m_lpDragItem->Item.wType != TYPE_RM )
	{
		::GlobalUnlock(hData);
		m_lpDragItem=NULL;
		return DROPEFFECT_NONE;
	}

	CTreeCtrl	*pTree=&GetTreeCtrl();
	UINT		uFlags;

	HTREEITEM hItem=pTree->HitTest(point,&uFlags);
	if ((hItem != NULL) && (TVHT_ONITEM & uFlags))
		return DROPEFFECT_COPY;
	else
		return DROPEFFECT_NONE;
}

BOOL CRMLineUpRightView::OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point) 
{
	if( m_lpDragItem==NULL )
		return DROPEFFECT_NONE;

	DrawDragItem(m_lpDragItem->strName,m_OldPoint);
	m_OldPoint.x=m_OldPoint.y=-32000;

	CTreeCtrl	*pTree=&GetTreeCtrl();
	UINT		uFlags;

	HTREEITEM hItem=pTree->HitTest(point,&uFlags);
	if( (hItem == NULL) || !(TVHT_ONITEM & uFlags))
	{
		m_lpDragItem=NULL;
		return DROPEFFECT_NONE;
	}

	if( m_lpDragItem->Item.wType!=TYPE_RM )
		return DROPEFFECT_NONE;

	pTree->SetItemText(hItem,m_lpDragItem->strName);

	typeTreeItem *lpItem=(typeTreeItem *)pTree->GetItemData(hItem);
	CString		strSQL;
	CDatabase	db;

	strSQL.Format("UPDATE CartwallContents SET Type = %d, ElementID = %d WHERE CartwallID = %d AND Position = %d",
		m_lpDragItem->Item.wType,
		m_lpDragItem->Item.lID,
		m_ID,
		lpItem->lID );

	db.Open(m_strConnect);
	db.ExecuteSQL(strSQL);
	db.Close();

	m_lpDragItem=NULL;
	return DROPEFFECT_COPY;
}

void CRMLineUpRightView::OnDoubleClick()
{
	CTreeCtrl *pTree=&GetTreeCtrl();
	HTREEITEM hItem=pTree->GetSelectedItem();

	if( hItem==NULL )
		return;

	typeTreeItem *lpItem=(typeTreeItem *)pTree->GetItemData(hItem);
	if( lpItem==NULL )
		return;

	CString		str;
	str.Format("%d -",lpItem->lID);
	pTree->SetItemText(hItem,str);

	CDatabase	db;
	CString		strSQL;

	strSQL.Format("UPDATE CartwallContents SET Type = 0, ElementID = 0 WHERE CartwallID = %d AND Position = %d",
		m_ID,
		lpItem->lID );

	db.Open(m_strConnect);
	db.ExecuteSQL(strSQL);
	db.Close();
}