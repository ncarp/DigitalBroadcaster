// SplitterLogo.cpp : implementation file
//

#include "stdafx.h"
#include "OnAir_Slave.h"
#include "SplitterLogo.h"
#include ".\splitterlogo.h"
#include "..\onair\externalobjects.h"

// CSplitterLogo

IMPLEMENT_DYNAMIC(CSplitterLogo, CStatic)
CSplitterLogo::CSplitterLogo()
{
}

CSplitterLogo::~CSplitterLogo()
{
}


BEGIN_MESSAGE_MAP(CSplitterLogo, CStatic)
	ON_WM_PAINT()
	ON_WM_SYSCOLORCHANGE()
	ON_WM_CREATE()
END_MESSAGE_MAP()



// CSplitterLogo message handlers


void CSplitterLogo::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	Graphics graph(dc);
	
	graph.DrawImage(m_bmBack,0,0);
}

void CSplitterLogo::OnSysColorChange() 
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
//	graph.FillPath(&brushLight,&pathLight);
//	graph.FillPath(&brushDark,&pathDark);
}

int CSplitterLogo::OnCreate(LPCREATESTRUCT lpCreateStruct)
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


	return 0;
}
