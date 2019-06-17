// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Scheduler.h"

#include "MainFrm.h"
#include "..\OnAir\PFLWnd.h"
#include "..\hasp\hasp.h"
#include "..\include\haspcode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CPFLWnd	*g_wndPFL;
extern	CSchedulerApp	theApp;
/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_SCHEDULE, OnSchedule)
	ON_COMMAND(ID_VIEW_VERTICAL, OnViewVertical)
	ON_COMMAND(ID_VIEW_HORIZONTAL, OnViewHorizontal)
	ON_COMMAND(ID_HELP_HELP, OnHelpHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	g_wndPFL = new CPFLWnd();
	g_wndPFL->CreateEx(WS_EX_TOOLWINDOW,NULL,"Digital Broadcaster 2006 - PFL",WS_SYSMENU|WS_MINIMIZEBOX|WS_POPUP|WS_VISIBLE|WS_CAPTION,CRect(0,0,512,115),this,0);
	g_wndPFL->OnClose();
	g_wndPFL->m_bTopMost=FALSE;

	int X = GetSystemMetrics(SM_CXMAXIMIZED),
		Y = GetSystemMetrics(SM_CYMAXIMIZED);

	g_wndInfo = new CHtmlInfo();
	g_wndInfo->CreateEx(WS_EX_TOOLWINDOW,NULL,"Digital Broadcaster 2006 - Info",WS_SYSMENU|WS_MINIMIZEBOX|WS_POPUP|WS_VISIBLE|WS_CAPTION|WS_THICKFRAME,CRect(X-800,Y-600,X,Y),this,0);
	g_wndInfo->OnClose();

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnSchedule() 
{
	if( !g_Permissions.bScheduler )
		return;

	int	par1,par2,par3,par4;

	if( HASP_HASPPROTECTION && HASP_WORKSTATION)
	{
		if( HASP_TIMEKEY )
			hasp(78,0,0,HASP_PASS1,HASP_PASS2,&par1,&par2,&par3,&par4);
		else if( HASP_4 )
			hasp(6,0,0,HASP_PASS1,HASP_PASS2,&par1,&par2,&par3,&par4);
		else
		{
			hasp(5,0,0,HASP_PASS1,HASP_PASS2,&par1,&par2,&par3,&par4);
			if( par3!=0 )
				par3=0;
			else
				par3=-1;
		}
		if( (par3!=0) || ((par1!=HASP_IDLOW) && (HASP_IDLOW!=0)) || ((par2!=HASP_IDHIGH) && (HASP_IDHIGH!=0)) )
		{
			return;
		}
	}

	theApp.m_pDocCalendar->OpenDocumentFile(NULL);	
}

void CMainFrame::OnViewVertical() 
{
	MDITile(MDITILE_VERTICAL);
}

void CMainFrame::OnViewHorizontal() 
{
	MDITile(MDITILE_HORIZONTAL);	
}

void CMainFrame::OnHelpHelp() 
{
	CString str;
	
	str.Format("%s/manual/Scheduler.pdf",g_strBaseURL);

	if( g_wndInfo->m_pView->GetLocationURL()==str )
		g_wndInfo->RestoreWindow();
	else
		g_wndInfo->SetView(str);	
}
