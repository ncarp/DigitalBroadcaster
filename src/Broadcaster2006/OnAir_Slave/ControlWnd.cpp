// ControlWnd.cpp : implementation file
//

#include "stdafx.h"
#include "OnAir_Slave.h"
#include <gdiplus.h>
using namespace Gdiplus;

#include "ControlWnd.h"
#include ".\controlwnd.h"


// CControlWnd

IMPLEMENT_DYNCREATE(CControlWnd, CFrameWnd)

CControlWnd::CControlWnd()
{
}

CControlWnd::~CControlWnd()
{
}


BEGIN_MESSAGE_MAP(CControlWnd, CFrameWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_NCPAINT()
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()


// CControlWnd message handlers

void CControlWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect	rect;

	GetClientRect(&rect);
	dc.FillRect(&rect,&CBrush(GetSysColor(COLOR_INACTIVECAPTION)));
}

int CControlWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect	rect;

	GetWindowRect(&rect);
	m_wndLogo.Create(NULL,WS_VISIBLE,CRect(0,0,425,99),this,133);
	m_wndClock.Create(NULL,WS_VISIBLE,CRect(0,100,rect.right,200),this);
	m_wndList.Create(WS_VISIBLE|LVS_REPORT,CRect(2,205,rect.right-6,rect.bottom-7),this,1);

	m_wndList.GetClientRect(&rect);
	m_wndList.InsertColumn(0,"Data",LVCFMT_LEFT,65);
	m_wndList.InsertColumn(1,"Hora",LVCFMT_LEFT,60);
	m_wndList.InsertColumn(2,"Origem",LVCFMT_LEFT,60);
	m_wndList.InsertColumn(3,"Mensagem",LVCFMT_LEFT,rect.Width()-185);

	COleDateTime	dt = COleDateTime::GetCurrentTime();
	CString			text;

	text.Format("%4d-%2d-%2d",dt.GetYear(),dt.GetMonth(),dt.GetDay());
	text.Replace(" ","0");
	m_wndList.InsertItem(0,text,0);

	text.Format("%2d:%2d:%2d",dt.GetHour(),dt.GetMinute(),dt.GetSecond());
	text.Replace(" ","0");
	m_wndList.SetItemText(0,1,text);
	m_wndList.SetItemText(0,2,"System");
	m_wndList.SetItemText(0,3,"Inicio do sistema");
	return 0;
}

void CControlWnd::OnNcPaint()
{
	CWindowDC	dc( this );
	CRect		rect;

	GetWindowRect(&rect);
	rect.OffsetRect(0-rect.left,0-rect.top);

	dc.Draw3dRect(&rect,GetSysColor(COLOR_ACTIVECAPTION),GetSysColor(COLOR_ACTIVECAPTION)); 
	rect.DeflateRect(1,1,1,1);
	dc.Draw3dRect(&rect,GetSysColor(COLOR_INACTIVECAPTION),GetSysColor(COLOR_INACTIVECAPTION)); 
}

void CControlWnd::OnSysCommand(UINT nID, LPARAM lParam)
{
	if( nID==SC_CLOSE )
	{
		if( AfxMessageBox("Tem a certeza que pretende sair da aplicação?",MB_YESNO)==IDYES )
			PostQuitMessage(0);
	}
	else
		CFrameWnd::OnSysCommand(nID, lParam);
}
