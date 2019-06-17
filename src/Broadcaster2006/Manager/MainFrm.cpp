// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Manager.h"

#include "MainFrm.h"
#include "..\common\include\global.h"
#include "NationalitiesMain.h"
#include "Expressions.h"
#include "ErcMainDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame
extern	CManagerApp theApp;

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_ONAIRUSER, OnOnairuser)
	ON_COMMAND(ID_FOLDERS, OnFolders)
	ON_COMMAND(ID_TIME, OnTime)
	ON_COMMAND(ID_LOG, OnLog)
	ON_COMMAND(ID_USERS, OnUsers)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_TABLES_NATIONALITIES, &CMainFrame::OnTablesNationalities)
	ON_COMMAND(ID_TABLES_EXPRESSIONS, &CMainFrame::OnTablesExpressions)
	ON_COMMAND(ID_ERC_CRIAR, &CMainFrame::OnErcCriar)
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

/*	if( !g_Permissions.bManager )
	{
		CMenu *p = GetMenu();

		p->EnableMenuItem(ID_USERS,MF_BYCOMMAND|MF_GRAYED);
		p->EnableMenuItem(ID_ONAIRUSER,MF_BYCOMMAND|MF_GRAYED);
		p->EnableMenuItem(ID_TIME,MF_BYCOMMAND|MF_GRAYED);
		p->EnableMenuItem(ID_FOLDERS,MF_BYCOMMAND|MF_GRAYED);
	} */

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


void CMainFrame::OnOnairuser() 
{
	if( g_Permissions.bManager )
		theApp.pDocOnAirUser->OpenDocumentFile(NULL);	
}

void CMainFrame::OnFolders() 
{
	if( g_Permissions.bManagerFolder )
		theApp.pDocHD->OpenDocumentFile(NULL);
}

void CMainFrame::OnTime() 
{
	if( g_Permissions.bManagerTime )
		theApp.pDocTime->OpenDocumentFile(NULL);	
}

void CMainFrame::OnLog() 
{
	if( g_Permissions.bManagerLog )
		theApp.pDocLog->OpenDocumentFile(NULL);
}

void CMainFrame::OnUsers()
{
	if( g_Permissions.bManager )
		theApp.pDocUser->OpenDocumentFile(NULL);
}

void CMainFrame::OnTablesNationalities()
{
	CNationalitiesMain dlg;

	dlg.DoModal();
}

void CMainFrame::OnTablesExpressions()
{
	CExpressions dlg;

	dlg.DoModal();
}

void CMainFrame::OnErcCriar()
{
	CErcMainDlg dlg;

	dlg.DoModal();
}
