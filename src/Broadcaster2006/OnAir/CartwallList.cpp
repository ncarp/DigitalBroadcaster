// CartwallList.cpp : implementation file
//

#include "stdafx.h"
#include "OnAir.h"
#include "CartwallList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCartwallList

CCartwallList::CCartwallList()
{
	m_nPos=0;
}

CCartwallList::~CCartwallList()
{
}


BEGIN_MESSAGE_MAP(CCartwallList, CWnd)
	//{{AFX_MSG_MAP(CCartwallList)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCartwallList message handlers

int CCartwallList::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect	rect;
	long	lHeight;
	long	lCapacity;
	
	GetClientRect(&rect);

	lHeight=rect.bottom-rect.top;
	lCapacity=lHeight/53;

	SetScrollRange(SB_VERT,0,2650-rect.Height());

	rect.DeflateRect(2,2,2,2);
	rect.bottom=rect.top+52;

	for( int i=0; i<50; i++ )
	{
		m_Carts[i] = new CCart();
		m_Carts[i]->Create(NULL,SS_NOTIFY|WS_VISIBLE,rect,this);
		m_Carts[i]->m_wCartNumber=i+1;
		rect.OffsetRect(0,53);
	}	
	return 0;
}

void CCartwallList::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rect;
	GetClientRect(&rect);

	dc.FillRect(&rect,&CBrush(GetSysColor(COLOR_3DFACE)));
}

void CCartwallList::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	switch( nSBCode )
	{
	case SB_THUMBPOSITION:
	case SB_THUMBTRACK: 
//		wndCart[0]->MoveWindow(0,-100,100,100);
		SetScrollPos(SB_VERT,nPos);
		ScrollWindow(0,m_nPos-nPos);
		m_nPos=nPos;
//		SetCartPos();
		break;
	}	
}
