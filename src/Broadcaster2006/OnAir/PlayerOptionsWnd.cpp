// PlayerOptionsWnd.cpp : implementation file
//

#include "stdafx.h"
#include "OnAir.h"
#include "PlayerOptionsWnd.h"
#include "OnAirDefines.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPlayerOptionsWnd

#define ID_PAUSE	1001
#define ID_LOOP		1002

CPlayerOptionsWnd::CPlayerOptionsWnd()
{
}

CPlayerOptionsWnd::~CPlayerOptionsWnd()
{
}


BEGIN_MESSAGE_MAP(CPlayerOptionsWnd, CStatic)
	//{{AFX_MSG_MAP(CPlayerOptionsWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND( ID_PAUSE,OnPause  )
	ON_COMMAND( ID_LOOP,OnLoop )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlayerOptionsWnd message handlers

void CPlayerOptionsWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect	rect;

	GetClientRect(&rect);
	dc.Draw3dRect(rect,RGB(255,255,255),RGB(128,128,128));
}

int CPlayerOptionsWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_pPause = new CPlayerButton();
	m_pPause->Create("",WS_VISIBLE|BS_OWNERDRAW,CRect(0,0,0,0),this,ID_PAUSE);
	m_pPause->SetImageList(20,20,0,3);
	m_pPause->AddImage(IDB_PAUSE_OFF);
	m_pPause->AddImage(IDB_PAUSE_ON);
	
	m_pLoop = new CPlayerButton();
	m_pLoop->Create("",WS_VISIBLE|BS_OWNERDRAW,CRect(0,0,0,0),this,ID_LOOP);
	m_pLoop->SetImageList(25,20,0,3);
	m_pLoop->AddImage(IDB_LOOP_OFF);
	m_pLoop->AddImage(IDB_LOOP_ON);

	return 0;
}

void CPlayerOptionsWnd::OnSize(UINT nType, int cx, int cy) 
{
	CStatic::OnSize(nType, cx, cy);
	
	m_pPause->MoveWindow(CRect(cx/2,1,cx-2,cy-2));
	m_pLoop->MoveWindow(CRect(1,1,cx/2,cy-2));
}

void CPlayerOptionsWnd::OnPause()
{
	m_pPause->m_bLight=!m_pPause->m_bLight;
	
	if( !GetParent()->SendMessage(UM_SETPAUSE) )
		m_pPause->m_bLight=FALSE;

	m_pPause->Invalidate();
}							 

void CPlayerOptionsWnd::OnLoop()
{
	m_pLoop->m_bLight=!m_pLoop->m_bLight;
	m_pLoop->Invalidate();
	GetParent()->SendMessage(UM_SETLOOP);
}

void CPlayerOptionsWnd::Reset()
{
	m_pLoop->m_bLight=FALSE;
	m_pPause->m_bLight=FALSE;

	m_pLoop->Invalidate();
	m_pPause->Invalidate();
}