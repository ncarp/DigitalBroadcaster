// GenericInfoWnd.cpp : implementation file
//

#include "stdafx.h"
#include <gdiplus.h>
using namespace Gdiplus;

#include "ExternalObjects.h"
#include "OnAirUtils.h"

#include "OnAir.h"
#include "GenericInfoWnd.h"
#include "..\include\Utils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGenericInfoWnd

CGenericInfoWnd::CGenericInfoWnd()
{
}

CGenericInfoWnd::~CGenericInfoWnd()
{
	delete m_bmBack;
	delete m_bmCrono;
}


BEGIN_MESSAGE_MAP(CGenericInfoWnd, CStatic)
	//{{AFX_MSG_MAP(CGenericInfoWnd)
	ON_WM_CREATE()
	ON_WM_SYSCOLORCHANGE()
	ON_WM_PAINT()
	ON_WM_SYSKEYUP()
	ON_WM_KEYUP()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGenericInfoWnd message handlers

int CGenericInfoWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	//////////////////////////////////////////////////////////////////////////
	// Create the background bitmpa 
	CRect	rect;
	GetClientRect(&rect);

	CClientDC	dc(this);
	Graphics	graph(dc);

	m_bmBack	= ::new Bitmap(rect.Width(),rect.Height(),&graph);
	m_bmCrono	= ::new Bitmap(120,25,&graph);

	OnSysColorChange();
	//////////////////////////////////////////////////////////////////////////
	
	SetTimer(1,100,NULL);

	m_LineUpX = (INT)(rect.Width()*0.5f-60.0f);
	m_TrackX = (INT)(rect.Width()*0.5f-60.0f);

	return 0;
}

void CGenericInfoWnd::OnSysColorChange() 
{
	CStatic::OnSysColorChange();
			
	REAL				iWidth = (REAL)m_bmBack->GetWidth(),
						iHeight = (REAL)m_bmBack->GetHeight();
	int					iCount=4;

	COLORREF			crefCaption1 = RGB(0,0,0),
						crefCaption2 = RGB(0,0,0); 
	Color				colorBack[4];
	PointF				pointsBack[] = {	PointF(0.0f,0.0f), 
											PointF(0.0f,iHeight), 
											PointF(iWidth,iHeight),
											PointF(iWidth,0.0f) },

						pointsLight[] = {	PointF(0.0f,0.0f),
											PointF(0.0f,iHeight*0.5f), 
											PointF(iWidth*3.0f,3.0f), 
											PointF(iWidth*1.0f,0.0f) 
										},
						pointsDark[] = {	PointF(iWidth*1.0f,iHeight*0.5f),
											PointF(iWidth*1.0f,iHeight*0.0f), 
											PointF(iWidth*1.0f-4.0f,iHeight*0.5f-4.0f), 
											PointF(iWidth*0.0f,iHeight*0.5f) 
										},
						pointsDark2[] = {	PointF(iWidth*1.0f,iHeight*1.0f), 
											PointF(iWidth*1.0f,iHeight*0.5f),
											PointF(iWidth*1.0f-4,iHeight*1.0f-4), 
											PointF(iWidth*0.0f,iHeight*1.0f) 
										},
						pointsLight2[] = {	PointF(iWidth*0.0f,iHeight*0.5f),
											PointF(iWidth*0.0f,iHeight*1.0f), 
											PointF(iWidth*3.0f,iHeight*0.5f+3.0f), 
											PointF(iWidth*1.0f,iHeight*0.5f) 
										};
	GraphicsPath		pathBack,
						pathLight,
						pathLight2,
						pathDark,
						pathDark2;
	
	pathBack.AddLines(pointsBack,4);
	pathLight.AddLines(pointsLight,4);
	pathLight2.AddLines(pointsLight2,4);
	pathDark.AddLines(pointsDark,4);
	pathDark2.AddLines(pointsDark2,4);

	PathGradientBrush	brushBack(&pathBack),
						brushLight(&pathLight),
						brushLight2(&pathLight2),
						brushDark(&pathDark),
						brushDark2(&pathDark2);
	
	colorBack[0].SetFromCOLORREF(RGB(0,0,0));
	colorBack[1].SetFromCOLORREF(RGB(0,0,0));
	colorBack[2].SetFromCOLORREF(RGB(0,0,0));
	colorBack[3].SetFromCOLORREF(RGB(0,0,0));

//	colorBack[1].SetFromCOLORREF(RGB(255,218,185));
//	colorBack[2].SetFromCOLORREF(RGB(255,218,185));
//	colorBack[3].SetFromCOLORREF(RGB(255,218,185));

	brushBack.SetSurroundColors(colorBack,&iCount);
	brushBack.SetCenterColor(colorBack[0]);

	brushLight.SetSurroundColors(g_colorLight,&iCount);
	brushLight.SetCenterColor(g_colorLight[0]);
	brushLight.SetCenterPoint(pointsLight[0]);

	brushLight2.SetSurroundColors(g_colorLight,&iCount);
	brushLight2.SetCenterColor(g_colorLight[0]);
	brushLight2.SetCenterPoint(pointsLight2[0]);

	brushDark.SetSurroundColors(g_colorLight,&iCount);
	brushDark.SetCenterColor(g_colorLight[0]);
	brushDark.SetCenterPoint(pointsDark[0]);
	brushDark.SetGammaCorrection(TRUE);

	brushDark2.SetSurroundColors(g_colorLight,&iCount);
	brushDark2.SetCenterColor(g_colorLight[0]);
	brushDark2.SetCenterPoint(pointsDark2[0]);
	brushDark2.SetGammaCorrection(TRUE);

	SolidBrush	brushWhite( Color(255,255,255,255) );
	Graphics	graph(m_bmBack);

	graph.FillPath(&brushBack,&pathBack);
	graph.FillPath(&brushLight,&pathLight);
	graph.FillPath(&brushDark,&pathDark);
	graph.FillPath(&brushLight2,&pathLight2);
	graph.FillPath(&brushDark2,&pathDark2);
}

void CGenericInfoWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	Graphics		graph(dc);
	StringFormat	format;
	CString			strTitle;
	CRect			rect;
	WCHAR			wchar[200];
	
	GetClientRect(&rect);

	graph.DrawImage(m_bmBack,0,0);
//	graph.Clear(Color::White);

	format.SetAlignment(StringAlignmentCenter);
	
	strTitle.LoadString(IDS_LINEUPLENGTH);
	MultiByteConversion(strTitle,wchar);
	graph.DrawString(wchar,-1,g_fontSmallTitle,PointF((REAL)(rect.right*0.50),3),&format,&SolidBrush(Color(255,150,150,150)));

	strTitle.LoadString(IDS_NOWSHOWING);
	MultiByteConversion(strTitle,wchar);
	graph.DrawString(wchar,-1,g_fontSmallTitle,PointF((REAL)(rect.right*0.50),53),&format,&SolidBrush(Color(255,150,150,150)));
}

void CGenericInfoWnd::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( !CheckKey(nChar) )
		CStatic::OnSysKeyUp(nChar, nRepCnt, nFlags);
}

void CGenericInfoWnd::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( !CheckKey(nChar) )
		CStatic::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CGenericInfoWnd::OnTimer(UINT nIDEvent) 
{
	CString str;
	WCHAR	wchar[20];
	DWORD64	qwTime;

	//////////////////////////////////////////////////////////////////////////
	//	Drawing the LineUp Crono
	//	Get the LineUp Length, and coinverts it into a wchar string
	qwTime=((CLineUpWnd *)(g_wndLineUp))->GetTotalLength();
	GetTimeString64(qwTime,&str);
	str.Delete(10,2);
	MultiByteConversion(str,wchar);

	CClientDC		dc(this);
	Graphics		graphdc(dc);
	Graphics		graph(m_bmCrono);
	StringFormat	format;

	format.SetAlignment(StringAlignmentCenter);

	// Draw the line up crono, on the mem bitmap
	graph.DrawImage(m_bmBack,0,0,m_LineUpX,18,120,25,UnitPixel);
	graph.DrawString(wchar,-1,g_font24,PointF(62.0f,2.0f),&format,&SolidBrush(g_colorShadow));
	if( qwTime>6000000000 )
		graph.DrawString(wchar,-1,g_font24,PointF(60.0f,0.0f),&format,&SolidBrush(g_colorGreen));
	else if( qwTime>3000000000 )
		graph.DrawString(wchar,-1,g_font24,PointF(60.0f,0.0f),&format,&SolidBrush(Color::Yellow));
	else if( qwTime>0 )
		graph.DrawString(wchar,-1,g_font24,PointF(60.0f,0.0f),&format,&SolidBrush(g_colorRed));
	else
		graph.DrawString(wchar,-1,g_font24,PointF(60.0f,0.0f),&format,&SolidBrush(Color::White));

	// Puts the temp bitmap on the screen
	graphdc.DrawImage(m_bmCrono,(INT)m_LineUpX,18);

	// Get the last track time to finish
	qwTime=((CLineUpWnd *)g_wndLineUp)->GetLastTrackTimeToMix();
	GetTimeString64(qwTime,&str);
	str.Delete(10,2);
	MultiByteConversion(str,wchar);

	// Draw the Track crono
	graph.DrawImage(m_bmBack,0,0,m_TrackX,68,120,25,UnitPixel);
	graph.DrawString(wchar,-1,g_font24,PointF(61.0f,1.0f),&format,&SolidBrush(Color(255,150,100,100)));
	
	if( qwTime>100000000 )
		graph.DrawString(wchar,-1,g_font24,PointF(60.0f,0.0f),&format,&SolidBrush(g_colorGreen));
	else if( qwTime>50000000 )
		graph.DrawString(wchar,-1,g_font24,PointF(60.0f,0.0f),&format,&SolidBrush(Color::Yellow));
	else if( qwTime>0 )
		graph.DrawString(wchar,-1,g_font24,PointF(60.0f,0.0f),&format,&SolidBrush(g_colorRed));
	else
		graph.DrawString(wchar,-1,g_font24,PointF(60.0f,0.0f),&format,&SolidBrush(Color::White));

	// Puts the temp bitmap on the screen
	graphdc.DrawImage(m_bmCrono,(INT)m_TrackX,68);

}
