// TrafficManagmentFrame.cpp : implementation file
//

#include "stdafx.h"
#include "Traffic.h"
#include "TrafficManagmentFrame.h"
#include "TrafficManagmentLeftView.h"
#include "TrafficExternals.h"
#include "..\OnAir\OnAirDefines.h"
#include "..\common\include\global.h"
#include "radiostation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTrafficManagmentFrame

IMPLEMENT_DYNCREATE(CTrafficManagmentFrame, CMDIChildWnd)

CTrafficManagmentFrame::CTrafficManagmentFrame()
{
}

CTrafficManagmentFrame::~CTrafficManagmentFrame()
{
}


BEGIN_MESSAGE_MAP(CTrafficManagmentFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CTrafficManagmentFrame)
	ON_WM_CREATE()
	ON_COMMAND( CM_NEW, OnNewSpot )
	ON_COMMAND( CM_EDIT, OnEdit )
	ON_COMMAND( CM_CUT, OnCut )
	ON_COMMAND( CM_SCHEDULE, OnNewSchedule )
	ON_COMMAND( CM_QUERYBLOCKS, OnQueryBlocks )
	ON_COMMAND( CM_PFL, OnPFL )
	ON_COMMAND( CM_INFO, OnInfo )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrafficManagmentFrame message handlers

int CTrafficManagmentFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	TBBUTTON	buttons[12];

	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_wndToolBar.Create(TBSTYLE_FLAT|CCS_BOTTOM,CRect(0,0,0,0),this,292);

	buttons[0].iBitmap=0;
	buttons[0].idCommand=CM_NEW;
	buttons[0].fsState=TBSTATE_ENABLED;
	buttons[0].fsStyle=TBSTYLE_BUTTON;
	buttons[0].dwData=0;
	buttons[0].iString=0;

	buttons[1].iBitmap=1;
	buttons[1].idCommand=0;
	buttons[1].fsState=TBSTATE_ENABLED;
	buttons[1].fsStyle=TBSTYLE_SEP;
	buttons[1].dwData=0;
	buttons[1].iString=1;

	buttons[2].iBitmap=1;
	buttons[2].idCommand=CM_EDIT;
	buttons[2].fsState=TBSTATE_ENABLED;
	buttons[2].fsStyle=TBSTYLE_BUTTON;
	buttons[2].dwData=0;
	buttons[2].iString=1;

	buttons[3].iBitmap=1;
	buttons[3].idCommand=0;
	buttons[3].fsState=TBSTATE_ENABLED;
	buttons[3].fsStyle=TBSTYLE_SEP;
	buttons[3].dwData=0;
	buttons[3].iString=1;

	buttons[4].iBitmap=2;
	buttons[4].idCommand=CM_CUT;
	buttons[4].fsState=TBSTATE_ENABLED;
	buttons[4].fsStyle=TBSTYLE_BUTTON;
	buttons[4].dwData=0;
	buttons[4].iString=2;

	buttons[5].iBitmap=1;
	buttons[5].idCommand=0;
	buttons[5].fsState=TBSTATE_ENABLED;
	buttons[5].fsStyle=TBSTYLE_SEP;
	buttons[5].dwData=0;
	buttons[5].iString=1;

	buttons[6].iBitmap=3;
	buttons[6].idCommand=CM_SCHEDULE;
	buttons[6].fsState=TBSTATE_ENABLED;
	buttons[6].fsStyle=TBSTYLE_BUTTON;
	buttons[6].dwData=0;
	buttons[6].iString=3;

	buttons[7].iBitmap=0;
	buttons[7].idCommand=CM_SCHEDULE;
	buttons[7].fsState=TBSTATE_ENABLED;
	buttons[7].fsStyle=TBSTYLE_SEP;
	buttons[7].dwData=0;
	buttons[7].iString=0;

	buttons[8].iBitmap=4;
	buttons[8].idCommand=CM_QUERYBLOCKS;
	buttons[8].fsState=TBSTATE_ENABLED;
	buttons[8].fsStyle=TBSTYLE_BUTTON;
	buttons[8].dwData=0;
	buttons[8].iString=4;

	buttons[9].iBitmap=10;
	buttons[9].idCommand=CM_INFO;
	buttons[9].fsState=TBSTATE_ENABLED;
	buttons[9].fsStyle=TBSTYLE_BUTTON;
	buttons[9].dwData=0;
	buttons[9].iString=10;

	buttons[10].iBitmap=0;
	buttons[10].idCommand=CM_SCHEDULE;
	buttons[10].fsState=TBSTATE_ENABLED;
	buttons[10].fsStyle=TBSTYLE_SEP;
	buttons[10].dwData=0;
	buttons[10].iString=0;

	buttons[11].iBitmap=6;
	buttons[11].idCommand=CM_PFL;
	buttons[11].fsState=TBSTATE_ENABLED;
	buttons[11].fsStyle=TBSTYLE_BUTTON;
	buttons[11].dwData=0;
	buttons[11].iString=6;

	m_wndToolBar.SetImageList(g_ilToolBar);
	m_wndToolBar.SetHotImageList(g_ilToolBar);
	m_wndToolBar.AddStrings(g_strToolBarLabels);
	m_wndToolBar.AddButtons(12,buttons);
	m_wndToolBar.AutoSize();

	m_wndReBar.Create(this);
	m_wndReBar.AddBar(&m_wndToolBar);
	
	return 0;
}

BOOL CTrafficManagmentFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	m_wndSplitter.CreateStatic(this,1,2);
	m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CTrafficManagmentLeftView), CSize(400, 100), pContext);
	m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CHtmlView),CSize(100,100), pContext);

	return TRUE;
}

void CTrafficManagmentFrame::OnNewSpot()
{
	CTrafficManagmentLeftView *pView = (CTrafficManagmentLeftView *)m_wndSplitter.GetPane(0,0);
	pView->NewSpot();
}

void CTrafficManagmentFrame::OnEdit()
{
	CTrafficManagmentLeftView *pView = (CTrafficManagmentLeftView *)m_wndSplitter.GetPane(0,0);
	pView->OnDoubleClick();
}

void CTrafficManagmentFrame::OnCut()
{
	CTrafficManagmentLeftView *pView = (CTrafficManagmentLeftView *)m_wndSplitter.GetPane(0,0);
	pView->OnCut();
}

void CTrafficManagmentFrame::OnNewSchedule()
{
	CTrafficManagmentLeftView *pView = (CTrafficManagmentLeftView *)m_wndSplitter.GetPane(0,0);
	pView->NewSchedule();
}

void CTrafficManagmentFrame::OnQueryBlocks()
{
	if( !g_Permissions.bTrafficView )
		return;

	CRadioStation	dl;

	if( dl.DoModal()!=IDOK )
		return;

	CHtmlView *pView = (CHtmlView *)m_wndSplitter.GetPane(0,1);
	CString str;

	str.Format("%s\\BlocksStatisticsFrame.asp?DB=%s",g_strBaseURL,dl.m_strDB);
	pView->Navigate2(str);
}

void CTrafficManagmentFrame::OnPFL()
{
	CTrafficManagmentLeftView *pView = (CTrafficManagmentLeftView *)m_wndSplitter.GetPane(0,0);
	pView->PFL();
}

void CTrafficManagmentFrame::OnInfo()
{
	CHtmlView *pView = (CHtmlView *)m_wndSplitter.GetPane(0,1);
	CString str;

	str.Format("%s/AllTraffic.asp",g_strBaseURL);

	if( pView->GetLocationURL()!=str )
		pView->Navigate(str);
}