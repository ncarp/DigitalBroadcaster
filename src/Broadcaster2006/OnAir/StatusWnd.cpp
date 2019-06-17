// StatusWnd.cpp : implementation file
//

#include "stdafx.h"
#include "OnAir.h"
#include "StatusWnd.h"
#include "ExternalObjects.h"
#include "..\include\utils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern BOOL g_bHaspOK;
extern int  g_nHaspCount;
extern BOOL g_bNoLog;

/////////////////////////////////////////////////////////////////////////////
// CStatusWnd

CStatusWnd::CStatusWnd()
{
	m_nRed=0;
	m_bDesc=FALSE;
}

CStatusWnd::~CStatusWnd()
{
}


BEGIN_MESSAGE_MAP(CStatusWnd, CStatic)
	//{{AFX_MSG_MAP(CStatusWnd)
	ON_WM_CREATE()
	ON_WM_KEYUP()
	ON_WM_SYSKEYUP()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatusWnd message handlers

int CStatusWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	GetClientRect(&m_rect);

	m_rectAuto=m_rect;
	m_rectAuto.bottom=m_rectAuto.top+50;
//	m_rectAuto.DeflateRect(2,2,2,2);
//	m_rectAuto.bottom=m_rectAuto.Height()/3;

	m_rectLive=m_rectAuto;
	m_rectLive.OffsetRect(0,50);

	m_rectManual=m_rectLive;
	m_rectManual.OffsetRect(0,50);

	m_bmManual		= ::new Bitmap(AfxGetInstanceHandle(),(WCHAR*)MAKEINTRESOURCE(IDB_MANUAL));
	m_bmAutomatic	= ::new Bitmap(AfxGetInstanceHandle(),(WCHAR*)MAKEINTRESOURCE(IDB_AUTOMATIC));
	m_bmLive		= ::new Bitmap(AfxGetInstanceHandle(),(WCHAR*)MAKEINTRESOURCE(IDB_LIVE));

	CreateBitmap();
	CreateHotBitmap();
	CreateSelectedBitmap();

	SetTimer(10001,100,NULL);
	//////////////////////////////////////////////////////////////////////////
	
	return 0;
}

void CStatusWnd::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CStatic::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CStatusWnd::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CStatic::OnSysKeyUp(nChar, nRepCnt, nFlags);
}

