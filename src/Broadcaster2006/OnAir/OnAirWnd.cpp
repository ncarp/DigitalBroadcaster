// OnAirWnd.cpp : implementation file
//

#include "stdafx.h"

#include <gdiplus.h>
using namespace Gdiplus;

#include "..\include\utils.h"

#include "OnAir.h"
#include "OnAirWnd.h"
#include "ExternalObjects.h"
#include "CartwallWnd.h"
#include "ContainerWnd.h"
#include "OnAirUtils.h"
#include "PFLWnd.h"
#include "LogOnBack.h"
#include "..\hasp\hasp.h"
#include "..\include\haspcode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define	IDT_STARTUP	1001
#define IDT_HASP	1002

extern BOOL g_bFastStart;

CLogOnBack	*g_wndLogOnBack;
CStatusWnd	*g_wndStatus;	
CMusicInfo	*g_wndMusicInfo;
BOOL		g_bHaspOK=TRUE;
int			g_nHaspCount=960;

COleDateTime	dtLimit=COleDateTime(HASP_TIME_YEAR,HASP_TIME_MONTH,HASP_TIME_DAY,0,0,0);

/////////////////////////////////////////////////////////////////////////////
// COnAirWnd

COnAirWnd::COnAirWnd()
{
	m_nStartupStep = 0;
	m_nHaspFailed = 0;
}

COnAirWnd::~COnAirWnd()
{
}

BEGIN_MESSAGE_MAP(COnAirWnd, CWnd)
	//{{AFX_MSG_MAP(COnAirWnd)
	ON_WM_CREATE()
	ON_WM_ACTIVATE()
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_SYSCOLORCHANGE()
	ON_WM_ERASEBKGND()
	ON_WM_KEYUP()
	ON_WM_SYSKEYUP()
	ON_MESSAGE( UM_USERLOGOFF,OnUserLogOff)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// COnAirWnd message handlers

int COnAirWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CCartwallWnd	*wndCartwall;
	CLineUpWnd		*wndLineUp;
	CRect			crect;
	BOOL			bWideScreen;

	GetClientRect(&crect);

	if( crect.Width()>crect.Height()*2 )
		bWideScreen=TRUE;
	else
		bWideScreen=FALSE;

	OnSysColorChange();

	///////////////////////////////////////////////////////////////////////
	//	Main Clock
	m_wndMainClock = new CMainClockWnd();
	m_wndMainClock->Create(NULL,WS_VISIBLE,CRect(crect.right-150,0,crect.right,100),this);
	if( bWideScreen )
	{
		m_wndMainClock = new CMainClockWnd();
		m_wndMainClock->Create(NULL,WS_VISIBLE,CRect(0,0,150,100),this);
	}
	
	////////////////////////////////////////////////////////////////////////////
	//	Create logo's window
	m_wndLogoLeft = new CLogoWnd();
	m_wndLogoLeft->Create(NULL,SS_NOTIFY|WS_VISIBLE,CRect(crect.right-150,crect.bottom-100,crect.right,crect.bottom),this);

	if( bWideScreen )
	{
		m_wndLogoRight = new CLogoWnd();
		m_wndLogoRight->Create(NULL,WS_VISIBLE,CRect(0,crect.bottom-100,150,crect.bottom),this);
	}
	else
		m_wndLogoRight=NULL;

	/////////////////////////////////////////////////////////////////////////////
	//	Traffic window
	g_wndTrafficInfo = new CTrafficInfoWnd();
	g_wndTrafficInfo->Create(NULL,WS_VISIBLE|SS_NOTIFY,CRect(crect.right-150,400,crect.right,500),this);

	/////////////////////////////////////////////////////////////////////////////
	//	Scheduling info
	g_wndProgInfo = new CProgInfoWnd();
	g_wndProgInfo->Create(NULL,WS_VISIBLE|SS_NOTIFY,CRect(crect.right-150,500,crect.right,600),this);

	//////////////////////////////////////////////////////////////////////////////
	//	Timers
	m_wndInfo = new CGenericInfoWnd();
	m_wndInfo->Create(NULL,SS_NOTIFY|WS_VISIBLE,CRect(crect.right-150,300,crect.right,400),this);

	///////////////////////////////////////////////////////////////////////////////
	//	Status
	m_wndStatus = new CStatusWnd();
	m_wndStatus->Create(NULL,SS_NOTIFY|WS_VISIBLE,CRect(crect.right-150,100,crect.right,300),this);
	g_wndStatus = m_wndStatus;

	////////////////////////////////////////////////////////////////////////////////
	//	VU1
	m_wndVU1 = new CWndVU();
	m_wndVU1->Create(NULL,SS_NOTIFY|WS_VISIBLE,CRect(crect.right-150,600,crect.right,crect.bottom-100),this);

	if( bWideScreen )
	{
		m_wndVU2 = new CWndVU();
		m_wndVU2->Create(NULL,SS_NOTIFY|WS_VISIBLE,CRect(crect.left,crect.top+100,crect.left+150,crect.bottom-100),this);
	}

	if( bWideScreen )
		CreateToolBackground((crect.right-300)/4-4,62);
	else
		CreateToolBackground((crect.right-150)/2-2,62);

	/////////////////////////////////////////////////////////////////////////////////
	//	Cartwall
	wndCartwall = new CCartwallWnd();
	
	/////////////////////////////////////////////////////////////////////////////////
	//	Line Up
	wndLineUp = new CLineUpWnd();
	if( bWideScreen )
		wndLineUp->Create(NULL,"LineUp",WS_VISIBLE|WS_POPUP,CRect(0,0,(crect.right-300)/4,crect.bottom),this);
	else
		wndLineUp->Create(NULL,"LineUp",WS_VISIBLE|WS_POPUP,CRect(0,0,(crect.right-150)/2,crect.bottom),this);
	g_wndLineUp = (CWnd *)wndLineUp;

	//////////////////////////////////////////////////////////////////////////////////
	//	PFL
	g_wndPFL = new CPFLWnd();

	//////////////////////////////////////////////////////////////////////////////////
	//	Aired
	g_wndAired = new CAiredWnd();
	

	g_wndLogOnBack = new CLogOnBack();
	g_wndLogOnBack->CreateEx(WS_EX_TRANSPARENT,NULL,"Digital Broadcaster 2006 - Log On",WS_POPUP|WS_VISIBLE,crect,this,0);

	//////////////////////////////////////////////////////////////////////////////////
	//	Log On
	g_wndLogOn = new CLogOn();
	g_wndLogOn->CreateEx(WS_EX_TOOLWINDOW|WS_EX_TOPMOST,NULL,"Digital Broadcaster 2006 - Log On",WS_POPUP|WS_VISIBLE|WS_CAPTION,CRect(100,300,500,480),this,0);

	//////////////////////////////////////////////////////////////////////////////////
	// Music Info
	g_wndMusicInfo = new CMusicInfo();


	if( bWideScreen )
	{
		g_wndPFL->CreateEx(WS_EX_TOOLWINDOW|WS_EX_TOPMOST,NULL,"Digital Broadcaster 2006 - PFL",WS_SYSMENU|WS_MINIMIZEBOX|WS_POPUP|WS_VISIBLE|WS_CAPTION,CRect(0,0,(crect.right-300)/4,115),this,0);
		g_wndPFL->OnClose();

		g_wndMusicInfo->CreateEx(WS_EX_TOOLWINDOW|WS_EX_TOPMOST,NULL,"Digital Broadcaster 2006 - Info",WS_SYSMENU|WS_MINIMIZEBOX|WS_POPUP|WS_VISIBLE|WS_CAPTION,CRect(crect.CenterPoint().x-crect.Width()/8,100,crect.CenterPoint().x+crect.Width()/8,crect.bottom-100),this,0);
		g_wndMusicInfo->OnClose();

		wndCartwall->Create(NULL,NULL,WS_VISIBLE|WS_POPUP,CRect(0,0,(crect.right-300)/4,crect.bottom-163),this);
		wndCartwall->MoveWindow(10000,0,0,0);
		g_wndCartwall = (CWnd *)wndCartwall;

		g_wndAired->Create(NULL,NULL,WS_VISIBLE|WS_POPUP,CRect(0,0,(crect.right-300)/4,crect.bottom-163),this);
		g_wndAired->MoveWindow(10000,0,0,0);

		m_wndContainer1 = new CContainerWnd();
		m_wndContainer1->Create(NULL,WS_VISIBLE,CRect(150,0,150+(crect.right-300)/4,crect.bottom),this);
		m_wndContainer1->m_ctrlSelection->SetCurSel(0);
		m_wndContainer1->OnSelChange();

		m_wndContainer2 = new CContainerWnd();
		m_wndContainer2->Create(NULL,WS_VISIBLE,CRect(150+(crect.right-300)/4,0,crect.right/2-1,crect.bottom),this);
		m_wndContainer2->m_ctrlSelection->SetCurSel(1);
		m_wndContainer2->OnSelChange();

		m_wndContainer3 = new CContainerWnd();
		m_wndContainer3->Create(NULL,WS_VISIBLE,CRect(crect.right/2,0,150+(int)((crect.right-300)*0.75f)-1,crect.bottom),this);
		m_wndContainer3->m_ctrlSelection->SetCurSel(2);
		m_wndContainer3->OnSelChange();

		m_wndContainer4 = new CContainerWnd();
		m_wndContainer4->Create(NULL,WS_VISIBLE,CRect((int)((crect.right-300)*0.75f)+150,0,crect.right-150,crect.bottom),this);
		m_wndContainer4->m_ctrlSelection->SetCurSel(9);
		//m_wndContainer4->OnSelChange();
	}
	else
	{
		g_wndPFL->CreateEx(WS_EX_TOOLWINDOW|WS_EX_TOPMOST,NULL,"Digital Broadcaster 2006 - PFL",WS_SYSMENU|WS_MINIMIZEBOX|WS_POPUP|WS_VISIBLE|WS_CAPTION,CRect(0,0,crect.right/2,115),this,0);
		g_wndPFL->OnClose();

		g_wndMusicInfo->CreateEx(WS_EX_TOOLWINDOW|WS_EX_TOPMOST,NULL,"Digital Broadcaster 2006 - Info",WS_SYSMENU|WS_MINIMIZEBOX|WS_POPUP|WS_VISIBLE|WS_CAPTION,CRect(crect.CenterPoint().x-crect.Width()/4,100,crect.CenterPoint().x+crect.Width()/4,crect.bottom-100),this,0);
		g_wndMusicInfo->OnClose();

		wndCartwall->Create(NULL,NULL,WS_VISIBLE|WS_POPUP,CRect(0,0,crect.right/2-75,crect.bottom-63),this);
		wndCartwall->MoveWindow(10000,0,0,0);
		g_wndCartwall = (CWnd *)wndCartwall;

		g_wndAired->Create(NULL,NULL,WS_VISIBLE|WS_POPUP,CRect(0,0,crect.right/2-75,crect.bottom-53),this);
		g_wndAired->MoveWindow(10000,0,0,0);

		
		m_wndContainer1 = new CContainerWnd();
		m_wndContainer1->Create(NULL,WS_VISIBLE,CRect(0,0,crect.right/2-75,crect.bottom),this);
		m_wndContainer1->m_ctrlSelection->SetCurSel(0);
		m_wndContainer1->OnSelChange();

		m_wndContainer2 = new CContainerWnd();
		m_wndContainer2->Create(NULL,WS_VISIBLE,CRect(crect.right/2-75,0,crect.right-150,crect.bottom),this);
		m_wndContainer2->m_ctrlSelection->SetCurSel(9);
		m_wndContainer2->OnSelChange();

		m_wndContainer3=NULL;
		m_wndContainer4=NULL;
	}

	g_wndLogOnBack->BringWindowToTop();
	if( g_bFastStart )
	{
		//AfxMessageBox("FastStart");
		SetTimer(IDT_STARTUP,5000,NULL);
	}
	else
		SetTimer(IDT_STARTUP,15000,NULL);
	SetTimer(IDT_HASP,15000,NULL);
	OnTimer(IDT_HASP);

	// Log Item -----------------------------------------------------------------------
	typeLogItem *lpLog=new typeLogItem;
	lpLog->wType = 0;
	lpLog->lID = 0;
	lpLog->lTraffic = 0;
	strcpy(lpLog->strName,"--> Session Started");
	g_wndAired->LogItem(lpLog);
	// --------------------------------------------------------------------------------

	return 0;
}

