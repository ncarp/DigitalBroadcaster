// OnAirUserFrame.cpp : implementation file
//

#include "stdafx.h"
#include "Manager.h"
#include "OnAirUserFrame.h"
#include "OnAirUserView.h"
#include "..\onair\onairdefines.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern	CImageList	*g_ilToolBar;
extern	char		g_strToolBarLabels[];

/////////////////////////////////////////////////////////////////////////////
// COnAirUserFrame

IMPLEMENT_DYNCREATE(COnAirUserFrame, CMDIChildWnd)

COnAirUserFrame::COnAirUserFrame()
{
}

COnAirUserFrame::~COnAirUserFrame()
{
}


BEGIN_MESSAGE_MAP(COnAirUserFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(COnAirUserFrame)
	ON_COMMAND( CM_NEW,OnNew )
	ON_COMMAND( CM_EDIT,OnEdit)
	ON_COMMAND( CM_CUT,OnCut)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COnAirUserFrame message handlers

int COnAirUserFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	TBBUTTON	buttons[10];

	m_wndToolBar.Create(TBSTYLE_FLAT|CCS_BOTTOM,CRect(0,0,0,0),this,292);

	buttons[0].iBitmap=7;
	buttons[0].idCommand=CM_NEW;
	buttons[0].fsState=TBSTATE_ENABLED;
	buttons[0].fsStyle=TBSTYLE_BUTTON;
	buttons[0].dwData=0;
	buttons[0].iString=7;

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


	m_wndToolBar.SetImageList(g_ilToolBar);
	m_wndToolBar.SetHotImageList(g_ilToolBar);
	m_wndToolBar.AddStrings(g_strToolBarLabels);
	m_wndToolBar.AddButtons(6,buttons);
	m_wndToolBar.AutoSize();

	m_wndReBar.Create(this);
	m_wndReBar.AddBar(&m_wndToolBar);
	
	return 0;
}

BOOL COnAirUserFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	CMDIChildWnd::OnCreateClient(lpcs,pContext);
//	m_wndSplitter.CreateStatic(this,1,1);
//	m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(COnAirUserView), CSize(400, 100), pContext);
//	m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CHtmlView),CSize(100,100), pContext);

	return TRUE;
}

void COnAirUserFrame::OnNew()
{
	COnAirUserView *pView = (COnAirUserView *)GetActiveView();
	pView->OnNew();
}

void COnAirUserFrame::OnEdit()
{
	COnAirUserView *pView = (COnAirUserView *)GetActiveView();
	pView->OnDoubleClick();
}

void COnAirUserFrame::OnCut()
{
	COnAirUserView *pView = (COnAirUserView *)GetActiveView();
	pView->OnCut();
}