void CStatusWnd::OnPaint() 
{
	CPaintDC	dc(this); // device context for painting
	CString		str;
	WCHAR		wchar[50];
	
	Graphics		graph(dc);
	SolidBrush		redBrush(Color(64,255,0,0));
	StringFormat	format;

	ImageAttributes imageAtt;
	ColorMap cMap;
	cMap.oldColor = Color(255, 0,0,0); 
	cMap.newColor = Color(  0, 255,255,255); 
	imageAtt.SetRemapTable(1, &cMap,ColorAdjustTypeDefault);
	
	format.SetAlignment(StringAlignmentCenter);
	
	graph.DrawImage(m_bmBack,0,0);
	graph.DrawImage(m_bmBack,0,50);
	graph.DrawImage(m_bmBack,0,100);
	graph.DrawImage(m_bmBack,0,150);

	PointF	pAutoCX(2,2),
			pText((REAL)(int)(m_rect.Width()*0.50f),33.0f);

	if( g_wAutomationMode==AUTOMATION_FULLAUTO )
		graph.DrawImage(m_bmSelected,pAutoCX);
	else if (m_wHot==AUTOMATION_FULLAUTO )
		graph.DrawImage(m_bmHot,m_rectAuto.left,m_rectAuto.top);
	else if( m_wSelected==AUTOMATION_FULLAUTO )
	{
	}

	str.LoadString(IDS_FULLAUTO);
	MultiByteConversion(str,wchar);
	graph.DrawImage(m_bmAutomatic,Rect(0,2,150,45),0,0,150,45,UnitPixel,&imageAtt);
//	graph.DrawString(wchar,-1,g_fontSmallTitle,pText,&format,&SolidBrush(Color::Black));
	
	//////////////////////////////////////////////////////////////////////////////////////
	//	Live assist
	if( g_wAutomationMode==AUTOMATION_LIVEASSIST )
	{
		graph.FillRectangle(&redBrush,m_rectLive.left,m_rectLive.top,m_rectLive.Width(),m_rectLive.Height());
		graph.DrawImage(m_bmSelected,m_rectLive.left,m_rectLive.top);
	}
	else if (m_wHot==AUTOMATION_LIVEASSIST )
		graph.DrawImage(m_bmHot,m_rectLive.left,m_rectLive.top);

	pText = PointF(m_rect.Width()*0.50f,83);
	str.LoadString(IDS_LIVEASSIST);
	MultiByteConversion(str,wchar);
	graph.DrawImage(m_bmLive,Rect(0,52,150,45),0,0,150,45,UnitPixel,&imageAtt);
//	graph.DrawString(wchar,-1,g_fontSmallTitle,pText,&format,&SolidBrush(Color::White));

	////////////////////////////////////////////////////////////////////////////////////////
	//	Manual
	if( g_wAutomationMode==AUTOMATION_MANUAL )
		graph.DrawImage(m_bmSelected,m_rectManual.left,m_rectManual.top);
	else if (m_wHot==AUTOMATION_MANUAL )
		graph.DrawImage(m_bmHot,m_rectManual.left,m_rectManual.top);

	pText = PointF(m_rect.Width()*0.50f,133);
	str.LoadString(IDS_MANUAL);
	MultiByteConversion(str,wchar);
	graph.DrawImage(m_bmManual,Rect(0,102,150,45),0,0,150,45,UnitPixel,&imageAtt);
//	graph.DrawString(wchar,-1,g_fontSmallTitle,pText,&format,&SolidBrush(Color::Black));

	/////////////////////////////////////////////////////////////////////////////////////////
	// Status
	if( g_bHaspOK )
	{
	}
	else
	{
		pText = PointF(m_rect.Width()*0.50f,163);
		str.Format("HASP ERROR\n%d",g_nHaspCount);
		MultiByteConversion(str,wchar);
		graph.DrawString(wchar,-1,g_fontSmallTitle,pText,&format,&SolidBrush(Color::Red));
	}
}

