// ScheduleFrame.cpp : implementation file
//

#include "stdafx.h"
#include "Scheduler.h"
#include "ScheduleFrame.h"
#include "ScheduleLeftView.h"
#include "ScheduleRightView.h"
#include "..\OnAir\OnAirDefines.h"
#include "..\include\RSScheduleTemplate.h"
#include "..\common\include\global.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern	CImageList	*g_ilToolBar;
extern	char		g_strToolBarLabels[];

/////////////////////////////////////////////////////////////////////////////
// CScheduleFrame

IMPLEMENT_DYNCREATE(CScheduleFrame, CMDIChildWnd)

CScheduleFrame::CScheduleFrame()
{
}

CScheduleFrame::~CScheduleFrame()
{
}


BEGIN_MESSAGE_MAP(CScheduleFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CScheduleFrame)
	ON_WM_CREATE()
	ON_COMMAND( CM_EDIT, OnEdit )
	ON_COMMAND( CM_CUT, OnCut )
	ON_COMMAND( CM_PFL, OnPFL )
	ON_COMMAND( CM_LOCK, OnLock )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScheduleFrame message handlers

int CScheduleFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_wndToolBar.Create(TBSTYLE_FLAT|CCS_BOTTOM,CRect(0,0,0,0),this,292);

	TBBUTTON	buttons[10];

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

	buttons[4].iBitmap=16;
	buttons[4].idCommand=CM_LOCK;
	buttons[4].fsState=TBSTATE_ENABLED;
	buttons[4].fsStyle=TBSTYLE_BUTTON;
	buttons[4].dwData=0;
	buttons[4].iString=16;

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

	m_wndToolBar.SetImageList(g_ilToolBar);
	m_wndToolBar.SetHotImageList(g_ilToolBar);
	m_wndToolBar.AddStrings(g_strToolBarLabels);
	m_wndToolBar.AddButtons(8,buttons);
	m_wndToolBar.AutoSize();

	m_wndReBar.Create(this);
	m_wndReBar.AddBar(&m_wndToolBar);
	
	return 0;
	
}

BOOL CScheduleFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	m_wndSplitter.CreateStatic(this,1,2);
	m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CScheduleLeftView), CSize(400, 100), pContext);
	m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CScheduleRightView),CSize(100,100), pContext);

	CScheduleRightView *pView = (CScheduleRightView *)m_wndSplitter.GetPane(0,1);
	pView->m_pLeft = (CScheduleLeftView *)m_wndSplitter.GetPane(0,0);

	return TRUE;
}

void CScheduleFrame::OnPFL()
{
	int	nCol,nRow;

	CWnd *pTemp=m_wndSplitter.GetActivePane(&nRow,&nCol);

	if( nCol == 0 )
	{
		((CScheduleLeftView *)pTemp)->OnPFL();
	}
	else
	{
		((CScheduleRightView *)pTemp)->OnPFL();
	}
}

void CScheduleFrame::OnLock()
{
	if( !g_Permissions.bScheduleEdit )
		return;

	CScheduleRightView *pView = (CScheduleRightView *)m_wndSplitter.GetPane(0,1);
	pView->OnLockItem();
}

void CScheduleFrame::OnCut()
{
	int	nCol,nRow;

	CWnd *pTemp=m_wndSplitter.GetActivePane(&nRow,&nCol);

	if( nCol == 0 )
	{
		((CScheduleLeftView *)pTemp)->OnCut();
	}
	else
	{
		((CScheduleRightView *)pTemp)->OnCut();
	}
}

void CScheduleFrame::OnEdit() 
{
	CScheduleLeftView *pView = (CScheduleLeftView *)m_wndSplitter.GetPane(0,0);
	pView->OnDoubleClick();
}