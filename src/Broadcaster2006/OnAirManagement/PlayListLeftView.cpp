// PlayListLeftView.cpp : implementation file
//

#include "stdafx.h"
#include "OnAirManagement.h"
#include "PlayListLeftView.h"
#include "PlayList.h"
#include "..\OnAir\OnAirDefines.h"
#include "..\include\RSPlayListsDefinition.h"
#include "..\common\include\defines.h"
#include "..\common\include\permissions.h"
#include "..\common\include\global.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern UINT g_nFormat;
/////////////////////////////////////////////////////////////////////////////
// CPlayListLeftView

IMPLEMENT_DYNCREATE(CPlayListLeftView, CDigitalLeftView)

CPlayListLeftView::CPlayListLeftView()
{
}

CPlayListLeftView::~CPlayListLeftView()
{
}


BEGIN_MESSAGE_MAP(CPlayListLeftView, CDigitalLeftView)
	//{{AFX_MSG_MAP(CPlayListLeftView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlayListLeftView drawing

void CPlayListLeftView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CPlayListLeftView diagnostics

#ifdef _DEBUG
void CPlayListLeftView::AssertValid() const
{
	CDigitalLeftView::AssertValid();
}

void CPlayListLeftView::Dump(CDumpContext& dc) const
{
	CDigitalLeftView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPlayListLeftView message handlers

void CPlayListLeftView::OnInitialUpdate() 
{
	CDigitalLeftView::OnInitialUpdate();
	
	CString	str;
	str.LoadString(IDS_PLAYLISTMANAGEMENT);
	m_pDocument->SetTitle(str+" - "+m_strRadio);

	if( g_Permissions.bOnAirManagement )
		AfxBeginThread(RefreshList,(LPVOID)this);
	else
		m_pDocument->SetTitle(str+" - "+m_strRadio+" - Acesso negado!");
}

UINT CPlayListLeftView::RefreshList(LPVOID lp)
{
	CPlayListLeftView *pView = (CPlayListLeftView*)lp;
	CTreeCtrl	*pTree = &pView->GetTreeCtrl();
	HTREEITEM	hItem;
	typeTreeItem *lpItem;
	CString		str;

	str.LoadString(IDS_DISCOGRAPHY);
	lpItem = new typeTreeItem;
	lpItem->lID = 1;
	lpItem->wType = 0;
	hItem = pTree->InsertItem(str,17,17);
	pTree->SetItemData(hItem,(DWORD)lpItem);

	str.LoadString(IDS_NOTLISTED);
	lpItem = new typeTreeItem;
	lpItem->lID = 2;
	lpItem->wType = 0;
	hItem = pTree->InsertItem(str,15,15);
	pTree->SetItemData(hItem,(DWORD)lpItem);

	CRSPlayListsDefinition rs( pView->m_strConnect );
	rs.m_strFilter = "Activ = 1";
	rs.m_strSort = "Name";
	rs.Open();

	while( !rs.IsEOF() )
	{
		rs.m_Name.TrimRight();

		lpItem = new typeTreeItem;
		lpItem->lID = rs.m_ID;
		lpItem->wType = TYPE_PLAYLIST;

		hItem = pTree->InsertItem(rs.m_Name,16,16);
		pTree->SetItemData(hItem,(DWORD)lpItem);

		rs.MoveNext();
	}
	rs.Close();

	return 0;
}

void CPlayListLeftView::OnSelChange()
{
	CTreeCtrl *pTree=&GetTreeCtrl();
	HTREEITEM hItem = pTree->GetSelectedItem();

	if( hItem==NULL )
		return;

	typeTreeItem *lpItem=(typeTreeItem *)pTree->GetItemData(hItem);
	if( lpItem==NULL )
		return;

	m_rightView->SetPlayList(lpItem->wType,lpItem->lID);
}

void CPlayListLeftView::OnNew()
{
	if( !g_Permissions.bPlayListAdd )
		return;


	CPlayList dl;
	dl.m_strConnect = m_strConnect;

	if( dl.DoModal()==IDOK )
	{
		CRSPlayListsDefinition rs( m_strConnect );
		rs.m_strSort="ID DESC";

		rs.Open();
		rs.AddNew();
		rs.m_Activ = 1;
		rs.m_Name = dl.m_Name;
		if( dl.m_OnAir )
			rs.m_OnAir = 1;
		else
			rs.m_OnAir = 0;
		rs.Update();
		rs.Requery();

		typeTreeItem *lpItem = new typeTreeItem;
		lpItem->lID = rs.m_ID;
		lpItem->wType = TYPE_PLAYLIST;

		CTreeCtrl *pTree = &GetTreeCtrl();
		HTREEITEM hItem = pTree->InsertItem(dl.m_Name,16,16);
		pTree->SetItemData(hItem,(DWORD)lpItem);
		
		WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_ADD,TYPE_PLAYLIST,lpItem->lID,m_lRadioID);
	}
}

