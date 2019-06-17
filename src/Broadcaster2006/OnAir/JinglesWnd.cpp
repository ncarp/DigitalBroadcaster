#include "..\instoremedia\jingleswnd.h"
// JinglesWnd.cpp : implementation file
//

#include "stdafx.h"

#include <gdiplus.h>
using namespace Gdiplus;

#include "OnAir.h"
#include "JinglesWnd.h"
#include "RSViewJinglesOnAir.h"
#include "ExternalObjects.h"
#include "OnAirUtils.h"
#include "..\include\utils.h"
#include ".\jingleswnd.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CJinglesWnd

IMPLEMENT_DYNCREATE(CJinglesWnd, CFrameWnd)

CJinglesWnd::CJinglesWnd()
{
}

CJinglesWnd::~CJinglesWnd()
{
}


BEGIN_MESSAGE_MAP(CJinglesWnd, CFrameWnd)
	//{{AFX_MSG_MAP(CJinglesWnd)
	ON_WM_CREATE()
	ON_WM_SYSCOMMAND()
	ON_WM_KEYUP()
	ON_WM_SYSKEYUP()
	ON_COMMAND(CM_REFRESH,OnRefresh)
	ON_COMMAND(CM_PFL,OnPFL)
	//}}AFX_MSG_MAP
	ON_WM_NCPAINT()
	ON_WM_PAINT()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJinglesWnd message handlers

int CJinglesWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_pRebar = new CReBar();
	m_pRebar->Create(this,RBS_BANDBORDERS,WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN|CBRS_BOTTOM);

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

	CToolBarCtrl	*wndToolBar=new CToolBarCtrl();
	CSize			size(40,40);

	wndToolBar->Create(TBSTYLE_FLAT|CCS_BOTTOM,CRect(10,10,100,100),this,292);
	wndToolBar->SetButtonSize(size);
	wndToolBar->SetImageList(g_ilToolEnabled);
	wndToolBar->SetHotImageList(g_ilToolHot);
	wndToolBar->AddStrings(g_lpstrToolLabels);
	wndToolBar->AddButtons(2,buttons);
	wndToolBar->AutoSize();

	m_pRebar->AddBar(wndToolBar,NULL,g_bmToolBackground);

	// Just testing...

	m_pList=new COnAirListBox();
	m_pList->Create(WS_VISIBLE|WS_CHILD|WS_VSCROLL|LBS_NOTIFY|LBS_OWNERDRAWVARIABLE|LBS_NOINTEGRALHEIGHT,crect,this,200);
	m_pList->m_iX1=rectHeader.right-70-GetSystemMetrics(SM_CXVSCROLL);
	m_pList->m_iX2=rectHeader.right-GetSystemMetrics(SM_CXVSCROLL);
	m_pList->SetBackColor(RGB(250,250,225));
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

void CJinglesWnd::OnSysCommand(UINT nID, LPARAM lParam) 
{
}

void CJinglesWnd::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( !CheckKey(nChar) )
		CFrameWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CJinglesWnd::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( !CheckKey(nChar) )
		CFrameWnd::OnSysKeyUp(nChar, nRepCnt, nFlags);
}

void CJinglesWnd::OnRefresh() 
{
	// Log Item -----------------------------------------------------------------------
	typeLogItem *lpLog=new typeLogItem;
	lpLog->wType = 0;
	lpLog->lID = 0;
	lpLog->lTraffic = 0;
	strcpy(lpLog->strName,"--> Refresh Jingles List");
	g_wndAired->LogItem(lpLog);
	// --------------------------------------------------------------------------------

	if( !m_pList->m_bIsRefreshing )
		AfxBeginThread(ThreadRefreshList,(LPVOID)this->m_pList);
}


UINT CJinglesWnd::ThreadRefreshList(LPVOID lp)
{
	CRSViewJinglesOnAir	rs(g_strOnAirConnect);
	COnAirListBox*		pList=(COnAirListBox*)lp;
	CTime				time=CTime::GetCurrentTime();
	CString				strTime;
	CString				strPrevType="";
	CString				strLength;
	CString				strIntro;
	typeArchiveItem*	lpItem;

	pList->m_bIsRefreshing=TRUE;
	pList->ResetContent();

	strTime.Format("%d-%d-%d",time.GetYear(),time.GetMonth(),time.GetDay() );

	rs.m_strSort="JingleType, Name";
	rs.m_strFilter.Format("EndingDate >= '%s' AND StartingDate <= '%s'",strTime,strTime);
	rs.Open();

	BOOL bFirstArtist=TRUE;

	while( !rs.IsEOF() )
	{
		if( rs.m_JingleType!=strPrevType )
		{
			if( bFirstArtist )
				bFirstArtist=FALSE;
			else
			{
				lpItem = new typeArchiveItem(TYPE_NOTHING,0,"",0);
				pList->InsertString(-1,(LPCTSTR)lpItem);
			}

			strPrevType=rs.m_JingleType;
			rs.m_JingleType.TrimRight();

			lpItem = new typeArchiveItem(TYPE_JINGLETYPE,rs.m_JingleID,rs.m_JingleType,rs.m_Rythm);
			
			pList->InsertString(-1,(LPCTSTR)lpItem);
		}
		rs.m_Name.TrimRight();

		GetTimeString(rs.m_Length,&strLength);
		strLength.Delete(0,3);
		strLength.Delete(7,2);

		if( rs.m_Intro>0 )
		{
			GetTimeString(rs.m_Intro,&strIntro);
			strIntro.Delete(0,4);
			strIntro.Delete(6,2);
		}
		else
			strIntro="nd";

		lpItem = new typeArchiveItem(TYPE_JINGLE,rs.m_JingleID,rs.m_Name,rs.m_Rythm,strLength,strIntro);
			
		pList->InsertString(-1,(LPCTSTR)lpItem);

		rs.MoveNext();
	}
	rs.Close();
	pList->m_bIsRefreshing=FALSE;

	return 0;
}

void CJinglesWnd::OnPFL()
{
	long int lPos=m_pList->GetCurSel();

	if( lPos==LB_ERR )
		return;

	typeArchiveItem* lpItem=(typeArchiveItem*)m_pList->GetItemData(lPos);
	if( lpItem==NULL )
		return;

	if( lpItem->wType==TYPE_JINGLE )
	{
		g_wndPFL->SetSound(lpItem);
		g_wndPFL->RestoreWindow();
	}
}


void CJinglesWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CFrameWnd::OnPaint() for painting messages
}
