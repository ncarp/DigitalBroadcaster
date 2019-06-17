// LogoWnd.cpp : implementation file
//

#include "stdafx.h"

#include <gdiplus.h>
using namespace Gdiplus;

#include "ExternalObjects.h"
#include "OnAirUtils.h"
#include "OnAir.h"
#include "LogoWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLogoWnd

CLogoWnd::CLogoWnd()
{
	m_nStep=500;
}

CLogoWnd::~CLogoWnd()
{
}


BEGIN_MESSAGE_MAP(CLogoWnd, CStatic)
	//{{AFX_MSG_MAP(CLogoWnd)
	ON_WM_CREATE()
	ON_WM_KEYUP()
	ON_WM_SYSKEYUP()
	ON_WM_SYSCOLORCHANGE()
	ON_WM_PAINT()
	ON_WM_SYSKEYDOWN()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogoWnd message handlers

int CLogoWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	//////////////////////////////////////////////////////////////////////////
	// Create the background bitmpa 
	CRect	rect;
	GetClientRect(&rect);

	CClientDC	dc(this);
	Graphics	graph(dc);

	m_bmBack = ::new Bitmap(rect.Width(),rect.Height(),&graph);
	OnSysColorChange();
	//////////////////////////////////////////////////////////////////////////

	SetTimer(1001,10,NULL);

	return 0;
}

void CLogoWnd::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( !CheckKey( nChar ) )
		CStatic::OnKeyUp(nChar, nRepCnt, nFlags);
}


void CLogoWnd::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( !CheckKey( nChar ) )
		CStatic::OnSysKeyUp(nChar, nRepCnt, nFlags);
}

void CLogoWnd::OnSysColorChange() 
{
	CStatic::OnSysColorChange();
	
	CStatic::OnSysColorChange();
	
	REAL				iWidth = (REAL)m_bmBack->GetWidth(),
						iHeight = (REAL)m_bmBack->GetHeight();
	int					iCount=4;

	COLORREF			crefCaption1 =::GetSysColor(COLOR_INACTIVECAPTION),
						crefCaption2 =::GetSysColor(COLOR_GRADIENTINACTIVECAPTION); 
	Color				colorBack[4];
						
	PointF				pointsBack[] = {	PointF(0.0f,0.0f), 
											PointF(0.0f,iHeight), 
											PointF(iWidth,iHeight),
											PointF(iWidth,0.0f) },

						pointsLight[] = {	PointF(0.0f,0.0f),
											PointF(0.0f,iHeight), 
											PointF(iWidth*0.2f,iHeight*0.2f), 
											PointF(iWidth,0.0f) 
										},
						pointsDark[] = {	PointF(0.0f,iHeight), 
											PointF(iWidth,iHeight),
											PointF(iWidth,0.0f), 
											PointF( iWidth*0.8f,iHeight*0.8f) 
										};
	GraphicsPath		pathBack,
						pathLight,
						pathDark;

	Bitmap				bmLogo( ((AfxGetApp())->m_hInstance),(WCHAR *)MAKEINTRESOURCE(IDB_LOGO));
	
	pathBack.AddLines(pointsBack,4);
	pathLight.AddLines(pointsLight,4);
	pathDark.AddLines(pointsDark,4);

	PathGradientBrush	brushBack(&pathBack),
						brushLight(&pathLight),
						brushDark(&pathDark);
	
	colorBack[0].SetFromCOLORREF(crefCaption2);
	colorBack[1].SetFromCOLORREF(crefCaption2);
	colorBack[2].SetFromCOLORREF(crefCaption1);
	colorBack[3].SetFromCOLORREF(crefCaption2);

	brushBack.SetSurroundColors(colorBack,&iCount);
	brushBack.SetCenterColor(colorBack[0]);

	brushLight.SetSurroundColors(g_colorLight,&iCount);
	brushLight.SetCenterColor(g_colorLight[0]);
	brushLight.SetCenterPoint(pointsLight[0]);

	brushDark.SetSurroundColors(g_colorDark,&iCount);
	brushDark.SetCenterColor(g_colorDark[1]);
	brushDark.SetCenterPoint(pointsDark[1]);
	brushDark.SetGammaCorrection(TRUE);

	SolidBrush			brushWhite( Color(255,255,255,255) );
	Graphics	graph(m_bmBack);

//	graph.FillPath(&brushBack,&pathBack);
	graph.DrawImage(&bmLogo,0,0);
	graph.FillPath(&brushLight,&pathLight);
	graph.FillPath(&brushDark,&pathDark);

	m_bmTop = ::new Bitmap( ((AfxGetApp())->m_hInstance),(WCHAR *)MAKEINTRESOURCE(IDB_LOGO_TOP));
	m_bmRadio = ::new Bitmap( ((AfxGetApp())->m_hInstance),(WCHAR *)MAKEINTRESOURCE(IDB_LOGO_RADIO));
}

void CLogoWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	Graphics graph(dc);
	ImageAttributes imageAtt;
	ColorMap cMap;
	cMap.oldColor = Color(255, 255,0,255); 
	cMap.newColor = Color(  0, 255,255,255); 
	imageAtt.SetRemapTable(1, &cMap,ColorAdjustTypeDefault);

	graph.DrawImage(m_bmBack,0,0);
	graph.DrawImage(m_bmTop,Rect(0,0,150,150),0,0,150,150,UnitPixel,&imageAtt);
}

void CLogoWnd::OnLButtonDblClk(UINT nFlags, CPoint point) 
{

}

void CLogoWnd::OnTimer(UINT_PTR nIDEvent)
{
	m_nStep++;

	if( m_nStep<=1000 )
		return;
	else if( m_nStep<=1100 )
	{
		Bitmap bm(150,100);
		Graphics graph(&bm);

		ImageAttributes imageAtt;
		ColorMap cMap;
		cMap.oldColor = Color(255, 255,0,255); 
		cMap.newColor = Color(  0, 255,255,255); 
		imageAtt.SetRemapTable(1, &cMap,ColorAdjustTypeDefault);
	
		ImageAttributes imageAtt2;
		ColorMap cMap2;
		cMap2.oldColor = Color(255, 0,0,0); 
		cMap2.newColor = Color(  0, 255,255,255); 
		imageAtt2.SetRemapTable(1, &cMap2,ColorAdjustTypeDefault);

		graph.DrawImage(m_bmBack,0,0);
		graph.DrawImage(m_bmRadio,Rect(0,0,150,m_nStep-1000),0,0,150,100,UnitPixel,&imageAtt2);
		graph.DrawImage(m_bmTop,Rect(0,m_nStep-1000,150,1100-m_nStep),0,0,150,100,UnitPixel,&imageAtt);

		CClientDC dc(this);
		Graphics grDC(dc);
		grDC.DrawImage(&bm,0,0);
	}
	else if( m_nStep<=2100 )
		return;
	else if( m_nStep<=2200 )
	{
		Bitmap bm(150,100);
		Graphics graph(&bm);

		ImageAttributes imageAtt;
		ColorMap cMap;
		cMap.oldColor = Color(255, 255,0,255); 
		cMap.newColor = Color(  0, 255,255,255); 
		imageAtt.SetRemapTable(1, &cMap,ColorAdjustTypeDefault);
	
		ImageAttributes imageAtt2;
		ColorMap cMap2;
		cMap2.oldColor = Color(255, 0,0,0); 
		cMap2.newColor = Color(  0, 255,255,255); 
		imageAtt2.SetRemapTable(1, &cMap2,ColorAdjustTypeDefault);

		graph.DrawImage(m_bmBack,0,0);
		graph.DrawImage(m_bmTop,Rect(0,0,150,m_nStep-2100),0,0,150,100,UnitPixel,&imageAtt);
		graph.DrawImage(m_bmRadio,Rect(0,m_nStep-2100,150,2200-m_nStep),0,0,150,100,UnitPixel,&imageAtt2);

		CClientDC dc(this);
		Graphics grDC(dc);
		grDC.DrawImage(&bm,0,0);
	}
	else
		m_nStep=0;

	CStatic::OnTimer(nIDEvent);
}
