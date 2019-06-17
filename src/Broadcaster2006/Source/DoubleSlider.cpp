// DoubleSlider.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\DoubleSlider.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDoubleSlider

CDoubleSlider::CDoubleSlider()
{
	CursorArrow=LoadCursor(NULL,IDC_ARROW);
	CursorSize=LoadCursor(NULL,IDC_SIZEWE);
	m_fRight=1.0f;
	m_fLeft=0.0f;
}

CDoubleSlider::~CDoubleSlider()
{
	
}


BEGIN_MESSAGE_MAP(CDoubleSlider, CStatic)
	//{{AFX_MSG_MAP(CDoubleSlider)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDoubleSlider message handlers

void CDoubleSlider::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rect,
			rect2;
	GetClientRect(&rect);

	dc.FillRect(rect,&CBrush(GetSysColor(COLOR_3DFACE)));
	dc.Draw3dRect(rect,GetSysColor(COLOR_3DSHADOW),GetSysColor(COLOR_3DHIGHLIGHT));

	rect.DeflateRect(1,1,1,1);
	dc.Draw3dRect(rect,GetSysColor(COLOR_3DDKSHADOW),GetSysColor(COLOR_3DLIGHT));
	
	rect2=rect;
	rect2.DeflateRect(1,3,1,3);
	rect2.right=m_LeftPos;
	dc.FillRect(rect2,&CBrush(GetSysColor(COLOR_3DSHADOW)));

	rect2=rect;
	rect2.DeflateRect(1,3,1,3);
	rect2.left=m_RightPos;
	dc.FillRect(rect2,&CBrush(RGB(150,150,150)));
}

int CDoubleSlider::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rect;
	GetClientRect(&rect);

	m_LeftLimit=m_LeftPos=rect.left+4;
	m_RightLimit=m_RightPos=rect.right-4;

	bLeftDrag=FALSE;
	bRightDrag=FALSE;

	return 0;
}

void CDoubleSlider::OnMouseMove(UINT nFlags, CPoint point) 
{
	if( (bLeftDrag) && (point.x>=m_LeftLimit) && (point.x<m_RightPos) )
	{
		m_LeftPos=point.x;
		Invalidate();
		m_fLeft = (float)(m_LeftPos-m_LeftLimit) / (float)(m_RightLimit-m_LeftLimit);
		GetParent()->SendMessage(UM_DOUBLECHANGE,1,GetDlgCtrlID());
	}

	if( (bRightDrag) && (point.x<=m_RightLimit) && (point.x>m_LeftPos) )
	{
		m_RightPos=point.x;
		Invalidate();
		m_fRight = (float)(m_RightPos-m_LeftLimit) / (float)(m_RightLimit-m_LeftLimit);
		GetParent()->SendMessage(UM_DOUBLECHANGE,0,GetDlgCtrlID());
	}

	if( (point.x>=m_LeftPos-2) && (point.x<=m_LeftPos+2) ||
		(point.x>=m_RightPos-2) && (point.x<=m_RightPos+2) )
		SetClassLong(m_hWnd,GCL_HCURSOR,(LONG)CursorSize);
	else
		SetClassLong(m_hWnd,GCL_HCURSOR,(LONG)CursorArrow);
	
}

void CDoubleSlider::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if( (point.x>=m_LeftPos-2) && (point.x<=m_LeftPos+2) )
	{
		bLeftDrag=TRUE;
		SetCapture();
	}

	if( (point.x>=m_RightPos-2) && (point.x<=m_RightPos+2) )
	{
		bRightDrag=TRUE;
		SetCapture();
	}
}

void CDoubleSlider::OnLButtonUp(UINT nFlags, CPoint point) 
{
	ReleaseCapture();
	bLeftDrag=bRightDrag=FALSE;
	
	CStatic::OnLButtonUp(nFlags, point);
}
