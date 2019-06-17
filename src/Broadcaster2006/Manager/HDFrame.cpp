// HDFrame.cpp : implementation file
//

#include "stdafx.h"
#include "Manager.h"
#include "HDFrame.h"
#include "hdview.h"
#include "..\onair\onairdefines.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern	CImageList	*g_ilToolBar;
extern	char		g_strToolBarLabels[];

/////////////////////////////////////////////////////////////////////////////
// CHDFrame

IMPLEMENT_DYNCREATE(CHDFrame, CMDIChildWnd)

CHDFrame::CHDFrame()
{
}

CHDFrame::~CHDFrame()
{
}


BEGIN_MESSAGE_MAP(CHDFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CHDFrame)
	ON_WM_CREATE()
	ON_COMMAND( CM_NEW, OnNew )
	ON_COMMAND( CM_EDIT, OnEdit )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHDFrame message handlers

int CHDFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	TBBUTTON	buttons[10];

	m_wndToolBar.Create(TBSTYLE_FLAT|CCS_BOTTOM,CRect(0,0,0,0),this,292);

	buttons[0].iBitmap=17;
	buttons[0].idCommand=CM_NEW;
	buttons[0].fsState=TBSTATE_ENABLED;
	buttons[0].fsStyle=TBSTYLE_BUTTON;
	buttons[0].dwData=0;
	buttons[0].iString=17;

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

	m_wndToolBar.SetImageList(g_ilToolBar);
	m_wndToolBar.SetHotImageList(g_ilToolBar);
	m_wndToolBar.AddStrings(g_strToolBarLabels);
	m_wndToolBar.AddButtons(4,buttons);
	m_wndToolBar.AutoSize();

	m_wndReBar.Create(this);
	m_wndReBar.AddBar(&m_wndToolBar);
	
	return 0;
}

void CHDFrame::OnNew()
{
	CHDView *pView = (CHDView *)GetActiveView();

	pView->AddFolder();
}

void CHDFrame::OnEdit()
{
	CHDView *pView = (CHDView *)GetActiveView();

	pView->OnDblclk(NULL,NULL);
}
