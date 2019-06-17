// RMsOnAirFrame.cpp : implementation file
//

#include "stdafx.h"
#include "NewsRoom.h"
#include "RMsOnAirFrame.h"
#include "RMsOnAirLeftView.h"
#include "..\Traffic\RadioStation.h"
#include "..\OnAir\OnAirDefines.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern char g_strToolBarLabels[];
extern CImageList	*g_ilToolBar;
/////////////////////////////////////////////////////////////////////////////
// CRMsOnAirFrame

IMPLEMENT_DYNCREATE(CRMsOnAirFrame, CMDIChildWnd)

CRMsOnAirFrame::CRMsOnAirFrame()
{
}

CRMsOnAirFrame::~CRMsOnAirFrame()
{
}


BEGIN_MESSAGE_MAP(CRMsOnAirFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CRMsOnAirFrame)
	ON_WM_CREATE()
	ON_COMMAND( CM_EDIT, OnEdit )
	ON_COMMAND( CM_CUT, OnCut )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRMsOnAirFrame message handlers

int CRMsOnAirFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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

BOOL CRMsOnAirFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	CRadioStation dl;
	dl.DoModal();

	m_wndSplitter.CreateStatic(this,1,2);
	m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CRMsOnAirLeftView), CSize(400, 100), pContext);
	m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CHtmlView),CSize(100,100), pContext);

	CRMsOnAirLeftView *pView = (CRMsOnAirLeftView *)m_wndSplitter.GetPane(0,0);
	pView->m_strConnect = dl.m_strConnect;
	pView->m_strRadio = dl.m_strRadio;
	pView->m_strDB = dl.m_strDB;

	return TRUE;
}

void CRMsOnAirFrame::OnEdit()
{
	CRMsOnAirLeftView *pView = (CRMsOnAirLeftView *)m_wndSplitter.GetPane(0,0);
	pView->OnDoubleClick();
}

void CRMsOnAirFrame::OnCut()
{
	CRMsOnAirLeftView *pView = (CRMsOnAirLeftView *)m_wndSplitter.GetPane(0,0);
	pView->OnCut();
}