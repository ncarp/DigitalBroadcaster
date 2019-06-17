// MusicWnd.cpp : implementation file
//

#include "stdafx.h"

#include <gdiplus.h>
using namespace Gdiplus;

#include "ExternalObjects.h"
#include "OnAirUtils.h"
#include "OnAir.h"
#include "MusicWnd.h"
#include "OnAirToolBarCtrl.h"
#include "RSViewMusicTracksOnAir.h"
#include "OnAirListBox.h"
#include "..\include\Utils.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMusicWnd

IMPLEMENT_DYNCREATE(CMusicWnd, CFrameWnd)

CMusicWnd::CMusicWnd()
{
}

CMusicWnd::~CMusicWnd()
{
}


BEGIN_MESSAGE_MAP(CMusicWnd, CFrameWnd)
	//{{AFX_MSG_MAP(CMusicWnd)
	ON_WM_CREATE()
	ON_WM_SYSCOMMAND()
	ON_COMMAND(CM_REFRESH, OnRefresh)
	ON_COMMAND(CM_PFL,OnPFL )
	ON_COMMAND(CM_INFO, OnInfo )
	ON_WM_KEYUP()
	ON_WM_SYSKEYUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMusicWnd message handlers

int CMusicWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_pRebar = new CReBar();
//	m_pRebar->Create(this,CCS_NODIVIDER|RBS_BANDBORDERS,WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN|CBRS_BOTTOM);
	m_pRebar->Create(this,CCS_TOP|CCS_NOPARENTALIGN|CCS_NODIVIDER|RBS_AUTOSIZE,WS_VISIBLE|CBRS_BOTTOM);

	CRect	crect;
	GetClientRect( &crect );

	////////////////////////////////////////////////////////////////////
	//	Create the header
	CRect	rectHeader=crect;
	rectHeader.bottom=crect.top+16;

	m_pHeader = new CHeaderCtrl();
	m_pHeader->Create(WS_VISIBLE|HDS_BUTTONS,rectHeader,this,87);

	crect.DeflateRect(0,17,0,67);

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

	return 0;
}

void CMusicWnd::OnSysCommand(UINT nID, LPARAM lParam) 
{
}


void CMusicWnd::OnRefresh() 
{
	if( !m_pList->m_bIsRefreshing )
		AfxBeginThread(ThreadRefreshList,(LPVOID)this->m_pList);
}

UINT CMusicWnd::ThreadRefreshList(LPVOID lpList)
{
	CDatabase	db;
	db.Open(g_strOnAirConnect);
	if( g_bTimeOut ) 
		db.SetQueryTimeout(1);
	else
		db.SetQueryTimeout(360);

	CRSViewMusicTracksOnAir	rs("",&db);

	typeArchiveItem			*lpItem;
	int						Pos=0;
	CString					strPrevArtist="";
	CString					strTemp;
	COnAirListBox			*pList=(COnAirListBox *)lpList;

	pList->m_bIsRefreshing=TRUE;
	pList->ResetContent();

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
	return( 0 );
}

void CMusicWnd::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( !CheckKey(nChar) )
		CFrameWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CMusicWnd::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( !CheckKey(nChar) )
		CFrameWnd::OnSysKeyUp(nChar, nRepCnt, nFlags);
}

void CMusicWnd::OnPFL()
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

void CMusicWnd::OnInfo()
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