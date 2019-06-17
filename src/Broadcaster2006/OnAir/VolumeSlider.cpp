// VolumeSlider.cpp : implementation file
//

#include "stdafx.h"
#include <gdiplus.h>
using namespace Gdiplus;

#include "ExternalObjects.h"
#include "OnAirUtils.h"
#include "OnAir.h"
#include "VolumeSlider.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVolumeSlider

CVolumeSlider::CVolumeSlider()
{
	m_bDragging=FALSE;
	m_bmBack=NULL;
	m_nPrevPos=19;
	m_lCurVolume=-3000;
}

CVolumeSlider::~CVolumeSlider()
{
	::delete m_bmBack;
	::delete m_bmThumb;
}


BEGIN_MESSAGE_MAP(CVolumeSlider, CStatic)
	//{{AFX_MSG_MAP(CVolumeSlider)
	ON_WM_PAINT()
	ON_WM_KEYUP()
	ON_WM_SYSKEYUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVolumeSlider message handlers

int CVolumeSlider::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_bmThumb=::new Bitmap(AfxGetInstanceHandle(),(WCHAR*)MAKEINTRESOURCE(IDB_THUMB_VOL));
	return 0;
}

void CVolumeSlider::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect	rect;
	GetClientRect(&rect);

	dc.Draw3dRect(&rect,RGB(255,255,255),RGB(128,128,128));
	rect.DeflateRect(1,1,1,1);
	dc.Draw3dRect(&rect,RGB(128,128,128),RGB(255,255,255));

	Graphics	graph(dc);
	graph.DrawImage(m_bmBack,2,2);
	graph.DrawImage(m_bmThumb,m_nPrevPos-17,3);
}

void CVolumeSlider::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( !CheckKey(nChar) )
		CStatic::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CVolumeSlider::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( !CheckKey(nChar) )
		CStatic::OnSysKeyUp(nChar, nRepCnt, nFlags);
}

void CVolumeSlider::OnMouseMove(UINT nFlags, CPoint point) 
{
	if( !m_bDragging )
		return;

	CClientDC	dc(this);
	Graphics	graph(dc);
	int			X=point.x;
	
	if( X<20 )
		X=20;
	if( X>m_rect.Width()-20 )
		X=m_rect.Width()-20;

	if( X!=m_nPrevPos )
	{
		graph.FillRectangle(&SolidBrush(g_colorFace),m_nPrevPos-17,3,35,17);
		graph.DrawImage(m_bmThumb,X-17,3);
		m_nPrevPos=X;

		float	newVolPerc=(float)(X-20)/(float)(m_rect.Width()-40);
		float	newVol=3000*newVolPerc-3000.0f;
		GetParent()->SendMessage(UM_VOLUMECHANGE,(DWORD)newVol);
	}
}

void CVolumeSlider::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_bDragging=TRUE;
	SetCapture();
	OnMouseMove(nFlags,point);
}

void CVolumeSlider::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_bDragging=FALSE;
	ReleaseCapture();
}


void CVolumeSlider::OnSize(UINT nType, int cx, int cy) 
{
	CStatic::OnSize(nType, cx, cy);
	
		// Get the window metrics
	GetClientRect(&m_rect);

	// Creates the backgroung
	if( m_bmBack!=NULL )
		::delete m_bmBack;

	m_bmBack = ::new Bitmap(m_rect.Width()-4,m_rect.Height()-4);
	
	LinearGradientBrush	brYellow(PointF(m_rect.Width()*0.5f,0.0f),	// Starting point
								 PointF(m_rect.Width()*0.8f,0.0f),		// Ending point,
								 g_colorGreen,
								 Color::Yellow );

	LinearGradientBrush brRed(	 PointF(m_rect.Width()*0.8f,0.0f),	// Starting point
								 PointF(m_rect.Width()*1.0f,0.0f),		// Ending point,
								 Color::Yellow,
								 g_colorRed );

	Graphics	graph(m_bmBack);
	graph.Clear(g_colorFace);
	graph.FillRectangle(&SolidBrush(g_colorGreen),
						RectF(0,0,m_rect.Width()*0.5f,2.0f) );
	graph.FillRectangle(&brYellow,
						RectF(m_rect.Width()*0.5f,0.0f,m_rect.Width()*0.3f,2.0f) );
	graph.FillRectangle(&brRed,
						RectF(m_rect.Width()*0.8f,0.0f,m_rect.Width()*0.2f,2.0f) );

	graph.FillRectangle(&SolidBrush(g_colorGreen),
						RectF(0,(REAL)m_rect.Height()-6,m_rect.Width()*0.5f,2.0f) );
	graph.FillRectangle(&brYellow,
						RectF(m_rect.Width()*0.5f,(REAL)m_rect.Height()-6,m_rect.Width()*0.3f,(REAL)m_rect.Height()-2) );
	graph.FillRectangle(&brRed,
						RectF(m_rect.Width()*0.8f,(REAL)m_rect.Height()-6,m_rect.Width()*0.2f,(REAL)m_rect.Height()-2) );
//	graph.FillRectangle(&SolidBrush(Color(128,255,255,255)),
//						Rect(0,0,m_rect.Width(),m_rect.Height()) );
	
}


void CVolumeSlider::SetVolume(long Vol)
{
	if( m_lCurVolume!=Vol )
	{
		float fTemp=3000.0f+Vol;

		fTemp=fTemp/3000*(float)(m_rect.Width()-40)+20.0f;

		int			X=(int)fTemp;
	
		if( X!=m_nPrevPos )
		{
			CClientDC	dc(this);
			Graphics	graph(dc);

			graph.FillRectangle(&SolidBrush(g_colorFace),m_nPrevPos-17,3,35,17);
			graph.DrawImage(m_bmThumb,X-17,3);
			m_nPrevPos=X;
			
		}
		m_lCurVolume=Vol;
	}
}
