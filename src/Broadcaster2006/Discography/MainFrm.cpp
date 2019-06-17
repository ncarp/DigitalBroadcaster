#include "..\onair_slave\mainfrm.h"
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Discography.h"

#include "MainFrm.h"
#include "LeftView.h"
#include "DiscographyView.h"
#include "Music.h"
#include "..\OnAir\PFLWnd.H" 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CImageList	*g_ilToolBar;
extern char			g_strToolBarLabels[];

CPFLWnd				*g_wndPFL;

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI_RANGE(AFX_ID_VIEW_MINIMUM, AFX_ID_VIEW_MAXIMUM, OnUpdateViewStyles)
	ON_COMMAND_RANGE(AFX_ID_VIEW_MINIMUM, AFX_ID_VIEW_MAXIMUM, OnViewStyle)
	ON_COMMAND( CM_NEW, OnNew )
	ON_COMMAND( CM_EDIT, OnEdit )
	ON_COMMAND( CM_PFL, OnPFL )
	ON_COMMAND( CM_CUT, OnCut )
	ON_COMMAND( CM_INFO, OnInfo )
	ON_COMMAND( ID_HELP_HELP, OnHelp )
	ON_WM_SYSCOMMAND()
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
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	TBBUTTON	buttons[10];
	buttons[0].iBitmap=14;
	buttons[0].idCommand=CM_NEW;
	buttons[0].fsState=TBSTATE_ENABLED;
	buttons[0].fsStyle=TBSTYLE_BUTTON;
	buttons[0].dwData=0;
	buttons[0].iString=14;

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

	buttons[8].iBitmap=4;
	buttons[8].idCommand=CM_INFO;
	buttons[8].fsState=TBSTATE_ENABLED;
	buttons[8].fsStyle=TBSTYLE_BUTTON;
	buttons[8].dwData=0;
	buttons[8].iString=15;
	
	buttons[9].iBitmap=0;
	buttons[9].idCommand=CM_SCHEDULE;
	buttons[9].fsState=TBSTATE_ENABLED;
	buttons[9].fsStyle=TBSTYLE_SEP;
	buttons[9].dwData=0;
	buttons[9].iString=0;
	
	m_wndToolBar.Create(TBSTYLE_FLAT|CCS_BOTTOM,CRect(10,10,100,100),this,292);
	m_wndToolBar.SetImageList(g_ilToolBar);
	m_wndToolBar.SetHotImageList(g_ilToolBar);
	m_wndToolBar.AddStrings(g_strToolBarLabels);
	m_wndToolBar.AddButtons(10,buttons);
	m_wndToolBar.AutoSize();

	if ( !m_wndReBar.Create(this) || !m_wndReBar.AddBar(&m_wndToolBar) )
	{
		TRACE0("Failed to create rebar\n");
		return -1;      // fail to create
	}

	g_wndPFL = new CPFLWnd();
	g_wndPFL->CreateEx(WS_EX_TOOLWINDOW,NULL,"Digital Broadcaster 2006 - PFL",WS_SYSMENU|WS_MINIMIZEBOX|WS_POPUP|WS_VISIBLE|WS_CAPTION,CRect(0,0,512,115),this,0);
	g_wndPFL->OnClose();
	g_wndPFL->m_bTopMost = FALSE;
/*
	if( !g_Permissions.bDiscographyAdd )
		m_wndToolBar.EnableButton( CM_NEW,FALSE );

	if( !g_Permissions.bDiscographyDelete )
		m_wndToolBar.EnableButton( CM_REMOVE,FALSE );

	if( !g_Permissions.bDiscographyEdit )
		m_wndToolBar.EnableButton( CM_EDIT,FALSE);

	if( !g_Permissions.bDiscography )
		m_wndToolBar.EnableButton( CM_INFO,FALSE);
*/
	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	// create splitter window
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
		return FALSE;

	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CLeftView), CSize(400, 100), pContext) ||
		!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CHtmlView), CSize(100, 100), pContext))
	{
		m_wndSplitter.DestroyWindow();
		return FALSE;
	}

	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
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
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

CDiscographyView* CMainFrame::GetRightPane()
{
	CWnd* pWnd = m_wndSplitter.GetPane(0, 1);
	CDiscographyView* pView = DYNAMIC_DOWNCAST(CDiscographyView, pWnd);
	return pView;
}

