// CalendarFrame.cpp : implementation file
//

#include "stdafx.h"
#include "Scheduler.h"
#include "CalendarFrame.h"
#include "CalendarRightView.h"
#include "CalendarLeftView.h"
#include "..\onair\onairdefines.h"
#include "..\Traffic\RadioStation.h"
#include "..\common\include\global.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CImageList	*g_ilToolBar;
extern char			g_strToolBarLabels[];
/////////////////////////////////////////////////////////////////////////////
// CCalendarFrame

IMPLEMENT_DYNCREATE(CCalendarFrame, CMDIChildWnd)

CCalendarFrame::CCalendarFrame()
{
}

CCalendarFrame::~CCalendarFrame()
{
}


BEGIN_MESSAGE_MAP(CCalendarFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CCalendarFrame)
	ON_WM_CREATE()
	ON_COMMAND( CM_NEW, OnNew )
	ON_COMMAND( CM_EDIT, OnEditHeadline )
	ON_COMMAND( CM_EDITLINEUP, OnEditSchedule )
	ON_COMMAND( CM_CUT, OnCut )
	ON_COMMAND( CM_PFL, OnPFL )
	ON_COMMAND( CM_INFO, OnInfo )
	ON_COMMAND( CM_STATISTICS,OnStatistics )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalendarFrame message handlers

int CCalendarFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	TBBUTTON	buttons[13];

	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_wndToolBar.Create(TBSTYLE_FLAT|CCS_BOTTOM,CRect(0,0,0,0),this,292);

	buttons[0].iBitmap=3;
	buttons[0].idCommand=CM_NEW;
	buttons[0].fsState=TBSTATE_ENABLED;
	buttons[0].fsStyle=TBSTYLE_BUTTON;
	buttons[0].dwData=0;
	buttons[0].iString=3;

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


	buttons[4].iBitmap=14;
	buttons[4].idCommand=CM_EDITLINEUP;
	buttons[4].fsState=TBSTATE_ENABLED;
	buttons[4].fsStyle=TBSTYLE_BUTTON;
	buttons[4].dwData=0;
	buttons[4].iString=14;

	buttons[5].iBitmap=1;
	buttons[5].idCommand=0;
	buttons[5].fsState=TBSTATE_ENABLED;
	buttons[5].fsStyle=TBSTYLE_SEP;
	buttons[5].dwData=0;
	buttons[5].iString=1;

	buttons[6].iBitmap=2;
	buttons[6].idCommand=CM_CUT;
	buttons[6].fsState=TBSTATE_ENABLED;
	buttons[6].fsStyle=TBSTYLE_BUTTON;
	buttons[6].dwData=0;
	buttons[6].iString=2;

	buttons[7].iBitmap=1;
	buttons[7].idCommand=0;
	buttons[7].fsState=TBSTATE_ENABLED;
	buttons[7].fsStyle=TBSTYLE_SEP;
	buttons[7].dwData=0;
	buttons[7].iString=1;

	buttons[8].iBitmap=6;
	buttons[8].idCommand=CM_PFL;
	buttons[8].fsState=TBSTATE_ENABLED;
	buttons[8].fsStyle=TBSTYLE_BUTTON;
	buttons[8].dwData=0;
	buttons[8].iString=6;
	
	buttons[9].iBitmap=0;
	buttons[9].idCommand=CM_SCHEDULE;
	buttons[9].fsState=TBSTATE_ENABLED;
	buttons[9].fsStyle=TBSTYLE_SEP;
	buttons[9].dwData=0;
	buttons[9].iString=0;

	buttons[10].iBitmap=17;
	buttons[10].idCommand=CM_INFO;
	buttons[10].fsState=TBSTATE_ENABLED;
	buttons[10].fsStyle=TBSTYLE_BUTTON;
	buttons[10].dwData=0;
	buttons[10].iString=17;

	buttons[11].iBitmap=0;
	buttons[11].idCommand=0;
	buttons[11].fsState=TBSTATE_ENABLED;
	buttons[11].fsStyle=TBSTYLE_SEP;
	buttons[11].dwData=0;
	buttons[11].iString=0;

	buttons[12].iBitmap=17;
	buttons[12].idCommand=CM_STATISTICS;
	buttons[12].fsState=TBSTATE_ENABLED;
	buttons[12].fsStyle=TBSTYLE_BUTTON;
	buttons[12].dwData=0;
	buttons[12].iString=18;


	m_wndToolBar.SetImageList(g_ilToolBar);
	m_wndToolBar.SetHotImageList(g_ilToolBar);
	m_wndToolBar.AddStrings(g_strToolBarLabels);
	m_wndToolBar.AddButtons(13,buttons);
	m_wndToolBar.AutoSize();

	m_wndReBar.Create(this);
	m_wndReBar.AddBar(&m_wndToolBar);
	
	return 0;
}

