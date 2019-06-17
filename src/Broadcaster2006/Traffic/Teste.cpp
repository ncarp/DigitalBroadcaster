// Teste.cpp : implementation file
//

#include "stdafx.h"
#include "Traffic.h"
#include "Teste.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTeste

CTeste::CTeste()
{
}

CTeste::~CTeste()
{
}


BEGIN_MESSAGE_MAP(CTeste, CStatic)
	//{{AFX_MSG_MAP(CTeste)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTeste message handlers

void CTeste::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rect;
	GetClientRect(&rect);
	dc.FillRect(rect,&CBrush(RGB(255,0,0)));
	
	// Do not call CStatic::OnPaint() for painting messages
}