BOOL COnAirWnd::GetWindowConfig()
{
	return TRUE;
}

void COnAirWnd::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
}

void COnAirWnd::OnSysCommand(UINT nID, LPARAM lParam) 
{
	CFrameWnd::OnSysCommand(nID,lParam);
}

void COnAirWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	Graphics graph(dc);
	
	graph.Clear(Color(255,0,0,128));
}

void COnAirWnd::OnTimer(UINT nIDEvent) 
{
	if( nIDEvent==IDT_STARTUP )
	{
		if( (m_nStartupStep==0) && (g_wAutomationMode == AUTOMATION_FULLAUTO) )
			((CLineUpWnd *)g_wndLineUp)->GetStartupSchedule();
		if( (m_nStartupStep==1) && (g_wAutomationMode == AUTOMATION_FULLAUTO) )
			((CLineUpWnd *)g_wndLineUp)->OnSpacePressed();
		if( m_nStartupStep==2 )
			KillTimer(IDT_STARTUP);
		m_nStartupStep++;
		return;
	}

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
			g_bHaspOK=FALSE;
			g_nHaspCount--;
			if( g_nHaspCount<1 )
			{
				AfxMessageBox(IDS_HASPERROR,MB_APPLMODAL);
				PostQuitMessage(0);
			}
		}
		else
		{
			g_bHaspOK=TRUE;
			g_wndStatus->Invalidate();
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

void COnAirWnd::OnSysColorChange() 
{
	CWnd::OnSysColorChange();

	g_colorCaptionText.SetFromCOLORREF(::GetSysColor(COLOR_CAPTIONTEXT) );
	
	Invalidate();
}

BOOL COnAirWnd::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	const char* pszClassName = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW,NULL );

	return CWnd::CreateEx(	0,
							NULL,
							lpszWindowName,
							dwStyle,
							rect,
							pParentWnd,
							0);
}

