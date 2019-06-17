// OnAirContainerWnd.cpp : implementation file
//

#include "stdafx.h"
#include "OnAir_Slave.h"
#include "OnAirContainerWnd.h"
#include ".\onaircontainerwnd.h"


// COnAirContainerWnd

IMPLEMENT_DYNCREATE(COnAirContainerWnd, CFrameWnd)

COnAirContainerWnd::COnAirContainerWnd()
{
}

COnAirContainerWnd::~COnAirContainerWnd()
{
}


BEGIN_MESSAGE_MAP(COnAirContainerWnd, CFrameWnd)
	ON_WM_NCPAINT()
	ON_WM_PAINT()
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()


// COnAirContainerWnd message handlers

void COnAirContainerWnd::OnNcPaint()
{
	CWindowDC	dc( this );
	CRect		rect;
	

	GetWindowRect(&rect);
	rect.OffsetRect(0-rect.left,0-rect.top);

	dc.Draw3dRect(&rect,GetSysColor(COLOR_ACTIVECAPTION),GetSysColor(COLOR_ACTIVECAPTION)); 
	rect.DeflateRect(1,1,1,1);
	dc.Draw3dRect(&rect,GetSysColor(COLOR_INACTIVECAPTION),GetSysColor(COLOR_INACTIVECAPTION)); 
}

void COnAirContainerWnd::OnPaint()
{
	CPaintDC	dc(this); // device context for painting
	CRect		rect;

	GetClientRect(&rect);
	dc.FillRect(&rect,&CBrush(GetSysColor(COLOR_INACTIVECAPTION)));
}

void COnAirContainerWnd::OnSysCommand(UINT nID, LPARAM lParam)
{
	if( nID!=SC_CLOSE )
		CFrameWnd::OnSysCommand(nID, lParam);
}
