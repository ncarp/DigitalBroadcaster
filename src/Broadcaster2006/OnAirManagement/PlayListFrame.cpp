// PlayListFrame.cpp : implementation file
//

#include "stdafx.h"
#include "OnAirManagement.h"
#include "PlayListFrame.h"
#include "PlayListLeftView.h"
#include "PlayListRightView.h"
#include "..\OnAir\OnAirDefines.h"
#include "..\OnAir\PFLWND.h"
#include "..\traffic\RadioStation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static UINT indicators2[] = { ID_SEPARATOR,};

extern	CImageList	*g_ilToolBar;
extern	char		g_strToolBarLabels[];
extern	CPFLWnd		g_wndPFL;
/////////////////////////////////////////////////////////////////////////////
// CPlayListFrame

IMPLEMENT_DYNCREATE(CPlayListFrame, CMDIChildWnd)

CPlayListFrame::CPlayListFrame()
{
}

CPlayListFrame::~CPlayListFrame()
{
}


BEGIN_MESSAGE_MAP(CPlayListFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CPlayListFrame)
	ON_WM_CREATE()
	ON_COMMAND( CM_NEW,OnNew )
	ON_COMMAND( CM_EDIT, OnEdit )
	ON_COMMAND( CM_CUT, OnCut )
	ON_COMMAND( CM_PFL, OnPFL )
	ON_COMMAND( CM_QUERYBLOCKS, OnStat )
	ON_COMMAND( CM_INFO, OnInfo )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlayListFrame message handlers

int CPlayListFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	TBBUTTON	buttons[12];

	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_wndToolBar.Create(TBSTYLE_FLAT|CCS_BOTTOM,CRect(0,0,0,0),this,292);

	buttons[0].iBitmap=13;
	buttons[0].idCommand=CM_NEW;
	buttons[0].fsState=TBSTATE_ENABLED;
	buttons[0].fsStyle=TBSTYLE_BUTTON;
	buttons[0].dwData=0;
	buttons[0].iString=13;

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

	buttons[6].iBitmap=6;
	buttons[6].idCommand=CM_PFL;
	buttons[6].fsState=TBSTATE_ENABLED;
	buttons[6].fsStyle=TBSTYLE_BUTTON;
	buttons[6].dwData=0;
	buttons[6].iString=6;
	
	buttons[7].iBitmap=0;
	buttons[7].idCommand=CM_SCHEDULE;
	buttons[7].fsState=TBSTATE_ENABLED;
	buttons[7].fsStyle=TBSTYLE_SEP;
	buttons[7].dwData=0;
	buttons[7].iString=0;

	buttons[8].iBitmap=14 ;
	buttons[8].idCommand=CM_INFO;
	buttons[8].fsState=TBSTATE_ENABLED;
	buttons[8].fsStyle=TBSTYLE_BUTTON;
	buttons[8].dwData=0;
	buttons[8].iString=14;
	
	buttons[9].iBitmap=0;
	buttons[9].idCommand=CM_SCHEDULE;
	buttons[9].fsState=TBSTATE_ENABLED;
	buttons[9].fsStyle=TBSTYLE_SEP;
	buttons[9].dwData=0;
	buttons[9].iString=0;

	buttons[10].iBitmap=4;
	buttons[10].idCommand=CM_QUERYBLOCKS;
	buttons[10].fsState=TBSTATE_ENABLED;
	buttons[10].fsStyle=TBSTYLE_BUTTON;
	buttons[10].dwData=0;
	buttons[10].iString=4;
	
	buttons[11].iBitmap=0;
	buttons[11].idCommand=CM_SCHEDULE;
	buttons[11].fsState=TBSTATE_ENABLED;
	buttons[11].fsStyle=TBSTYLE_SEP;
	buttons[11].dwData=0;
	buttons[11].iString=0;

	m_wndToolBar.SetImageList(g_ilToolBar);
	m_wndToolBar.SetHotImageList(g_ilToolBar);
	m_wndToolBar.AddStrings(g_strToolBarLabels);
	m_wndToolBar.AddButtons(12,buttons);
	m_wndToolBar.AutoSize();

	m_wndReBar.Create(this);
	m_wndReBar.AddBar(&m_wndToolBar);
	
	m_wndStatusBar.Create(this);
	m_wndStatusBar.SetIndicators(indicators2,sizeof(indicators2)/sizeof(UINT));
	return 0;
}

BOOL CPlayListFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	CRadioStation dl;
	if( dl.DoModal()!=IDOK )
		return FALSE;

	m_wndSplitter.CreateStatic(this,1,2);
	m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CPlayListLeftView), CSize(400, 100), pContext);
	m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CPlayListRightView),CSize(100,100), pContext);

	CPlayListLeftView *pView = (CPlayListLeftView *)m_wndSplitter.GetPane(0,0);
	pView->m_strConnect = dl.m_strConnect;
	pView->m_strRadio = dl.m_strRadio;
	pView->m_strDB = dl.m_strDB;
	pView->m_lRadioID = dl.m_lRadioID;

	CPlayListRightView *pRView = (CPlayListRightView *)m_wndSplitter.GetPane(0,1);
	pView->m_rightView = pRView;
	pRView->m_strConnect = dl.m_strConnect;
	pRView->m_wndStatusBar = &m_wndStatusBar;
	pRView->m_lRadioID = dl.m_lRadioID;
	pRView->m_strDB = dl.m_strDB;

	return TRUE;
}

void CPlayListFrame::OnNew()
{
	CPlayListLeftView *pView = (CPlayListLeftView *)m_wndSplitter.GetPane(0,0);
	pView->OnNew();
}

void CPlayListFrame::OnEdit()
{
	CPlayListLeftView *pView = (CPlayListLeftView *)m_wndSplitter.GetPane(0,0);
	pView->OnDoubleClick();
}

void CPlayListFrame::OnCut()
{
	int row,col;

	m_wndSplitter.GetActivePane(&row,&col);

	if( col==0 )
	{
		CPlayListLeftView *pView = (CPlayListLeftView *)m_wndSplitter.GetPane(0,0);
		pView->OnCut();
	}
	else
	{
		CPlayListRightView *pView = (CPlayListRightView *)m_wndSplitter.GetPane(0,1);
		pView->OnCut();
	}
}

void CPlayListFrame::OnPFL()
{
	CPlayListRightView *pView = (CPlayListRightView *)m_wndSplitter.GetPane(0,1);
	pView->OnPFL();
}

void CPlayListFrame::OnInfo()
{
	CPlayListRightView *pView = (CPlayListRightView *)m_wndSplitter.GetPane(0,1);
	pView->OnInfo();
}

void CPlayListFrame::OnStat()
{
	CString str;

	str.Format("%s/musicstat.asp",g_strBaseURL);
	g_wndInfo->SetView(str);
}
