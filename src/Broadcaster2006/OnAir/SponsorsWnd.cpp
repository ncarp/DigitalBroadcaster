// SponsorsWnd.cpp : implementation file
//

#include "stdafx.h"
#include "OnAir.h"
#include "SponsorsWnd.h"
#include "OnAirDefines.h"
#include "ExternalObjects.h"
#include "OnAirUtils.h"
#include "RSViewOnAirSponsors.h"
#include "..\include\utils.h"
#include "..\include\RSBlocksDefinition.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSponsorsWnd

IMPLEMENT_DYNCREATE(CSponsorsWnd, CFrameWnd)

CSponsorsWnd::CSponsorsWnd()
{
}

CSponsorsWnd::~CSponsorsWnd()
{
}


BEGIN_MESSAGE_MAP(CSponsorsWnd, CFrameWnd)
	//{{AFX_MSG_MAP(CSponsorsWnd)
	ON_WM_CREATE()
	ON_WM_KEYUP()
	ON_WM_SYSKEYUP()
	ON_WM_SYSCOMMAND()
	ON_COMMAND( CM_REFRESH,OnRefresh )
	ON_COMMAND( CM_PFL, OnPFL )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSponsorsWnd message handlers

int CSponsorsWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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
	m_pList->m_iX1=rectHeader.right-GetSystemMetrics(SM_CXVSCROLL);
	m_pList->m_iX2=64000;
	m_pList->SetBackColor(RGB(245,255,245));
	// 
	HDITEM	hdItem;
	CString	strTemp;

	strTemp.LoadString(IDS_TITLE);

	hdItem.mask=HDI_FORMAT|HDI_TEXT|HDI_WIDTH;
	hdItem.pszText=strTemp.GetBuffer(0);
	hdItem.cxy=rectHeader.Width()-70-GetSystemMetrics(SM_CXVSCROLL);
	hdItem.cchTextMax=strTemp.GetLength();
	hdItem.fmt=HDF_CENTER|HDF_STRING;
	m_pHeader->InsertItem(0,&hdItem);

	hdItem.cxy=70;
	strTemp.LoadString(IDS_DURATION);
	hdItem.pszText=strTemp.GetBuffer(0);
	m_pHeader->InsertItem(1,&hdItem);

	m_pHeader->EnableWindow(FALSE);

	
	return 0;
}

void CSponsorsWnd::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( CheckKey(nChar) )
		CFrameWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CSponsorsWnd::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( CheckKey(nChar) )
		CFrameWnd::OnSysKeyUp(nChar, nRepCnt, nFlags);
}

void CSponsorsWnd::OnSysCommand(UINT nID, LPARAM lParam) 
{
//	Do nothing !!
}

void CSponsorsWnd::OnRefresh()
{
	if( !m_pList->m_bIsRefreshing )
		AfxBeginThread(ThreadRefresh,(LPVOID)m_pList);
}

UINT CSponsorsWnd::ThreadRefresh(LPVOID lp)
{
	CRSViewOnAirSponsors	rs(g_strOnAirConnect);
	CRSBlocksDefinition rsBlocks(g_strOnAirConnect);
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

	rsBlocks.m_strFilter = "Sponsor = 1 AND Activ = 1";
	rsBlocks.m_strSort = "Name";
	rsBlocks.Open();

	BOOL bFirstItem=TRUE;

	if( rsBlocks.GetRecordCount() )
	{
		CString strBlock;
		strBlock.LoadString(IDS_SPONSORBLOCKS);
	
		lpItem = new typeArchiveItem(TYPE_SPONSORBLOCK,0,strBlock,0);
		pList->InsertString(-1,(LPCTSTR)lpItem);

		while( !rsBlocks.IsEOF() )
		{
			rsBlocks.m_Name.TrimRight();

			lpItem = new typeArchiveItem(TYPE_BLOCK,rsBlocks.m_ID,rsBlocks.m_Name,0);
			pList->InsertString(-1,(LPCTSTR)lpItem);

			rsBlocks.MoveNext();
		}
		bFirstItem=FALSE;
	}
	rsBlocks.Close();

	rs.m_strSort="CustomerName, SpotName";
	rs.m_strFilter.Format("EndingDate >= '%s' AND StartingDate <= '%s'",strTime,strTime);
	rs.Open();

	while( !rs.IsEOF() )
	{
		if( rs.m_CustomerName!=strPrevType )
		{
			if( bFirstItem==TRUE )
				bFirstItem=FALSE;
			else
			{
				lpItem = new typeArchiveItem(TYPE_NOTHING,0,"",0);
				pList->InsertString(-1,(LPCTSTR)lpItem);
			}

			strPrevType=rs.m_CustomerName;
			rs.m_CustomerName.TrimRight();

			lpItem = new typeArchiveItem(TYPE_CUSTOMER,0,rs.m_CustomerName,0);
			
			pList->InsertString(-1,(LPCTSTR)lpItem);
		}
		rs.m_SpotName.TrimRight();

		GetTimeString(rs.m_Length,&strLength);
		strLength.Delete(0,3);
		strLength.Delete(7,2);

		lpItem = new typeArchiveItem(TYPE_SPOT,rs.m_SpotID,rs.m_SpotName,0,strLength);
			
		pList->InsertString(-1,(LPCTSTR)lpItem);

		rs.MoveNext();
	}
	rs.Close();

	if( bFirstItem!=TRUE )
	{
		lpItem = new typeArchiveItem(TYPE_NOTHING,0,"",0);
		pList->InsertString(-1,(LPCTSTR)lpItem);
	}
	pList->m_bIsRefreshing=FALSE;

	return 0;
}

void CSponsorsWnd::OnPFL()
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
