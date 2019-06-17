// TextOnAirFrame.cpp : implementation file
//

#include "stdafx.h"
#include "NewsRoom.h"
#include "TextOnAirFrame.h"
#include "TextOnAirLeftView.h"
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
// CTextOnAirFrame

IMPLEMENT_DYNCREATE(CTextOnAirFrame, CMDIChildWnd)

CTextOnAirFrame::CTextOnAirFrame()
{
}

CTextOnAirFrame::~CTextOnAirFrame()
{
}


BEGIN_MESSAGE_MAP(CTextOnAirFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CTextOnAirFrame)
	ON_WM_CREATE()
	ON_COMMAND( CM_EDIT, OnEdit )
	ON_COMMAND( CM_CUT, OnCut )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextOnAirFrame message handlers

int CTextOnAirFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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

BOOL CTextOnAirFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	CRadioStation dl;
	dl.DoModal();

	m_wndSplitter.CreateStatic(this,1,2);
	m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CTextOnAirLeftView), CSize(400, 100), pContext);
	m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CHtmlView),CSize(100,100), pContext);

	CTextOnAirLeftView *pView = (CTextOnAirLeftView *)m_wndSplitter.GetPane(0,0);
	pView->m_strConnect = dl.m_strConnect;
	pView->m_strRadio = dl.m_strRadio;
	pView->m_strDB = dl.m_strDB;

	return TRUE;
}

void CTextOnAirFrame::OnEdit()
{
	CTextOnAirLeftView *pView=(CTextOnAirLeftView *)m_wndSplitter.GetPane(0,0);
	pView->OnDoubleClick();
}

void CTextOnAirFrame::OnCut()
{
	CTextOnAirLeftView *pView=(CTextOnAirLeftView *)m_wndSplitter.GetPane(0,0);
	pView->OnCut();
}