void CPlayListLeftView::OnDoubleClick()
{
	if( !g_Permissions.bPlayListEdit )
		return;

	CTreeCtrl		*pTree = &GetTreeCtrl();
	HTREEITEM		hItem = pTree->GetSelectedItem();

	if( hItem==NULL )
		return;

	LPtypeTreeItem	lpItem = (LPtypeTreeItem)pTree->GetItemData(hItem);

	if( lpItem==NULL )
		return;

	if( lpItem->wType == TYPE_PLAYLIST )
	{
		CRSPlayListsDefinition rs( m_strConnect );
		rs.m_strFilter.Format("ID = %d",lpItem->lID);
		rs.Open();
		if( rs.GetRecordCount() )
		{
			CPlayList dl;
			rs.m_Name.TrimRight();

			dl.m_strConnect = m_strConnect;
			dl.m_Name = rs.m_Name;
			dl.m_OnAir = rs.m_OnAir;
			dl.m_ID = rs.m_ID;
			if( dl.DoModal()==IDOK )
			{
				rs.Edit();
				rs.m_Activ=1;
				rs.m_Name=dl.m_Name;
				if( dl.m_OnAir )
					rs.m_OnAir=1;
				else
					rs.m_OnAir=0;
				rs.Update();
				pTree->SetItemText(hItem,dl.m_Name);

				WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_EDIT,TYPE_PLAYLIST,lpItem->lID,m_lRadioID);
			}
		}
		rs.Close();
	}
}

void CPlayListLeftView::OnCut()
{
	if( !g_Permissions.bPlayListCut )
		return;

	CTreeCtrl		*pTree = &GetTreeCtrl();
	HTREEITEM		hItem = pTree->GetSelectedItem();

	if( hItem==NULL )
		return;

	LPtypeTreeItem	lpItem = (LPtypeTreeItem)pTree->GetItemData(hItem);

	if( lpItem==NULL )
		return;

	if( lpItem->wType == TYPE_PLAYLIST )
	{
		if( AfxMessageBox(IDS_CONFIRMPLAYLISTREMOVE,MB_YESNO)==IDYES )
		{
			CDatabase	db;
			CString		strSQL;

			strSQL.Format("DELETE FROM [PLayLists-Def] WHERE ID = %d",lpItem->lID );
			db.Open(m_strConnect);
			db.ExecuteSQL(strSQL);

			strSQL.Format("DELETE FROM [PlayLists-Contents] WHERE ListID = %d", lpItem->lID );
			db.ExecuteSQL(strSQL);
			db.Close();

			WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_CUT,TYPE_PLAYLIST,lpItem->lID,m_lRadioID);
			pTree->DeleteItem(hItem);
		}
	}
}

BOOL CPlayListLeftView::OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point) 
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

	if( m_lpDragItem->Item.wType!=TYPE_MUSIC )
		return DROPEFFECT_NONE;

	typeTreeItem *lpItem=(typeTreeItem *)pTree->GetItemData(hItem);
	if( lpItem==NULL )
		return DROPEFFECT_NONE;

	if( lpItem->wType != TYPE_PLAYLIST )
		return DROPEFFECT_NONE;

	CString		strSQL;
	CDatabase	db;

	strSQL.Format("DELETE From [PlayLists-Contents] WHERE ListID = %d AND MusicTrackID = %d",
		lpItem->lID,
		m_lpDragItem->Item.lID );

	db.Open(m_strConnect);
	db.ExecuteSQL(strSQL);

	strSQL.Format("INSERT INTO [PlayLists-Contents] (ListID,MusicTrackID) VALUES (%d,%d)",
		lpItem->lID,
		m_lpDragItem->Item.lID );

	db.ExecuteSQL(strSQL);
	db.Close();

	WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_ADDTOPLAYLIST,TYPE_PLAYLIST,lpItem->lID,m_lRadioID,m_lpDragItem->Item.lID);

	m_lpDragItem=NULL;

	pTree->SelectDropTarget(NULL);

	return dropEffect;
}

DROPEFFECT CPlayListLeftView::OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) 
{
	if( !pDataObject->IsDataAvailable( g_nFormat ) )
		return DROPEFFECT_NONE;

	HGLOBAL hData=pDataObject->GetGlobalData(g_nFormat);
	m_lpDragItem=(typeTreeDrag *)::GlobalLock(hData);

	if( m_lpDragItem->Item.wType != TYPE_MUSIC )
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

DROPEFFECT CPlayListLeftView::OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) 
{
	CDigitalLeftView::OnDragOver(pDataObject, dwKeyState, point);

	if( !g_Permissions.bPlayListEditContent )
		return DROPEFFECT_NONE;

	CTreeCtrl	*pTree=&GetTreeCtrl();
	UINT		uFlags;

	HTREEITEM hItem=pTree->HitTest(point,&uFlags);
	
	if ((hItem != NULL) && (TVHT_ONITEM & uFlags))
	{
		typeTreeItem *lpItem = (typeTreeItem *)pTree->GetItemData(hItem);
		if( lpItem != NULL )
		{
			if( lpItem->wType == TYPE_PLAYLIST )
			{
				HTREEITEM hDrop=pTree->GetDropHilightItem();
				if( hDrop!=hItem )
				{
					DrawDragItem(m_lpDragItem->strName,point);
					pTree->SelectDropTarget(hItem);
					DrawDragItem(m_lpDragItem->strName,point);
				}
		
				if( dwKeyState & MK_SHIFT )
					return DROPEFFECT_MOVE;
				else
					return DROPEFFECT_COPY;
			}
		}
	}

	HTREEITEM hDrop=pTree->GetDropHilightItem();
	if( hDrop!=NULL )
	{
		DrawDragItem(m_lpDragItem->strName,point);
		pTree->SelectDropTarget(NULL);
		DrawDragItem(m_lpDragItem->strName,point);
	}
	return DROPEFFECT_NONE;
}
