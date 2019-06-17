// MusicPlayListWnd.cpp : implementation file
//

#include "stdafx.h"
#include "OnAir.h"
#include "MusicPlayListWnd.h"
#include "OnAirUtils.h"
#include "ExternalObjects.h"
#include "RSViewMusicTracksOnAir.h"
#include "..\include\RSPlayListsDefinition.h"
#include "..\include\Utils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define CM_REFRESH		1001
#define	ID_SELECTION	1002

/////////////////////////////////////////////////////////////////////////////
// CMusicPlayListWnd

IMPLEMENT_DYNCREATE(CMusicPlayListWnd, CFrameWnd)

CMusicPlayListWnd::CMusicPlayListWnd()
{
}

CMusicPlayListWnd::~CMusicPlayListWnd()
{
}


BEGIN_MESSAGE_MAP(CMusicPlayListWnd, CFrameWnd)
	//{{AFX_MSG_MAP(CMusicPlayListWnd)
	ON_WM_SYSCOMMAND()
	ON_WM_KEYUP()
	ON_WM_SYSKEYUP()
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_COMMAND( CM_REFRESH,OnRefresh )
	ON_COMMAND( CM_PFL,OnPFL )
	ON_COMMAND( CM_INFO,OnInfo )
	ON_CBN_SELCHANGE( ID_SELECTION,OnSelChange )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMusicPlayListWnd message handlers

void CMusicPlayListWnd::OnSysCommand(UINT nID, LPARAM lParam) 
{
}

void CMusicPlayListWnd::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( !CheckKey(nChar) )
		CFrameWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CMusicPlayListWnd::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( !CheckKey(nChar) )
		CFrameWnd::OnSysKeyUp(nChar, nRepCnt, nFlags);
}

int CMusicPlayListWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect	crect;
	GetClientRect( &crect );

	////////////////////////////////////////////////////////////////////
	//	Create the combo box control (play list selection)
	m_pSelection = new CComboBoxEx();
	m_pSelection->Create(CBS_DROPDOWNLIST|WS_VISIBLE,CRect(crect.left+40,crect.top+2,crect.right-1,crect.top+402),this,ID_SELECTION);
	m_pSelection->SetFont(g_cfont24);
	m_pSelection->SetImageList(g_ilContainer);
	m_pSelection->EnableWindow(FALSE);

	////////////////////////////////////////////////////////////////////
	//	Create the ReBar control
	m_pRebar = new CReBar();
	m_pRebar->Create(this,RBS_BANDBORDERS,WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN|CBRS_BOTTOM);

	////////////////////////////////////////////////////////////////////
	//	Create the header
	CRect	rectHeader=crect;
	rectHeader.bottom=crect.top+16;
	rectHeader.OffsetRect(0,38);

	m_pHeader = new CHeaderCtrl();
	m_pHeader->Create(WS_VISIBLE|HDS_BUTTONS,rectHeader,this,87);

	crect.DeflateRect(0,55,0,67);

	TBBUTTON	buttons[5];
	buttons[0].iBitmap=0;
	buttons[0].idCommand=CM_REFRESH;
	buttons[0].fsState=TBSTATE_ENABLED;
	buttons[0].fsStyle=TBSTYLE_BUTTON;
	buttons[0].dwData=0;
	buttons[0].iString=0;

	buttons[1].iBitmap=2;
	buttons[1].idCommand=CM_PFL;
	buttons[1].fsState=TBSTATE_ENABLED;
	buttons[1].fsStyle=TBSTYLE_BUTTON;
	buttons[1].dwData=0;
	buttons[1].iString=3;

	buttons[2].iBitmap=3;
	buttons[2].idCommand=CM_INFO;
	buttons[2].fsState=TBSTATE_ENABLED;
	buttons[2].fsStyle=TBSTYLE_BUTTON;
	buttons[2].dwData=0;
	buttons[2].iString=1;

	CToolBarCtrl	*wndToolBar=new CToolBarCtrl();
	CSize			size(40,40);

	wndToolBar->Create(TBSTYLE_FLAT|CCS_BOTTOM,CRect(10,10,100,100),this,292);
	wndToolBar->SetButtonSize(size);
	wndToolBar->SetImageList(g_ilToolEnabled);
	wndToolBar->SetHotImageList(g_ilToolHot);
	wndToolBar->AddStrings(g_lpstrToolLabels);
	wndToolBar->AddButtons(3,buttons);
	wndToolBar->AutoSize();

	m_pRebar->AddBar(wndToolBar,NULL,g_bmToolBackground);

	// Just testing...

	m_pList=new COnAirListBox();
	m_pList->Create(WS_VISIBLE|WS_CHILD|WS_VSCROLL|LBS_NOTIFY|LBS_OWNERDRAWVARIABLE|LBS_NOINTEGRALHEIGHT,crect,this,200);
	m_pList->m_iX1=rectHeader.right-70-GetSystemMetrics(SM_CXVSCROLL);
	m_pList->m_iX2=rectHeader.right-GetSystemMetrics(SM_CXVSCROLL);
	m_pList->SetBackColor(RGB(235,235,255));
	// 
	HDITEM	hdItem;
	CString	strTemp;

	strTemp.LoadString(IDS_TITLE);

	hdItem.mask=HDI_FORMAT|HDI_TEXT|HDI_WIDTH;
	hdItem.pszText=strTemp.GetBuffer(0);
	hdItem.cxy=rectHeader.Width()-140-GetSystemMetrics(SM_CXVSCROLL);
	hdItem.cchTextMax=strTemp.GetLength();
	hdItem.fmt=HDF_CENTER|HDF_STRING;
	m_pHeader->InsertItem(0,&hdItem);

	hdItem.cxy=70;
	strTemp.LoadString(IDS_DURATION);
	hdItem.pszText=strTemp.GetBuffer(0);
	m_pHeader->InsertItem(1,&hdItem);

	strTemp.LoadString(IDS_INTRO);
	hdItem.pszText=strTemp.GetBuffer(0);
	m_pHeader->InsertItem(2,&hdItem);
	m_pHeader->EnableWindow(FALSE);

	OnRefresh();
	
	return 0;
}

void CMusicPlayListWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect	rect;
	GetClientRect(&rect);

	dc.FillRect(&rect,&CBrush(GetSysColor(COLOR_3DFACE)));
}

void CMusicPlayListWnd::OnRefresh()
{
	m_pSelection->ResetContent();
	m_pList->ResetContent();
	m_pSelection->EnableWindow(FALSE);

	CRSPlayListsDefinition	rs(g_strOnAirConnect);
	rs.m_strFilter="Activ <> 0 AND OnAir <> 0";
	rs.m_strSort="Name DESC";
	rs.Open();

	if( rs.GetRecordCount() )
	{
		COMBOBOXEXITEM	cbItem;
		cbItem.mask=CBEIF_IMAGE|CBEIF_SELECTEDIMAGE|CBEIF_INDENT|CBEIF_LPARAM|CBEIF_TEXT;
		cbItem.iItem=0;
		cbItem.pszText=rs.m_Name.GetBuffer(0);
		cbItem.cchTextMax=20;
		cbItem.iImage=6;
		cbItem.iSelectedImage=6;
		cbItem.iIndent=0;

		while( !rs.IsEOF() )
		{
			rs.m_Name.TrimRight();
			cbItem.lParam=rs.m_ID;
			cbItem.pszText=rs.m_Name.GetBuffer(0);
			m_pSelection->InsertItem(&cbItem);
			rs.MoveNext();
		}
		m_pSelection->EnableWindow();
	}	

	rs.Close();
}

void CMusicPlayListWnd::OnSelChange()
{
	if( !m_pList->m_bIsRefreshing )
		AfxBeginThread(ThreadRefreshList,(LPVOID)this);
}


