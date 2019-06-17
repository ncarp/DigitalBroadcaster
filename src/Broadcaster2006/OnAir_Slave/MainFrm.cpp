// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "OnAir_Slave.h"
#include <gdiplus.h>
using namespace Gdiplus;

#include "MainFrm.h"
#include "..\hasp\hasp.h"
#include "..\include\haspcode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern	CControlWnd		*g_pControlWnd;
extern	COnAirSplitter	*g_pSplitter[];
extern	BOOL			g_bTimeOut;

COleDateTime	dtLimit=COleDateTime(HASP_TIME_YEAR,HASP_TIME_MONTH,HASP_TIME_DAY,0,0,0);
int m_nHaspFailed;

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_pContainer1 = NULL;
	m_pContainer2 = NULL;
	m_pControl = NULL;
	m_pSplitter[0] = NULL;
	m_pSplitter[1] = NULL;
	m_pSplitter[2] = NULL;
	m_pSplitter[3] = NULL;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect			crect;
	BOOL			bWideScreen;
	int				nWidth;

	GetClientRect(&crect);

	nWidth=crect.Width();
	
	if( nWidth>1024 )
		nWidth=(nWidth-426)/2;
	else
		nWidth=nWidth-426;

	if( crect.Width()>crect.Height()*2 )
		bWideScreen=TRUE;
	else
		bWideScreen=FALSE;

	m_pControl = new CControlWnd();
	m_pControl->CreateEx(0,NULL,NULL,WS_VISIBLE|WS_POPUP,CRect(0,0,426,crect.bottom),this,0);
	g_pControlWnd = m_pControl;

//	m_pControl->BringWindowToTop();

	m_pContainer1 = new COnAirContainerWnd();
	m_pContainer1->CreateEx(0,NULL,NULL,WS_VISIBLE|WS_POPUP,CRect(426,0,427+nWidth,crect.bottom),this,0);

	if( crect.Width()>1024 )
	{
		m_pContainer2 = new COnAirContainerWnd();
		m_pContainer2->CreateEx(0,NULL,NULL,WS_VISIBLE|WS_POPUP,CRect(427+nWidth,0,crect.right,crect.bottom),this,0);
	}

	m_pContainer1->GetClientRect(&crect);
	crect.DeflateRect(2,40,2,2);

	for( int i=0; i<4; i++ )
	{
		m_pSplitter[i] = new COnAirSplitter();
		m_pSplitter[i]->m_bEnabled = FALSE;
		m_pSplitter[i]->m_wNSplitter = i;
		m_pSplitter[i]->Create(NULL,NULL,WS_VISIBLE|WS_POPUP,crect,this);
		m_pSplitter[i]->MoveWindow(0,0,0,0);
		m_pSplitter[i]->ReadConfig();
		g_pSplitter[i]=m_pSplitter[i];
	}

	m_pContainer1->GetClientRect(&crect);
	crect.DeflateRect(2,2,2,2);
	m_pSplitter[0]->SetParent(m_pContainer1);
	m_pSplitter[0]->MoveWindow(&crect);
	m_pSplitter[0]->BringWindowToTop();

	if( m_pContainer2!=NULL )
	{
		m_pContainer2->GetClientRect(&crect);
		crect.DeflateRect(2,2,2,2);
		m_pSplitter[1]->SetParent(m_pContainer2);
		m_pSplitter[1]->MoveWindow(&crect);
		m_pSplitter[1]->BringWindowToTop();
		m_pSplitter[1]->EnableWindow(TRUE); 
	}

	SetTimer(1001,15000,NULL);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;

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
void CMainFrame::OnSetFocus(CWnd* pOldWnd)
{
	// forward focus to the view window
	SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// let the view have first crack at the command
//	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
//		return TRUE;

	// otherwise, do default handling
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	int	par1,par2,par3,par4;

	if( HASP_HASPPROTECTION )
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
			m_nHaspFailed++;
			if( m_nHaspFailed>4 )
			{
				AfxMessageBox(IDS_HASPERROR,MB_APPLMODAL);
				PostQuitMessage(0);
			}
		}

		if( HASP_TIMEONKEY )
		{
			int iService;
			int		dwYear,
					dwMonth,
					dwDay;

			if( HASP_TIMEKEY )
				iService=75;
			else
				iService=3;

			par1=0;
			hasp(iService,0,0,HASP_PASS1,HASP_PASS2,&par1,&dwYear,&par3,&par4);
			dwYear+=2000;
			par1=1;
			hasp(iService,0,0,HASP_PASS1,HASP_PASS2,&par1,&dwMonth,&par3,&par4);
			par2=2;
			hasp(iService,0,0,HASP_PASS1,HASP_PASS2,&par1,&dwDay,&par3,&par4);

			dtLimit = COleDateTime(dwYear,dwMonth,dwDay,23,59,59);
		}
	}

	if( HASP_TIMEPROTECTION )
	{
		COleDateTime t;
		
		if( HASP_TIMEKEY )
		{
			hasp(73,0,0,HASP_PASS1,HASP_PASS2,&par1,&par2,&par3,&par4);
			if( (par3!=0) )
			{
				if( m_nHaspFailed>4 )
				{
					AfxMessageBox(IDS_HASPERROR,MB_APPLMODAL);
					PostQuitMessage(0);
					return;
				}
			}
			t=COleDateTime(par4+2000,par2,par1,23,59,59);
		}
		else
			t=COleDateTime::GetCurrentTime();

		if( t>dtLimit )
		{
			g_bTimeOut=TRUE;
			if( HASP_TIMECRASH )
				memcpy(0,(LPVOID)1000,20000);
		}
	} 

}
