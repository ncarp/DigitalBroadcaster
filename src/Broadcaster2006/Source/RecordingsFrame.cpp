// RecordingsFrame.cpp : implementation file
//

#include "stdafx.h"

#include "..\include\RecordingsFrame.h"
#include "..\include\RecordingsLeftView.h"
#include "..\include\RecordingTask.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern	CImageList	*g_ilToolBar;
extern	char		g_strToolBarLabels[];

/////////////////////////////////////////////////////////////////////////////
// CRecordingsFrame

IMPLEMENT_DYNCREATE(CRecordingsFrame, CMDIChildWnd)

CRecordingsFrame::CRecordingsFrame()
{
}

CRecordingsFrame::~CRecordingsFrame()
{
}


BEGIN_MESSAGE_MAP(CRecordingsFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CRecordingsFrame)
	ON_WM_CREATE()
	ON_COMMAND( CM_NEW, OnNew)
	ON_COMMAND( CM_EDIT, OnEdit )
	ON_COMMAND( CM_CUT, OnCut )
	ON_COMMAND( CM_PFL, OnPFL )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRecordingsFrame message handlers

BOOL CRecordingsFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	m_wndSplitter.CreateStatic(this,1,2);
	m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CRecordingsLeftView), CSize(400, 100), pContext);
	m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CHtmlView),CSize(100,100), pContext);
	
	return TRUE;
}

int CRecordingsFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	TBBUTTON	buttons[10];

	m_wndToolBar.Create(TBSTYLE_FLAT|CCS_BOTTOM,CRect(0,0,0,0),this,292);

	buttons[0].iBitmap=5;
	buttons[0].idCommand=CM_NEW;
	buttons[0].fsState=TBSTATE_ENABLED;
	buttons[0].fsStyle=TBSTYLE_BUTTON;
	buttons[0].dwData=0;
	buttons[0].iString=5;

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

	buttons[7].iBitmap=6;
	buttons[7].idCommand=0;
	buttons[7].fsState=TBSTATE_ENABLED;
	buttons[7].fsStyle=TBSTYLE_SEP;
	buttons[7].dwData=0;
	buttons[7].iString=6;

	m_wndToolBar.SetImageList(g_ilToolBar);
	m_wndToolBar.SetHotImageList(g_ilToolBar);
	m_wndToolBar.AddStrings(g_strToolBarLabels);
	m_wndToolBar.AddButtons(8,buttons);
	m_wndToolBar.AutoSize();

	m_wndReBar.Create(this);
	m_wndReBar.AddBar(&m_wndToolBar);
	
	return 0;
}

void CRecordingsFrame::OnNew()
{
	CRecordingsLeftView *pView = (CRecordingsLeftView *)m_wndSplitter.GetPane(0,0);
	pView->OnNew();
}

void CRecordingsFrame::OnEdit()
{
	CRecordingsLeftView *pView = (CRecordingsLeftView *)m_wndSplitter.GetPane(0,0);
	pView->OnDoubleClick();
}

void CRecordingsFrame::OnCut()
{
	CRecordingsLeftView *pView = (CRecordingsLeftView *)m_wndSplitter.GetPane(0,0);
	pView->OnCut();
}

void CRecordingsFrame::OnPFL()
{
	CRecordingsLeftView *pView = (CRecordingsLeftView *)m_wndSplitter.GetPane(0,0);
	pView->OnPFL();
}