void CMainFrame::OnUpdateViewStyles(CCmdUI* pCmdUI)
{
	// TODO: customize or extend this code to handle choices on the
	// View menu.

	CDiscographyView* pView = GetRightPane(); 

	// if the right-hand pane hasn't been created or isn't a view,
	// disable commands in our range

	if (pView == NULL)
		pCmdUI->Enable(FALSE);
	else
	{
		DWORD dwStyle = pView->GetStyle() & LVS_TYPEMASK;

		// if the command is ID_VIEW_LINEUP, only enable command
		// when we're in LVS_ICON or LVS_SMALLICON mode

		if (pCmdUI->m_nID == ID_VIEW_LINEUP)
		{
			if (dwStyle == LVS_ICON || dwStyle == LVS_SMALLICON)
				pCmdUI->Enable();
			else
				pCmdUI->Enable(FALSE);
		}
		else
		{
			// otherwise, use dots to reflect the style of the view
			pCmdUI->Enable();
			BOOL bChecked = FALSE;

			switch (pCmdUI->m_nID)
			{
			case ID_VIEW_DETAILS:
				bChecked = (dwStyle == LVS_REPORT);
				break;

			case ID_VIEW_SMALLICON:
				bChecked = (dwStyle == LVS_SMALLICON);
				break;

			case ID_VIEW_LARGEICON:
				bChecked = (dwStyle == LVS_ICON);
				break;

			case ID_VIEW_LIST:
				bChecked = (dwStyle == LVS_LIST);
				break;

			default:
				bChecked = FALSE;
				break;
			}

			pCmdUI->SetRadio(bChecked ? 1 : 0);
		}
	}
}


void CMainFrame::OnViewStyle(UINT nCommandID)
{
	// TODO: customize or extend this code to handle choices on the
	// View menu.
	CDiscographyView* pView = GetRightPane();

	// if the right-hand pane has been created and is a CDiscographyView,
	// process the menu commands...
	if (pView != NULL)
	{
		DWORD dwStyle = -1;

		switch (nCommandID)
		{
		case ID_VIEW_LINEUP:
			{
				// ask the list control to snap to grid
				CListCtrl& refListCtrl = pView->GetListCtrl();
				refListCtrl.Arrange(LVA_SNAPTOGRID);
			}
			break;

		// other commands change the style on the list control
		case ID_VIEW_DETAILS:
			dwStyle = LVS_REPORT;
			break;

		case ID_VIEW_SMALLICON:
			dwStyle = LVS_SMALLICON;
			break;

		case ID_VIEW_LARGEICON:
			dwStyle = LVS_ICON;
			break;

		case ID_VIEW_LIST:
			dwStyle = LVS_LIST;
			break;
		}

		// change the style; window will repaint automatically
		if (dwStyle != -1)
			pView->ModifyStyle(LVS_TYPEMASK, dwStyle);
	}
}


void CMainFrame::OnNew()
{
	if( !g_Permissions.bDiscographyAdd )
		return;

	CLeftView *pView = (CLeftView *)m_wndSplitter.GetPane(0,0);
	pView->OnNew();
}

void CMainFrame::OnEdit()
{
	if( !g_Permissions.bDiscographyEdit )
		return;

	CLeftView *pView = (CLeftView *)m_wndSplitter.GetPane(0,0);
	pView->OnDoubleClick();
}

void CMainFrame::OnCut()
{
	if( !g_Permissions.bDiscographyDelete )
		return;

	CLeftView *pView = (CLeftView *)m_wndSplitter.GetPane(0,0);
	pView->OnCut();
}

void CMainFrame::OnPFL()
{
	if( !g_Permissions.bDiscography )
		return;

	CLeftView *pView = (CLeftView *)m_wndSplitter.GetPane(0,0);
	pView->OnPFL();
}

void CMainFrame::OnInfo()
{
	if( !g_Permissions.bDiscography )
		return;

	CLeftView *pView = (CLeftView *)m_wndSplitter.GetPane(0,0);

	pView->SetView(g_strBaseURL+"/musicstat.asp");
}

void CMainFrame::OnHelp()
{
	CHtmlView *pView = (CHtmlView *)m_wndSplitter.GetPane(0,1);

	CString strURL;

	strURL.Format("%s/manual/discography.pdf",g_strBaseURL);
	pView->Navigate(strURL);
}

void CMainFrame::OnSysCommand(UINT nID, LPARAM lParam)
{
	CFrameWnd::OnSysCommand(nID, lParam);
}