BOOL CCalendarFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	CRadioStation dl;
	dl.DoModal();

	m_wndSplitter.CreateStatic(this,1,2);
	m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CCalendarLeftView), CSize(400, 100), pContext);
	m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CCalendarRightView),CSize(100,100), pContext);

	CCalendarLeftView *pView = (CCalendarLeftView *)m_wndSplitter.GetPane(0,0);
	pView->m_strConnect = dl.m_strConnect;
	pView->m_strRadio = dl.m_strRadio;
	pView->m_strDB = dl.m_strDB;
	pView->m_pRightView = (CCalendarRightView *)m_wndSplitter.GetPane(0,1);
	pView->m_pRightView->m_strConnect = dl.m_strConnect;
	pView->m_lRadioID = dl.m_lRadioID;
	pView->m_pRightView->m_lRadioID = dl.m_lRadioID;
	pView->m_pRightView->m_strDB = dl.m_strDB;

	return TRUE;
}

void CCalendarFrame::OnNew()
{
	if( !g_Permissions.bLineupAdd )
		return;

	CCalendarLeftView *pView = (CCalendarLeftView *)m_wndSplitter.GetPane(0,0);
	pView->OnNew();
}

void CCalendarFrame::OnEditHeadline()
{
	if( !g_Permissions.bLineupEdit )
		return;

	CCalendarLeftView *pView = (CCalendarLeftView *)m_wndSplitter.GetPane(0,0);
	pView->OnEditHeadline();
}

void CCalendarFrame::OnEditSchedule()
{
	if( !g_Permissions.bScheduleEdit && 
			!g_Permissions.bCriteriaAdd && !g_Permissions.bCriteriaCut && !g_Permissions.bCriteriaEdit &&
			!g_Permissions.bVoiceAdd && !g_Permissions.bVoiceCut && !g_Permissions.bVoiceEdit )
		return;

	CCalendarLeftView *pView = (CCalendarLeftView *)m_wndSplitter.GetPane(0,0);
	pView->OnEditSchedule();
}

void CCalendarFrame::OnCut()
{
	if( !g_Permissions.bLineupCut )
		return;

	CCalendarLeftView *pView = (CCalendarLeftView *)m_wndSplitter.GetPane(0,0);
	pView->OnCut();
}

void CCalendarFrame::OnPFL()
{
	CCalendarRightView *pView = (CCalendarRightView *)m_wndSplitter.GetPane(0,1);
	pView->OnPFL();
}

void CCalendarFrame::OnInfo()
{
	int	nRow,
		nCol;

	CWnd *pViewTemp = m_wndSplitter.GetActivePane(&nRow,&nCol);

	if( pViewTemp==NULL )
		return;

	if( nCol==1 )
	{
		CCalendarRightView *pView = (CCalendarRightView *)pViewTemp;
		pView->OnInfo();
	}
	else
	{
		CCalendarLeftView *pView = (CCalendarLeftView *)pViewTemp;
		pView->OnInfo();
	}
}

void CCalendarFrame::OnStatistics()
{
	CString strURL;
	CCalendarRightView *pView = (CCalendarRightView *)m_wndSplitter.GetPane(0,1);

	strURL.Format("%s/AiredMusicStatMain.asp?DB=%s",g_strBaseURL,pView->m_strDB);
//	AfxMessageBox(strURL);
	g_wndInfo->SetView(strURL);
}