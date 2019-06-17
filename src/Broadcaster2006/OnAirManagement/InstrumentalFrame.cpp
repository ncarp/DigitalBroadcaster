// InstrumentalFrame.cpp : implementation file
//

#include "stdafx.h"
#include "OnAirManagement.h"
#include "InstrumentalFrame.h"
#include "InstrumentalLeftView.h"
#include "..\traffic\RadioStation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern	CImageList	*g_ilToolBar;
extern	char		g_strToolBarLabels[];

/////////////////////////////////////////////////////////////////////////////
// CInstrumentalFrame

IMPLEMENT_DYNCREATE(CInstrumentalFrame, CMDIChildWnd)

CInstrumentalFrame::CInstrumentalFrame()
{
}

CInstrumentalFrame::~CInstrumentalFrame()
{
}


BEGIN_MESSAGE_MAP(CInstrumentalFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CInstrumentalFrame)
	ON_WM_CREATE()
	ON_COMMAND( CM_CUT, OnCut )
	ON_COMMAND( CM_PFL, OnPFL )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInstrumentalFrame message handlers

int CInstrumentalFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	TBBUTTON	buttons[4];

	buttons[0].iBitmap=2;
	buttons[0].idCommand=CM_CUT;
	buttons[0].fsState=TBSTATE_ENABLED;
	buttons[0].fsStyle=TBSTYLE_BUTTON;
	buttons[0].dwData=0;
	buttons[0].iString=2;

	buttons[1].iBitmap=1;
	buttons[1].idCommand=0;
	buttons[1].fsState=TBSTATE_ENABLED;
	buttons[1].fsStyle=TBSTYLE_SEP;
	buttons[1].dwData=0;
	buttons[1].iString=1;

	buttons[2].iBitmap=6;
	buttons[2].idCommand=CM_PFL;
	buttons[2].fsState=TBSTATE_ENABLED;
	buttons[2].fsStyle=TBSTYLE_BUTTON;
	buttons[2].dwData=0;
	buttons[2].iString=6;
	
	buttons[3].iBitmap=0;
	buttons[3].idCommand=CM_SCHEDULE;
	buttons[3].fsState=TBSTATE_ENABLED;
	buttons[3].fsStyle=TBSTYLE_SEP;
	buttons[3].dwData=0;
	buttons[3].iString=0;

	m_wndToolBar.Create(TBSTYLE_FLAT|CCS_BOTTOM,CRect(0,0,0,0),this,292);
	m_wndToolBar.SetImageList(g_ilToolBar);
	m_wndToolBar.SetHotImageList(g_ilToolBar);
	m_wndToolBar.AddStrings(g_strToolBarLabels);
	m_wndToolBar.AddButtons(4,buttons);
	m_wndToolBar.AutoSize();

	m_wndReBar.Create(this);
	m_wndReBar.AddBar(&m_wndToolBar);
	
	return 0;

}

BOOL CInstrumentalFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	CRadioStation dl;
	
	if( dl.DoModal()!=IDOK )
		return FALSE;

	m_wndSplitter.CreateStatic(this,1,2);
	m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CInstrumentalLeftView), CSize(400, 100), pContext);
	m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CHtmlView),CSize(100,100), pContext);
	
	CInstrumentalLeftView *pView = (CInstrumentalLeftView *)m_wndSplitter.GetPane(0,0);
	pView->m_strConnect = dl.m_strConnect;
	pView->m_lRadioID = dl.m_lRadioID;

	return TRUE;
}

void CInstrumentalFrame::OnCut()
{
	CInstrumentalLeftView *pView = (CInstrumentalLeftView *)m_wndSplitter.GetPane(0,0);
	pView->OnCut();
}

void CInstrumentalFrame::OnPFL()
{
	CInstrumentalLeftView *pView = (CInstrumentalLeftView *)m_wndSplitter.GetPane(0,0);
	pView->OnPFL();
}
