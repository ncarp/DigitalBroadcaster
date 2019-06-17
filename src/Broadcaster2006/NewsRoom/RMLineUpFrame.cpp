// RMLineUpFrame.cpp : implementation file
//

#include "stdafx.h"
#include "NewsRoom.h"
#include "RMLineUpFrame.h"
#include "RMLineUpLeftView.h"
#include "RMLineUpRightView.h"
#include "..\OnAir\OnAirDefines.h"
#include "..\Traffic\RadioStation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern	char		g_strToolBarLabels[];
extern	CImageList	*g_ilToolBar;

/////////////////////////////////////////////////////////////////////////////
// CRMLineUpFrame

IMPLEMENT_DYNCREATE(CRMLineUpFrame, CMDIChildWnd)

CRMLineUpFrame::CRMLineUpFrame()
{
}

CRMLineUpFrame::~CRMLineUpFrame()
{
}


BEGIN_MESSAGE_MAP(CRMLineUpFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CRMLineUpFrame)
	ON_WM_CREATE()
	ON_COMMAND( CM_NEW, OnNew )
	ON_COMMAND( CM_EDIT, OnEdit )
	ON_COMMAND( CM_CUT, OnCut )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRMLineUpFrame message handlers

int CRMLineUpFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	TBBUTTON	buttons[10];

	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_wndToolBar.Create(TBSTYLE_FLAT|CCS_BOTTOM,CRect(0,0,0,0),this,292);

	buttons[0].iBitmap=9;
	buttons[0].idCommand=CM_NEW;
	buttons[0].fsState=TBSTATE_ENABLED;
	buttons[0].fsStyle=TBSTYLE_BUTTON;
	buttons[0].dwData=0;
	buttons[0].iString=9;

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

BOOL CRMLineUpFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	CRadioStation dl;
	dl.DoModal();

	m_wndSplitter.CreateStatic(this,1,2);
	m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CRMLineUpLeftView), CSize(400, 100), pContext);
	m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CRMLineUpRightView),CSize(100,100), pContext);

	CRMLineUpLeftView *pView = (CRMLineUpLeftView *)m_wndSplitter.GetPane(0,0);
	pView->m_strConnect = dl.m_strConnect;
	pView->m_strRadio = dl.m_strRadio;
	pView->m_strDB = dl.m_strDB;
	pView->m_pViewCart=(CRMLineUpRightView *)m_wndSplitter.GetPane(0,1);
	pView->m_pViewCart->m_strConnect=dl.m_strConnect;
	return TRUE;
}

void CRMLineUpFrame::OnNew()
{
	CRMLineUpLeftView *pView=(CRMLineUpLeftView *)m_wndSplitter.GetPane(0,0);
	pView->OnNew();
}

void CRMLineUpFrame::OnEdit()
{
	CRMLineUpLeftView *pView=(CRMLineUpLeftView *)m_wndSplitter.GetPane(0,0);
	pView->OnDoubleClick();
}

void CRMLineUpFrame::OnCut()
{
	CRMLineUpLeftView *pView=(CRMLineUpLeftView *)m_wndSplitter.GetPane(0,0);
	pView->OnCut();
}