// BlocksWnd.cpp : implementation file
//

#include "stdafx.h"
#include "onair.h"
#include "BlocksWnd.h"
#include "OnAirDefines.H"
#include "OnAirUtils.h"
#include "ExternalObjects.h"
#include "..\include\RSBlocksDefinition.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBlocksWnd

IMPLEMENT_DYNCREATE(CBlocksWnd, CFrameWnd)

CBlocksWnd::CBlocksWnd()
{
}

CBlocksWnd::~CBlocksWnd()
{
}


BEGIN_MESSAGE_MAP(CBlocksWnd, CFrameWnd)
	//{{AFX_MSG_MAP(CBlocksWnd)
	ON_WM_CREATE()
	ON_WM_SYSCOMMAND()
	ON_WM_KEYUP()
	ON_WM_SYSKEYUP()
	ON_COMMAND( CM_REFRESH, OnRefresh )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBlocksWnd message handlers

int CBlocksWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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

	CToolBarCtrl	*wndToolBar=new CToolBarCtrl();
	CSize			size(40,40);

	wndToolBar->Create(TBSTYLE_FLAT|CCS_BOTTOM,CRect(10,10,100,100),this,292);
	wndToolBar->SetButtonSize(size);
	wndToolBar->SetImageList(g_ilToolEnabled);
	wndToolBar->SetHotImageList(g_ilToolHot);
	wndToolBar->AddStrings(g_lpstrToolLabels);
	wndToolBar->AddButtons(1,buttons);
	wndToolBar->AutoSize();

	m_pRebar->AddBar(wndToolBar,NULL,g_bmToolBackground);

	// Create the List box

	m_pList=new COnAirListBox();
	m_pList->Create(WS_VISIBLE|WS_CHILD|WS_VSCROLL|LBS_NOTIFY|LBS_OWNERDRAWVARIABLE|LBS_NOINTEGRALHEIGHT,crect,this,200);
	m_pList->m_iX1=rectHeader.right-70-GetSystemMetrics(SM_CXVSCROLL);
	m_pList->m_iX2=rectHeader.right-GetSystemMetrics(SM_CXVSCROLL);
	m_pList->SetBackColor(RGB(245,255,245));
	
	
	// Create the header items
	HDITEM	hdItem;
	CString	strTemp;

	strTemp.LoadString(IDS_TITLE);

	hdItem.mask=HDI_FORMAT|HDI_TEXT|HDI_WIDTH;
	hdItem.pszText=strTemp.GetBuffer(0);
	hdItem.cxy=rectHeader.Width()-GetSystemMetrics(SM_CXVSCROLL);
	hdItem.cchTextMax=strTemp.GetLength();
	hdItem.fmt=HDF_CENTER|HDF_STRING;
	m_pHeader->InsertItem(0,&hdItem);
	
	m_pHeader->EnableWindow(FALSE);
	
	return 0;
}

void CBlocksWnd::OnSysCommand(UINT nID, LPARAM lParam) 
{
}

void CBlocksWnd::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( CheckKey(nChar) )
		CFrameWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CBlocksWnd::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( CheckKey(nChar) )
		CFrameWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CBlocksWnd::OnRefresh()
{
	// Log Item -----------------------------------------------------------------------
	typeLogItem *lpLog=new typeLogItem;
	lpLog->wType = 0;
	lpLog->lID = 0;
	lpLog->lTraffic = 0;
	strcpy(lpLog->strName,"--> Refresh Blocks List");
	g_wndAired->LogItem(lpLog);
	// --------------------------------------------------------------------------------

	if( !m_pList->m_bIsRefreshing )
		AfxBeginThread(OnRefreshThread,(LPVOID)m_pList);
}

UINT CBlocksWnd::OnRefreshThread(LPVOID T)
{
	COnAirListBox *pList=(COnAirListBox *)T;
	typeArchiveItem *lpItem;

	pList->m_bIsRefreshing=TRUE;
	pList->ResetContent();

	CRSBlocksDefinition rs(g_strOnAirConnect);
	rs.m_strFilter	= "Activ <> 0 AND Sponsor = 0";
	rs.m_strSort	= "Time";
	rs.Open();
	
	while( !rs.IsEOF() )
	{
		lpItem = new typeArchiveItem(TYPE_BLOCK,rs.m_ID,rs.m_Name,0);
		pList->InsertString(-1,(LPCTSTR)lpItem);

		rs.MoveNext();
	}
	rs.Close();

	pList->m_bIsRefreshing=FALSE;

	return 0;
}