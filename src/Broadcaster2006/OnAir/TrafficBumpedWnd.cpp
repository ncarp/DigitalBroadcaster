// TrafficBumpedWnd.cpp : implementation file
//

#include "stdafx.h"
#include "onair.h"
#include "TrafficBumpedWnd.h"
#include "OnAirDefines.h"
#include "OnAirUtils.h"
#include "ExternalObjects.h"
#include "..\include\Utils.h"
#include "..\include\RSViewBumpedTraffic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTrafficBumpedWnd

IMPLEMENT_DYNCREATE(CTrafficBumpedWnd, CFrameWnd)

CTrafficBumpedWnd::CTrafficBumpedWnd()
{
}

CTrafficBumpedWnd::~CTrafficBumpedWnd()
{
}


BEGIN_MESSAGE_MAP(CTrafficBumpedWnd, CFrameWnd)
	//{{AFX_MSG_MAP(CTrafficBumpedWnd)
	ON_WM_CREATE()
	ON_WM_SYSCOMMAND()
	ON_WM_KEYUP()
	ON_WM_SYSKEYUP()
	ON_COMMAND( CM_REFRESH, OnRefresh )
	ON_COMMAND( CM_PFL, OnPFL)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrafficBumpedWnd message handlers

int CTrafficBumpedWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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

	crect.DeflateRect(0,17,0,64);

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
	m_pList->SetBackColor(RGB(245,255,245));
	// 
	HDITEM	hdItem;
	CString	strTemp;

	strTemp.LoadString(IDS_TITLE);

	hdItem.mask=HDI_FORMAT|HDI_TEXT|HDI_WIDTH;
	hdItem.pszText=strTemp.GetBuffer(0);
	hdItem.cxy=rectHeader.Width()-160-GetSystemMetrics(SM_CXVSCROLL);
	hdItem.cchTextMax=strTemp.GetLength();
	hdItem.fmt=HDF_CENTER|HDF_STRING;
	m_pHeader->InsertItem(0,&hdItem);

	hdItem.cxy=90;
	strTemp.LoadString(IDS_DATE);
	hdItem.pszText=strTemp.GetBuffer(0);
	m_pHeader->InsertItem(1,&hdItem);

	strTemp.LoadString(IDS_DURATION);
	hdItem.pszText=strTemp.GetBuffer(0);
	hdItem.cxy=70;
	m_pHeader->InsertItem(2,&hdItem);
	m_pHeader->EnableWindow(FALSE);
	
	return 0;
}

void CTrafficBumpedWnd::OnSysCommand(UINT nID, LPARAM lParam) 
{
}

void CTrafficBumpedWnd::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( CheckKey(nChar) )
		CFrameWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CTrafficBumpedWnd::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( CheckKey(nChar) )
		CFrameWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CTrafficBumpedWnd::OnRefresh()
{
	if( m_pList->m_bIsRefreshing )
		return;

	AfxBeginThread(OnRefreshThread,(LPVOID)m_pList,THREAD_PRIORITY_LOWEST);
}

UINT CTrafficBumpedWnd::OnRefreshThread(LPVOID V)
{
	COnAirListBox			*pList = (COnAirListBox *)V;
	CRSViewBumpedTraffic	rs(g_strOnAirConnect );
	COleDateTime			date = COleDateTime::GetCurrentTime();
	COleDateTimeSpan		ts(7,0,0,0);
	COleDateTime			date2=date-ts;
	CString					strLength,
							strDate;
	typeArchiveItem			*lpItem;
	long					lTime=date.GetHour()*3600000+date.GetMinute()*60000+date.GetSecond()*1000;


	pList->m_bIsRefreshing=TRUE;
	pList->ResetContent();
	
	rs.m_strFilter.Format("BlockDate >= '%d-%d-%d' AND BlockDate < '%d-%d-%d'",
		date2.GetYear(),date2.GetMonth(),date2.GetDay(),
		date.GetYear(),date.GetMonth(),date.GetDay());
	rs.m_strSort = "BlockDate, Time";
	rs.Open();

	while( !rs.IsEOF() )
	{
		rs.m_CustomerName.TrimRight();
		rs.m_Name.TrimRight();

		GetTimeString(rs.m_Length,&strLength);
		strLength.Delete(0,3);
		strLength.Delete(7,2);
	
		strDate.Format("%d-%2d-%2d",rs.m_BlockDate.year,rs.m_BlockDate.month,rs.m_BlockDate.day);
		lpItem = new typeArchiveItem(TYPE_SPOT,rs.m_SpotID,rs.m_Name+" - "+rs.m_CustomerName,0,strDate,strLength);
		lpItem->lTraffID = rs.m_ID;
			
		pList->InsertString(-1,(LPCTSTR)lpItem);

		rs.MoveNext();
	}

	rs.m_strFilter.Format("BlockDate = '%d-%d-%d' AND Time < '%d'",
		date.GetYear(),date.GetMonth(),date.GetDay(),lTime);
	rs.m_strSort = "BlockDate, Time";
	rs.Requery();

	while( !rs.IsEOF() )
	{
		rs.m_CustomerName.TrimRight();
		rs.m_Name.TrimRight();

		GetTimeString(rs.m_Length,&strLength);
		strLength.Delete(0,3);
		strLength.Delete(7,2);
	
		strDate.Format("%d-%2d-%2d",rs.m_BlockDate.year,rs.m_BlockDate.month,rs.m_BlockDate.day);
		lpItem = new typeArchiveItem(TYPE_SPOT,rs.m_SpotID,rs.m_Name+" - "+rs.m_CustomerName,0,strDate,strLength);
		lpItem->lTraffID = rs.m_ID;
			
		pList->InsertString(-1,(LPCTSTR)lpItem);

		rs.MoveNext();
	}

	rs.Close();
	pList->m_bIsRefreshing=FALSE;

	return 0;
}

void CTrafficBumpedWnd::OnPFL()
{
	long int lPos=m_pList->GetCurSel();

	if( lPos==LB_ERR )
		return;

	typeArchiveItem* lpItem=(typeArchiveItem*)m_pList->GetItemData(lPos);
	if( lpItem==NULL )
		return;

	if( lpItem->wType==TYPE_SPOT )
	{
		g_wndPFL->SetSound(lpItem);
		g_wndPFL->RestoreWindow();
	}
}