BOOL COnAirWnd::OnEraseBkgnd(CDC* pDC) 
{
	
	return TRUE;
}

void COnAirWnd::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( !CheckKey(nChar) )
		CWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}

void COnAirWnd::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( !CheckKey(nChar) )
		CWnd::OnSysKeyUp(nChar, nRepCnt, nFlags);
}

void COnAirWnd::CreateToolBackground(int W, int H)
{
	if( g_bmToolBackground )
		delete g_bmToolBackground;

	CClientDC	dc(this);
	
	CDC	tempDC;
	tempDC.CreateCompatibleDC(&dc);

	g_bmToolBackground = new CBitmap();
	g_bmToolBackground->CreateCompatibleBitmap(&dc,W,H);

	tempDC.SelectObject(g_bmToolBackground);
	
	Graphics	graph(tempDC);

	REAL				iWidth = (REAL)W,
						iHeight = (REAL)H;
	int					iCount=4;
	Color				color;
	LinearGradientBrush brTop(PointF(0,0),PointF(0,20),Color(200,255,255,255),Color(0,255,255,255)),
						brBottom(PointF(0,0),PointF(0,20),Color(0,255,255,255),Color(200,255,255,255));

	color.SetFromCOLORREF(GetSysColor(COLOR_3DFACE));
	graph.FillRectangle(&SolidBrush(color),RectF(0.0f,0.0f,iWidth,iHeight));
	graph.FillRectangle(&brTop,RectF(0.0f,0.0f,iWidth,20));
	graph.FillRectangle(&brBottom,RectF(0.0f,iHeight-20,iWidth,20));
}

LRESULT COnAirWnd::OnUserLogOff(WPARAM,LPARAM)
{
	m_wndContainer1->EnableWindow(FALSE);
	m_wndContainer2->EnableWindow(FALSE);

	if( m_wndContainer3!=NULL )
		m_wndContainer3->EnableWindow(FALSE);

	if( m_wndContainer4!=NULL )
		m_wndContainer4->EnableWindow(FALSE);

	return 0;
}
