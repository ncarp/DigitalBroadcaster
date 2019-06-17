// PlayListRightView.cpp : implementation file
//

#include "stdafx.h"
#include "OnAirManagement.h"
#include "PlayListRightView.h"
#include "..\OnAir\PFLWnd.h"
#include "..\include\rsViewDiscography.h"
#include "..\include\RSPlayListsDefinition.H"
#include "..\common\include\defines.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CString	g_strMainConnect;
extern CPFLWnd	*g_wndPFL;

/////////////////////////////////////////////////////////////////////////////
// CPlayListRightView

IMPLEMENT_DYNCREATE(CPlayListRightView, CDigitalLeftView)

CPlayListRightView::CPlayListRightView()
{
	m_IsRefreshing = FALSE;
}

CPlayListRightView::~CPlayListRightView()
{
}


BEGIN_MESSAGE_MAP(CPlayListRightView, CDigitalLeftView)
	//{{AFX_MSG_MAP(CPlayListRightView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlayListRightView drawing

void CPlayListRightView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CPlayListRightView diagnostics

#ifdef _DEBUG
void CPlayListRightView::AssertValid() const
{
	CDigitalLeftView::AssertValid();
}

void CPlayListRightView::Dump(CDumpContext& dc) const
{
	CDigitalLeftView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPlayListRightView message handlers
void CPlayListRightView::SetPlayList(WORD wType,long lID)
{
	if( m_IsRefreshing )
		return;
	
	if( (wType==0) && (lID==1) )
	{
		m_PlayList=0;
		AfxBeginThread(FillWithAll,(LPVOID)this);
	}

	if( (wType==0) && (lID==2) )
	{
		m_PlayList=0;
		AfxBeginThread(FillWithNotListed,(LPVOID)this);
	}

	if( (wType==TYPE_PLAYLIST) )
	{
		m_PlayList = lID;
		AfxBeginThread(FillWithPlayList,(LPVOID)this);
	}
}

UINT CPlayListRightView::FillWithAll( LPVOID lp )
{
	CPlayListRightView *pView = (CPlayListRightView *)lp;
	CTreeCtrl	*pTree = &pView->GetTreeCtrl();

	pView->m_IsRefreshing=TRUE;
	pTree->DeleteAllItems();

	CRSViewDiscography	rs( pView->m_strConnect );
	CString		strPrev;
	HTREEITEM	hArtist,
				hMusic;
	typeTreeItem *lpItem;

	rs.m_strSort = "Artist, Title";
	rs.Open();

	while( !rs.IsEOF() )
	{
		if( strPrev!=rs.m_Artist )
		{
			strPrev = rs.m_Artist;
			rs.m_Artist.TrimRight();

			hArtist = pTree->InsertItem(rs.m_Artist,16,16);
			pTree->SetItemData(hArtist,0);
			pTree->SetItemState(hArtist,TVIS_BOLD,TVIS_BOLD);
		}
		rs.m_Title.TrimRight();

		lpItem = new typeTreeItem;
		lpItem->lID=rs.m_ID;
		lpItem->wType=TYPE_MUSIC;

		hMusic = pTree->InsertItem(rs.m_Title,17,17,hArtist);
		pTree->SetItemData(hMusic,(DWORD)lpItem);

		rs.MoveNext();
	}

	pView->m_IsRefreshing=FALSE;
	return 0;
}

UINT CPlayListRightView::FillWithNotListed( LPVOID lp )
{
	CPlayListRightView *pView = (CPlayListRightView *)lp;
	CTreeCtrl	*pTree = &pView->GetTreeCtrl();

	pView->m_IsRefreshing=TRUE;
	pTree->DeleteAllItems();

	CRSViewDiscography	rs( pView->m_strConnect );
	CString		strPrev;
	HTREEITEM	hArtist,
				hMusic;
	typeTreeItem *lpItem;

	rs.m_strFilter = "ID NOT IN (Select MusicTrackID FROM [PlayLists-Contents])";
	rs.m_strSort = "Artist, Title";
	rs.Open();

	while( !rs.IsEOF() )
	{
		if( strPrev!=rs.m_Artist )
		{
			strPrev = rs.m_Artist;
			rs.m_Artist.TrimRight();

			hArtist = pTree->InsertItem(rs.m_Artist,16,16);
			pTree->SetItemData(hArtist,0);
			pTree->SetItemState(hArtist,TVIS_BOLD,TVIS_BOLD);
		}
		rs.m_Title.TrimRight();

		lpItem = new typeTreeItem;
		lpItem->lID=rs.m_ID;
		lpItem->wType=TYPE_MUSIC;

		hMusic = pTree->InsertItem(rs.m_Title,17,17,hArtist);
		pTree->SetItemData(hMusic,(DWORD)lpItem);

		rs.MoveNext();
	}

	pView->m_IsRefreshing=FALSE;
	return 0;
}

UINT CPlayListRightView::FillWithPlayList( LPVOID lp )
{
	CPlayListRightView *pView = (CPlayListRightView *)lp;
	CTreeCtrl	*pTree = &pView->GetTreeCtrl();

	pView->m_IsRefreshing=TRUE;
	pTree->DeleteAllItems();

	CRSViewDiscography	rs( pView->m_strConnect );
	CString		strPrev;
	HTREEITEM	hArtist,
				hMusic;
	typeTreeItem *lpItem;

	rs.m_strFilter.Format("ID IN (Select MusicTrackID FROM [PlayLists-Contents] WHERE ListID = %d)",pView->m_PlayList);
	rs.m_strSort = "Artist, Title";
	rs.Open();

	while( !rs.IsEOF() )
	{
		if( strPrev!=rs.m_Artist )
		{
			strPrev = rs.m_Artist;
			rs.m_Artist.TrimRight();

			hArtist = pTree->InsertItem(rs.m_Artist,16,16);
			pTree->SetItemData(hArtist,0);
			pTree->SetItemState(hArtist,TVIS_BOLD,TVIS_BOLD);
		}
		rs.m_Title.TrimRight();

		lpItem = new typeTreeItem;
		lpItem->lID=rs.m_ID;
		lpItem->wType=TYPE_MUSIC;

		hMusic = pTree->InsertItem(rs.m_Title,17,17,hArtist);
		pTree->SetItemData(hMusic,(DWORD)lpItem);

		rs.MoveNext();
	}

	pView->m_IsRefreshing=FALSE;
	return 0;
}

void CPlayListRightView::OnPFL() 
{
	CTreeCtrl		*pTree = &GetTreeCtrl();
	HTREEITEM		hItem = pTree->GetSelectedItem();
	LPtypeTreeItem	lpItem = (LPtypeTreeItem)pTree->GetItemData(hItem);
	CString			strURL;

	if( lpItem==NULL )
		return;
	
	if( lpItem->wType!=TYPE_MUSIC)
		return;

	g_wndPFL->SetSound(TYPE_MUSIC,lpItem->lID);
	g_wndPFL->RestoreWindow();
}

void CPlayListRightView::OnSelChange()
{
	CTreeCtrl		*pTree = &GetTreeCtrl();
	HTREEITEM		hItem = pTree->GetSelectedItem();
	LPtypeTreeItem	lpItem = (LPtypeTreeItem)pTree->GetItemData(hItem);
	CString			str="";

	m_wndStatusBar->SetPaneText(0,"");

	if( lpItem==NULL )
		return;

	if( lpItem->wType!=TYPE_MUSIC)
		return;

	CRSPlayListsDefinition rs( m_strConnect );
	rs.m_strFilter.Format("ID IN (SELECT ListID FROM [PlayLists-Contents] WHERE MusicTrackID = %d)",lpItem->lID);
	rs.m_strSort="Name";
	rs.Open();

	if( rs.GetRecordCount() )
		while( !rs.IsEOF() )
		{
			rs.m_Name.TrimRight();
			str+=rs.m_Name+", ";
			rs.MoveNext();
		}
	rs.Close();	
	
	
	m_wndStatusBar->SetPaneText(0,str);
}

void CPlayListRightView::OnDragMove()
{
	CTreeCtrl		*pTree = &GetTreeCtrl();
	HTREEITEM		hItem = pTree->GetSelectedItem();
	LPtypeTreeItem	lpItem = (LPtypeTreeItem)pTree->GetItemData(hItem);
	CString			str="";

	m_wndStatusBar->SetPaneText(0,"");

	if( lpItem==NULL )
		return;

	if( lpItem->wType!=TYPE_MUSIC)
		return;

	CDatabase	db;
	CString		strSQL;

	strSQL.Format("DELETE From [PlayLists-Contents] WHERE ListID = %d AND MusicTrackID = %d",
		m_PlayList,
		lpItem->lID );

	db.Open(m_strConnect);
	db.ExecuteSQL( strSQL);
	db.Close();

	WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_CUTFROMPLAYLIST,TYPE_PLAYLIST,m_PlayList,m_lRadioID,lpItem->lID);

	pTree->DeleteItem(hItem);
}

