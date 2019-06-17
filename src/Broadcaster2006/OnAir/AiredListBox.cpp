// AiredListBox.cpp : implementation file
//

#include "stdafx.h"
#include "onair.h"
#include "AiredListBox.h"
#include "OnAirDefines.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAiredListBox

CAiredListBox::CAiredListBox()
{
	m_bIsRefreshing = FALSE;
}

CAiredListBox::~CAiredListBox()
{
}

BEGIN_MESSAGE_MAP(CAiredListBox, CLineUpListBox)
	//{{AFX_MSG_MAP(CAiredListBox)
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(UM_CANDROP,OnCanDrop)
	ON_MESSAGE(UM_DROP,OnDrop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAiredListBox message handlers

void CAiredListBox::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CListBox::OnMouseMove(nFlags, point);
}

LRESULT CAiredListBox::OnCanDrop( WPARAM,LPARAM )
{
	return 0;
}

LRESULT CAiredListBox::OnDrop( WPARAM,LPARAM )
{
	return 0;
}