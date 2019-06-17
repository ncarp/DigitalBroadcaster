// RMsWnd.cpp : implementation file
//

#include "stdafx.h"
#include "onair.h"
#include "RMsWnd.h"
#include "OnAirUtils.h"
#include "OnAirDefines.h"
#include "ExternalObjects.h"
#include "..\include\RSViewRMsOnAir.h"
#include "..\include\Utils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRMsWnd

IMPLEMENT_DYNCREATE(CRMsWnd, CFrameWnd)

CRMsWnd::CRMsWnd()
{
}

CRMsWnd::~CRMsWnd()
{
}


BEGIN_MESSAGE_MAP(CRMsWnd, CFrameWnd)
	//{{AFX_MSG_MAP(CRMsWnd)
	ON_WM_SYSCOMMAND()
	ON_WM_SYSKEYUP()
	ON_WM_KEYUP()
	ON_WM_CREATE()
	ON_COMMAND( CM_REFRESH,OnRefresh )
	ON_COMMAND( CM_PFL,OnPFL )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRMsWnd message handlers

void CRMsWnd::OnSysCommand(UINT nID, LPARAM lParam) 
{
}

void CRMsWnd::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( !CheckKey(nChar) )
		CFrameWnd::OnSysKeyUp(nChar, nRepCnt, nFlags);
}

void CRMsWnd::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( !CheckKey(nChar) )
		CFrameWnd::OnSysKeyUp(nChar, nRepCnt, nFlags);
}

int CRMsWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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

void CRMsWnd::OnRefresh() 
{
	if( !m_pList->m_bIsRefreshing )
		AfxBeginThread(ThreadRefreshList,(LPVOID)this->m_pList);
}


UINT CRMsWnd::ThreadRefreshList(LPVOID lp)
{
	CRSViewRMsOnAir		rs(g_strOnAirConnect);
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

	rs.m_strSort="Type, Name";
	rs.m_strFilter.Format("EndingDate >= '%s' AND StartingDate <= '%s'",strTime,strTime);
	rs.Open();

	while( !rs.IsEOF() )
	{
		if( rs.m_Type!=strPrevType )
		{
			strPrevType=rs.m_Type;
			rs.m_Type.TrimRight();

			lpItem = new typeArchiveItem(TYPE_RMTYPE,rs.m_TypeID,rs.m_Type,0,"","");
			
			pList->InsertString(-1,(LPCTSTR)lpItem);
		}
		rs.m_Name.TrimRight();

		GetTimeString(rs.m_Length,&strLength);
		strLength.Delete(0,3);
		strLength.Delete(7,2);

		lpItem = new typeArchiveItem(TYPE_RM,rs.m_RMID,rs.m_Name,0,strLength,"");
			
		pList->InsertString(-1,(LPCTSTR)lpItem);

		rs.MoveNext();
	}
	rs.Close();
	pList->m_bIsRefreshing=FALSE;

	return 0;
}

void CRMsWnd::OnPFL()
{
	long int lPos=m_pList->GetCurSel();

	if( lPos==LB_ERR )
		return;

	typeArchiveItem* lpItem=(typeArchiveItem*)m_pList->GetItemData(lPos);
	if( lpItem==NULL )
		return;

	if( lpItem->wType==TYPE_RM )
	{
		g_wndPFL->SetSound(lpItem);
		g_wndPFL->RestoreWindow();
	}
}
