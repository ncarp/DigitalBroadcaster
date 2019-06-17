// TimeFrame.cpp : implementation file
//

#include "stdafx.h"
#include "Manager.h"
#include "TimeFrame.h"
#include "TimeView.h"
#include "..\onair\onairdefines.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CImageList	*g_ilToolBar;
extern char			g_strToolBarLabels[];

/////////////////////////////////////////////////////////////////////////////
// CTimeFrame

IMPLEMENT_DYNCREATE(CTimeFrame, CMDIChildWnd)

CTimeFrame::CTimeFrame()
{
}

CTimeFrame::~CTimeFrame()
{
}


BEGIN_MESSAGE_MAP(CTimeFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CTimeFrame)
	ON_WM_CREATE()
	ON_COMMAND( CM_NEW, OnNew)
	ON_COMMAND( CM_EDIT, OnEdit)
	ON_COMMAND( CM_CUT, OnCut)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimeFrame message handlers
int CTimeFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	TBBUTTON	buttons[10];

	m_wndToolBar.Create(TBSTYLE_FLAT|CCS_BOTTOM,CRect(0,0,0,0),this,292);

	buttons[0].iBitmap=3;
	buttons[0].idCommand=CM_NEW;
	buttons[0].fsState=TBSTATE_ENABLED;
	buttons[0].fsStyle=TBSTYLE_BUTTON;
	buttons[0].dwData=0;
	buttons[0].iString=18;

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

void CTimeFrame::OnNew()
{
	((CTimeView *)GetActiveView())->OnNew();
	
}

void CTimeFrame::OnEdit()
{
	((CTimeView *)GetActiveView())->OnDblclk(NULL,NULL);
}

void CTimeFrame::OnCut()
{
	((CTimeView *)GetActiveView())->OnCut();
}