void CStatusWnd::OnTimer(UINT nIDEvent) 
{
	static int nHasp = 0;

	if( m_bDesc )
	{
		m_nRed-=18;
		if( m_nRed<18 )
		{
			m_nRed=18;
			m_bDesc=FALSE;
		}
	}
	else
	{
		m_nRed+=18;
		if( m_nRed>96 )
		{
			m_nRed=96;
			m_bDesc=TRUE;
		}
	}

	Bitmap	bmTemp(m_rectLive.Width(),m_rectLive.Height());
	Graphics graph(&bmTemp);

	ImageAttributes imageAtt;
	ColorMap cMap;
	cMap.oldColor = Color(255, 0,0,0); 
	cMap.newColor = Color(  0, 0,0,0); 
	imageAtt.SetRemapTable(1, &cMap,ColorAdjustTypeDefault);

	if( g_wAutomationMode==AUTOMATION_FULLAUTO )
	{
		SolidBrush brRed(Color(m_nRed,0,255,0));
		graph.DrawImage(m_bmBack,0.0f,0.0f,
								(REAL)m_rectAuto.left,(REAL)m_rectAuto.top,
								(REAL)m_rectAuto.Width(),(REAL)m_rectAuto.Height(),
								UnitPixel
								);
		graph.DrawImage(m_bmSelected,0,0);
		graph.FillRectangle(&brRed,1.0f,1.0f,(REAL)m_rectAuto.Width()-2,(REAL)m_rectAuto.Height()-2 );
		graph.DrawImage(m_bmAutomatic,Rect(0,2,m_bmAutomatic->GetWidth(),m_bmAutomatic->GetHeight()),0,0,150,45,UnitPixel,&imageAtt);
		CClientDC dc(this);
		Graphics graphDC(dc);

		graphDC.DrawImage(&bmTemp,PointF((REAL)m_rectAuto.left,(REAL)m_rectAuto.top));
	}

	if( g_wAutomationMode==AUTOMATION_LIVEASSIST)
	{
		SolidBrush brRed(Color(m_nRed,255,255,0));
		graph.DrawImage(m_bmBack,0.0f,0.0f);
		graph.DrawImage(m_bmSelected,0,0);
		graph.FillRectangle(&brRed,1.0f,1.0f,(REAL)m_rectLive.Width()-2,(REAL)m_rectLive.Height()-2 );
		graph.DrawImage(m_bmLive,Rect(0,2,m_bmLive->GetWidth(),m_bmLive->GetHeight()),0,0,150,45,UnitPixel,&imageAtt);
		CClientDC dc(this);
		Graphics graphDC(dc);

		graphDC.DrawImage(&bmTemp,PointF((REAL)m_rectLive.left,(REAL)m_rectLive.top));
	}

	if( g_wAutomationMode==AUTOMATION_MANUAL)
	{
		SolidBrush brRed(Color(m_nRed+157,215,45,45));
		graph.FillRectangle(&SolidBrush(Color::Black),1.0f,1.0f,(REAL)m_rectManual.Width()-2,(REAL)m_rectManual.Height()-2 );
		graph.DrawImage(m_bmBack,0.0f,0.0f,
								(REAL)m_rectManual.left,(REAL)m_rectManual.top,
								(REAL)m_rectManual.Width(),(REAL)m_rectManual.Height(),
								UnitPixel
								);
//		graph.DrawImage(m_bmSelected,0,0);
//		graph.FillRectangle(&SolidBrush(Color::Black),1.0f,1.0f,(REAL)m_rectManual.Width()-2,(REAL)m_rectManual.Height()-2 );
		graph.FillRectangle(&brRed,1.0f,1.0f,(REAL)m_rectManual.Width()-2,(REAL)m_rectManual.Height()-2 );
		graph.DrawImage(m_bmManual,Rect(0,2,m_bmManual->GetWidth(),m_bmManual->GetHeight()),0,0,150,45,UnitPixel,&imageAtt);
		CClientDC dc(this);
		Graphics graphDC(dc);

		graphDC.DrawImage(&bmTemp,PointF((REAL)m_rectManual.left,(REAL)m_rectManual.top));
	}

	if( ((!g_bHaspOK) && (nHasp!=g_nHaspCount)) || (g_bNoLog) )
	{
		PointF pText;
		CString str;
		WCHAR wchar[100];
		StringFormat format;

		format.SetAlignment(StringAlignmentCenter);

		SolidBrush brRed(Color(m_nRed+157,215,45,45));
		graph.FillRectangle(&SolidBrush(Color::Black),1.0f,1.0f,(REAL)m_rectManual.Width()-2,(REAL)m_rectManual.Height()-2 );
		graph.DrawImage(m_bmBack,0.0f,0.0f,
								(REAL)m_rectManual.left,(REAL)m_rectManual.top+50,
								(REAL)m_rectManual.Width(),(REAL)m_rectManual.Height(),
								UnitPixel
								);
		graph.FillRectangle(&brRed,1.0f,1.0f,(REAL)m_rectManual.Width()-2,(REAL)m_rectManual.Height()-2 );

		if( (!g_bHaspOK) && (nHasp!=g_nHaspCount) )
		{
			pText = PointF(m_rect.Width()*0.50f,5);
			str.Format("HASP ERROR\n%d",g_nHaspCount);
			MultiByteConversion(str,wchar);
			graph.DrawString(wchar,-1,g_font14Bold,pText,&format,&SolidBrush(Color::Blue));
		}

		CClientDC dc(this);
		Graphics graphDC(dc);
		

		graphDC.DrawImage(&bmTemp,PointF((REAL)m_rectManual.left,(REAL)m_rectManual.top+50));
	}
}