UINT CMusicPlayListWnd::ThreadRefreshList(LPVOID lpv)
{
	CRSViewMusicTracksOnAir	rs(g_strOnAirConnect);
	typeArchiveItem			*lpItem;
	int						Pos=0;
	CString					strPrevArtist="";
	CString					strTemp;
	CMusicPlayListWnd*		pWnd=(CMusicPlayListWnd*)lpv;
	COnAirListBox			*pList=pWnd->m_pList;

	pList->m_bIsRefreshing=TRUE;
	pWnd->m_pSelection->EnableWindow(FALSE);
	pList->ResetContent();

	int iCurSel=pWnd->m_pSelection->GetCurSel();

	if( iCurSel==CB_ERR )
	{
		pList->m_bIsRefreshing=FALSE;
		return 0;
	}
	long	lListID=pWnd->m_pSelection->GetItemData(iCurSel);

	rs.m_strFilter.Format("TrackID in (Select MusicTrackID from [PlayLists-Contents] where ListID = '%d')",lListID);
	rs.m_strSort="ArtistName, TrackTitle";
	rs.Open();

	BOOL bFirstArtist=TRUE;

	while( !rs.IsEOF() )
	{
		// If this a new artist, insert it in the list 
		if( strPrevArtist!=rs.m_ArtistName )
		{
			if( bFirstArtist )
				bFirstArtist=FALSE;
			else
			{
				lpItem = new typeArchiveItem(TYPE_NOTHING,0,"",0);
				pList->InsertString(-1,(LPCTSTR)lpItem);
			}

			strPrevArtist=rs.m_ArtistName;
			rs.m_ArtistName.TrimRight();
			
			lpItem = new typeArchiveItem(TYPE_ARTIST,rs.m_ArtistID,rs.m_ArtistName,0);

			pList->InsertString(-1,(LPCTSTR)lpItem);
		}

		rs.m_TrackTitle.TrimRight();
		lpItem = new typeArchiveItem(TYPE_MUSIC,rs.m_TrackID,rs.m_TrackTitle,rs.m_TrackRythm);
		GetTimeString(rs.m_TrackLength,&(lpItem->strData1));
		lpItem->strData1.Delete(0,3);
		lpItem->strData1.Delete(7,2);

		if( rs.m_TrackIntroTime>0 )
		{
			GetTimeString(rs.m_TrackIntroTime,&(lpItem->strData2));
			lpItem->strData2.Delete(0,4);
			lpItem->strData2.Delete(6,2);
		}
		else
			lpItem->strData2="nd";


		pList->InsertString(-1,(LPCTSTR)lpItem);

		Pos++;
		rs.MoveNext();
	}

	pList->m_bIsRefreshing=FALSE;
	pWnd->m_pSelection->EnableWindow();

	return 0;
}

void CMusicPlayListWnd::OnPFL()
{
	long int lPos=m_pList->GetCurSel();

	if( lPos==LB_ERR )
		return;

	typeArchiveItem* lpItem=(typeArchiveItem*)m_pList->GetItemData(lPos);
	if( lpItem==NULL )
		return;

	if( lpItem->wType==TYPE_MUSIC )
	{
		g_wndPFL->SetSound(lpItem);
		g_wndPFL->RestoreWindow();
	}
}

void CMusicPlayListWnd::OnInfo()
{
	long int lPos=m_pList->GetCurSel();

	if( lPos==LB_ERR )
		return;

	typeArchiveItem* lpItem=(typeArchiveItem*)m_pList->GetItemData(lPos);
	if( lpItem==NULL )
		return;

	CString strURL;
	if( lpItem->wType==TYPE_MUSIC )
	{
		strURL.Format("%s\\OnAirSong.asp?ID=%d&DB=%s",g_strBaseURL,lpItem->lID,g_strDB);
		g_wndMusicInfo->SetView(strURL);
	}
	else
	{
		strURL.Format("%s\\Artist.asp?ID=%d",g_strBaseURL,lpItem->lID);
		g_wndMusicInfo->SetView(strURL);
	}

}
