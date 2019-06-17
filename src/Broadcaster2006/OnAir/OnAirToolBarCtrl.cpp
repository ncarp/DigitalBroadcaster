// OnAirToolBarCtrl.cpp : implementation file
//

#include "stdafx.h"

#include <gdiplus.h>
using namespace Gdiplus;

#include "ExternalObjects.h"
#include "..\include\utils.h"

#include "OnAir.h"
#include "OnAirToolBarCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COnAirToolBarCtrl

COnAirToolBarCtrl::COnAirToolBarCtrl()
{
}

COnAirToolBarCtrl::~COnAirToolBarCtrl()
{
}


BEGIN_MESSAGE_MAP(COnAirToolBarCtrl, CToolBarCtrl)
	//{{AFX_MSG_MAP(COnAirToolBarCtrl)
	ON_WM_PAINT()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COnAirToolBarCtrl message handlers

void COnAirToolBarCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	Graphics	graph(dc);

	// Do not call CToolBarCtrl::OnPaint() for painting messages
}

void COnAirToolBarCtrl::OnSize(UINT nType, int cx, int cy) 
{
	CToolBarCtrl::OnSize(nType, cx, cy);
	
		
}
