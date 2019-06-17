// SponsorsFrame.cpp : implementation file
//

#include "stdafx.h"
#include "Traffic.h"
#include "SponsorsFrame.h"
#include "TrafficExternals.h"
#include "SponsorsLeftView.h"
#include "RadioStation.h"
#include "..\OnAir\OnAirDefines.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSponsorsFrame

IMPLEMENT_DYNCREATE(CSponsorsFrame, CMDIChildWnd)

CSponsorsFrame::CSponsorsFrame()
{
}

CSponsorsFrame::~CSponsorsFrame()
{
}


BEGIN_MESSAGE_MAP(CSponsorsFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CSponsorsFrame)
	ON_WM_CREATE()
	ON_COMMAND( CM_EDIT,OnEdit )
	ON_COMMAND( CM_CUT, OnCut )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSponsorsFrame message handlers

BOOL CSponsorsFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	CRadioStation dl;
	dl.DoModal();
	
	m_wndSplitter.CreateStatic(this,1,2);
	m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CSponsorsLeftView), CSize(400, 100), pContext);
	m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CHtmlView),CSize(100,100), pContext);
	
	CSponsorsLeftView *pView = (CSponsorsLeftView *)m_wndSplitter.GetPane(0,0);
	pView->m_strConnect = dl.m_strConnect;
	pView->m_strRadio = dl.m_strRadio;
	pView->m_strDB = dl.m_strDB;
	pView->m_lRadioID = dl.m_lRadioID;

	return TRUE;
}

int CSponsorsFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	TBBUTTON	buttons[10];

	m_wndToolBar.Create(TBSTYLE_FLAT|CCS_BOTTOM,CRect(0,0,0,0),this,292);

	buttons[0].iBitmap=1;
	buttons[0].idCommand=CM_EDIT;
	buttons[0].fsState=TBSTATE_ENABLED;
	buttons[0].fsStyle=TBSTYLE_BUTTON;
	buttons[0].dwData=0;
	buttons[0].iString=1;

	buttons[1].iBitmap=1;
	buttons[1].idCommand=0;
	buttons[1].fsState=TBSTATE_ENABLED;
	buttons[1].fsStyle=TBSTYLE_SEP;
	buttons[1].dwData=0;
	buttons[1].iString=1;

	buttons[2].iBitmap=2;
	buttons[2].idCommand=CM_CUT;
	buttons[2].fsState=TBSTATE_ENABLED;
	buttons[2].fsStyle=TBSTYLE_BUTTON;
	buttons[2].dwData=0;
	buttons[2].iString=2;

	buttons[3].iBitmap=1;
	buttons[3].idCommand=0;
	buttons[3].fsState=TBSTATE_ENABLED;
	buttons[3].fsStyle=TBSTYLE_SEP;
	buttons[3].dwData=0;
	buttons[3].iString=1;

	m_wndToolBar.SetImageList(g_ilToolBar);
	m_wndToolBar.SetHotImageList(g_ilToolBar);
	m_wndToolBar.AddStrings(g_strToolBarLabels);
	m_wndToolBar.AddButtons(4,buttons);
	m_wndToolBar.AutoSize();

	m_wndReBar.Create(this);
	m_wndReBar.AddBar(&m_wndToolBar);
	
	return 0;
}

void CSponsorsFrame::OnEdit()
{
	CSponsorsLeftView *pView = (CSponsorsLeftView *)m_wndSplitter.GetPane(0,0);
	pView->OnDoubleClick();
}

void CSponsorsFrame::OnCut()
{
	CSponsorsLeftView *pView = (CSponsorsLeftView *)m_wndSplitter.GetPane(0,0);
	pView->CutSponsor();
}