void CStatusWnd::CreateBitmap()
{
	//////////////////////////////////////////////////////////////////////////
	// Create the background bitmpa 
	CRect	rect;
	GetClientRect(&rect);

	CClientDC	dc(this);
	Graphics	graphdc(dc);

	m_bmBack = ::new Bitmap(rect.Width(),50.0f,&graphdc);
	
	//////////////////////////////////////////////////////////////////////////
	// Paint the bitmap

	REAL				rWidth = (REAL)m_bmBack->GetWidth(),
						rHeight = (REAL)m_bmBack->GetHeight();
	int					iCount=4;

	COLORREF			crefCaption1 = RGB(123,151,223),
						crefCaption2 = RGB(157,185,235); 
	Color				colorBack[4];
	PointF				pointsBack[] = {	PointF(0.0f,0.0f), 
											PointF(0.0f,50.0f), 
											PointF(rWidth,50.0f),
											PointF(rWidth,0.0f) },

						pointsLight[] = {	PointF(0.0f,0.0f),
											PointF(0.0f,50.0f), 
											PointF(rWidth*3.2f,0.0f), 
											PointF(rWidth,0.0f) 
										},
						pointsDark[] = {	PointF(0.0f,50.0f), 
											PointF(rWidth,50.0f),
											PointF(rWidth,0.0f), 
											PointF( rWidth*0.8f,40.0f) 
										};
	GraphicsPath		pathBack,
						pathLight,
						pathDark;
	
	pathBack.AddLines(pointsBack,4);
	pathLight.AddLines(pointsLight,4);
	pathDark.AddLines(pointsDark,4);

	PathGradientBrush	brushBack(&pathBack),
						brushLight(&pathLight),
						brushDark(&pathDark);
	
	colorBack[0].SetFromCOLORREF(RGB(0,0,0));
	colorBack[1].SetFromCOLORREF(RGB(0,0,0));
	colorBack[2].SetFromCOLORREF(RGB(0,0,0));
	colorBack[3].SetFromCOLORREF(RGB(0,0,0));

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
	Graphics			graph(m_bmBack);

	graph.FillPath(&brushBack,&pathBack);
	graph.FillPath(&brushLight,&pathLight);
	graph.FillPath(&brushDark,&pathDark);

}

void CStatusWnd::CreateHotBitmap()
{
	m_bmHot = ::new Bitmap(m_rectAuto.Width(),m_rectAuto.Height());
	Graphics	graph(m_bmHot);
	Point		points[]={ Point(0,0),
							Point(0,m_bmHot->GetHeight()),
							Point(m_bmHot->GetWidth(),m_bmHot->GetHeight()),
							Point(m_bmHot->GetWidth(),0) };

	Point		pointsDark[]={ Point(0,m_bmHot->GetHeight()-1),
								Point(m_bmHot->GetWidth()-1,m_bmHot->GetHeight()-1),
								Point(m_bmHot->GetWidth()-1,0) };

	Point		pointsLight[]={ Point(m_bmHot->GetWidth(),0),
								Point(0,0),
								Point(0,m_bmHot->GetHeight()) };

	Color		colors[]={ Color(64,255,255,255),
							Color(32,255,255,255),
							Color(16,255,255,255),
							Color(32,255,255,255) };
	GraphicsPath			path;
	path.AddLines(points,4);

	int	nColors=4;
	PathGradientBrush		brush(&path);
	brush.SetSurroundColors(colors,&nColors);
	brush.SetCenterColor(colors[3]);

	graph.FillPath(&brush,&path);
	graph.DrawLines(&Pen(Color(190,64,64,64)),pointsDark,3);
	graph.DrawLines(&Pen(Color(190,255,255,255)),pointsLight,3);
}