void CPlayListRightView::OnCut()
{
	if( !g_Permissions.bPlayListEditContent )
		return;

	if( m_PlayList==0 )
		return;

	CTreeCtrl		*pTree = &GetTreeCtrl();
	HTREEITEM		hItem = pTree->GetSelectedItem();
	LPtypeTreeItem	lpItem = (LPtypeTreeItem)pTree->GetItemData(hItem);
	CString			strURL;

	if( lpItem==NULL )
		return;
	
	if( lpItem->wType!=TYPE_MUSIC)
		return;

	CDatabase	db;
	CString		strSQL;

	strSQL.Format("DELETE From [PlayLists-Contents] WHERE ListID = %d AND MusicTrackID = %d",
		m_PlayList,
		lpItem->lID );

	db.Open(m_strConnect);
	db.ExecuteSQL( strSQL);
	db.Close();

	WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_CUTFROMPLAYLIST,TYPE_PLAYLIST,m_PlayList,m_lRadioID,lpItem->lID);
	pTree->DeleteItem(hItem);
}

void CPlayListRightView::OnDoubleClick()
{
	OnPFL();
}

void CPlayListRightView::OnRDoubleClick()
{
	OnPFL();
}

void CPlayListRightView::OnInfo()
{
	CTreeCtrl		*pTree = &GetTreeCtrl();
	HTREEITEM		hItem = pTree->GetSelectedItem();

	if( hItem ==NULL )
		return;

	LPtypeTreeItem	lpItem = (LPtypeTreeItem)pTree->GetItemData(hItem);
	CString			strURL;

	if( lpItem==NULL )
		return;
	
	if( lpItem->wType!=TYPE_MUSIC)
		return;

	strURL.Format("%s/OnAirSong.asp?ID=%d&DB=%s",
		g_strBaseURL,
		lpItem->lID,
		m_strDB );

	g_wndInfo->SetView(strURL);
}