void CStatusWnd::CreateSelectedBitmap()
{
	m_bmSelected = ::new Bitmap(m_rect.Width(),50);
	Graphics	graph(m_bmSelected);
	Point		points[]={ Point(0,0),
							Point(0,m_bmSelected->GetHeight()),
							Point(m_bmSelected->GetWidth(),m_bmSelected->GetHeight()),
							Point(m_bmSelected->GetWidth(),0) };

	Point		pointsLight[]={ Point(0,m_bmSelected->GetHeight()-1),
								Point(m_bmSelected->GetWidth()-1,m_bmSelected->GetHeight()-1),
								Point(m_bmSelected->GetWidth()-1,0) };

	Point		pointsDark[]={ Point(m_bmSelected->GetWidth(),0),
								Point(0,0),
								Point(0,m_bmSelected->GetHeight()) };

	Color		colors[]={ Color(150,255,255,255),
							Color(128,255,255,255),
							Color(96,255,255,255),
							Color(128,255,255,255) };
	GraphicsPath			path;
	path.AddLines(points,4);

	int	nColors=4;
	PathGradientBrush		brush(&path);
	brush.SetSurroundColors(colors,&nColors);
	brush.SetCenterColor(colors[3]);

	graph.FillPath(&brush,&path);
	graph.DrawLines(&Pen(Color(190,64,64,64)),pointsDark,3);
	graph.DrawLines(&Pen(Color(190,255,255,255)),pointsLight,3);
}

void CStatusWnd::OnRButtonDown(UINT nFlags, CPoint point) 
{
	m_wSelected=m_wHot;
}

void CStatusWnd::OnRButtonUp(UINT nFlags, CPoint point) 
{
	if( ( m_wSelected!=AUTOMATION_NONE) && (m_wHot != AUTOMATION_NONE) )
	{
		g_wAutomationMode=m_wSelected;
		Invalidate();
		if( g_wAutomationMode == AUTOMATION_FULLAUTO )
		{
			g_wndLogOnBack->SetWindowPos(&wndTop,0,0,GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN),0);
			g_wndLogOn->SetWindowPos(&wndTopMost,250,250,0,0,SWP_NOSIZE);

			// Log Item -----------------------------------------------------------------------
			typeLogItem *lpLog=new typeLogItem;
			lpLog->wType = 0;
			lpLog->lID = 0;
			lpLog->lTraffic = 0;
			strcpy(lpLog->strName,"--> Full automation mode");
			g_wndAired->LogItem(lpLog);
			// --------------------------------------------------------------------------------
		} 
		else if( g_wAutomationMode == AUTOMATION_LIVEASSIST )
		{
			// Log Item -----------------------------------------------------------------------
			typeLogItem *lpLog=new typeLogItem;
			lpLog->wType = 0;
			lpLog->lID = 0;
			lpLog->lTraffic = 0;
			strcpy(lpLog->strName,"--> Live-assist mode");
			g_wndAired->LogItem(lpLog);
			// --------------------------------------------------------------------------------	
		}
		else
		{
			// Log Item -----------------------------------------------------------------------
			typeLogItem *lpLog=new typeLogItem;
			lpLog->wType = 0;
			lpLog->lID = 0;
			lpLog->lTraffic = 0;
			strcpy(lpLog->strName,"--> Manual mode");
			g_wndAired->LogItem(lpLog);
			// --------------------------------------------------------------------------------
		}
	}
}

void CStatusWnd::OnMouseMove(UINT nFlags, CPoint point) 
{
	WORD temp;
	if( !m_rect.PtInRect(point) )
	{
		m_wHot=m_wSelected=AUTOMATION_NONE;
		ReleaseCapture();
		Invalidate();
		return;
	}

	if( m_rectAuto.PtInRect(point) )
		temp=AUTOMATION_FULLAUTO;
	else if( m_rectLive.PtInRect(point) )
		temp=AUTOMATION_LIVEASSIST;
	else if( m_rectManual.PtInRect(point) )
		temp=AUTOMATION_MANUAL;
	else
		temp=AUTOMATION_NONE;

	if( temp!=m_wHot )
	{
		m_wHot=temp;
		Invalidate();
	}
	SetCapture();
}
