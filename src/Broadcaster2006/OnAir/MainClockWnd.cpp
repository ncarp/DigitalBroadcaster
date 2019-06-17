// MainClockWnd.cpp : implementation file
//

#include "stdafx.h"
#include <gdiplus.h>
using namespace Gdiplus;

#include "OnAir.h"
#include "MainClockWnd.h"
#include "ExternalObjects.h"
#include "OnAirUtils.h"
#include "..\include\utils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDT_MAINCLOCK	1


/////////////////////////////////////////////////////////////////////////////
// CMainClockWnd

CMainClockWnd::CMainClockWnd()
{
	m_strPreviousDate="";
}

CMainClockWnd::~CMainClockWnd()
{
	delete m_bmBack;
}

BEGIN_MESSAGE_MAP(CMainClockWnd, CStatic)
	//{{AFX_MSG_MAP(CMainClockWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_SYSCOLORCHANGE()
	ON_WM_KEYUP()
	ON_WM_SYSKEYUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainClockWnd message handlers

int CMainClockWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;

	/////////////////////////////////////////////////////////////////////////
	//	Inicialize m_bmBack
	CRect rect;
	GetClientRect(&rect);

	CClientDC	dc(this);
	Graphics	graph(dc);

	m_bmBack = ::new Bitmap(rect.Width(),rect.Height(),&graph);
	OnSysColorChange();

	/////////////////////////////////////////////////////////////////////////
	//	Start the timer
	SetTimer(IDT_MAINCLOCK,250,NULL);

	return 0;
}

void CMainClockWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	Graphics		graph(dc);
	
	graph.DrawImage(m_bmBack,0,0);
	
	m_strPreviousDate="";

	OnTimer(IDT_MAINCLOCK);
}

void CMainClockWnd::OnTimer(UINT nIDEvent) 
{
	COleDateTime	time=COleDateTime::GetCurrentTime();
	CString	strTime;
	WCHAR	wcharTime[50];

	CClientDC	dc(this);
	Graphics	graph(dc);
	RectF		rectf;
	PointF		pointOrigin( (REAL)m_bmBack->GetWidth()/2.0f,1.0f);
	
	///////////////////////////////////////////////////////////////////////
	//	Prepares the text to print
	strTime.Format("%2d:%2d:%2d",time.GetHour(),time.GetMinute(),time.GetSecond() );
	strTime.Replace(" ","0");

	MultiByteConversion(strTime,wcharTime);

	// Create a StringFormat object, and set the text alignment to center
	StringFormat	sFormat;
	sFormat.SetAlignment(StringAlignmentCenter);

	// Measures the string rectangle
	graph.MeasureString( wcharTime,-1,g_font36,pointOrigin,&sFormat,&rectf);
	rectf.Inflate(2.0f,2.0f);
	
	// Creates a bitmap big enougth to display the string
	Bitmap		bmTime((UINT)rectf.Width,(UINT)rectf.Height,&graph);

	// Creates a graphics object, to draw de time
	Graphics	graphTime(&bmTime);
	PointF		pointText(rectf.Width/2+2,3);

	graphTime.DrawImage(m_bmBack,0.0f,0.0f,rectf.X,rectf.Y,rectf.Width,rectf.Height,UnitPixel);
	graphTime.DrawString(wcharTime,-1,g_font36,pointText,&sFormat,&SolidBrush(Color(255,150,0,0)));
	pointText.X-=3;
	pointText.Y-=3;
	graphTime.DrawString(wcharTime,-1,g_font36,pointText,&sFormat,g_brushCaptionText);

	// Draws the string onto the main Graphics object
	graph.DrawImage(&bmTime,rectf.X,rectf.Y);

	///////////////////////////////////////////////////////////////////////
	//	Drawing the date. We start of by checking if the date as changed
	CString strDate;
	CString strDay;
	CString strMonth;

	strDay.LoadString(IDS_SUNDAY+(time.GetDayOfWeek()-1));
	strMonth.LoadString(IDS_JANUARY+(time.GetMonth()-1));
	strDate.Format("%s\n%s, %d",strDay,strMonth,time.GetDay());

	if( strDate!=m_strPreviousDate )
	{
		WCHAR wcharDate[50];

		m_strPreviousDate=strDate;
		
		// Convert strDate to WCHAR
		MultiByteConversion(strDate,wcharDate);

		// Set the point of origin for drawing the date string
		pointOrigin=PointF( (REAL)m_bmBack->GetWidth()/2.0f,45.0f );

		// Measures the string rectangle
		graph.MeasureString( wcharDate,-1,g_font24,pointOrigin,&sFormat,&rectf);
		// Inflate the rectangle, so it can contain the date's shadow
		rectf.Inflate(3.0f,3.0f);
		rectf.Offset(-2.0f,0);
	
		// Creates a bitmap big enougth to display the string
		Bitmap		bmDate((UINT)rectf.Width,(UINT)rectf.Height,&graph);

		// Creates a graphics object, to draw de time
		Graphics	graphDate(&bmDate);

		pointText = PointF(rectf.Width/2+1,2);

		graphDate.DrawImage(m_bmBack,0.0f,0.0f,rectf.X,rectf.Y,rectf.Width,rectf.Height,UnitPixel);
		graphDate.DrawString(wcharDate,-1,g_font24,pointText,&sFormat,g_brushShadowText);
		pointText.X-=2;
		pointText.Y-=2;
		graphDate.DrawString(wcharDate,-1,g_font24,pointText,&sFormat,g_brushCaptionText);

		graph.DrawImage(&bmDate,rectf.X,rectf.Y);
	}
}

void CMainClockWnd::OnSysColorChange() 
{
	CStatic::OnSysColorChange();

	REAL	rWidth=(REAL)m_bmBack->GetWidth(),
			rHeight=(REAL)m_bmBack->GetHeight();
	int		nCount=4;

	///////////////////////////////////////////////////////////////////////
	// Set the background colors, points, path and brush
/*	Color	colorBack[]= { Color(255,255,160,122),
							Color(255,255,160,122),
							Color(255,255,160,122),
							Color(255,255,160,122) }; */

	Color	colorBack[]= { Color(255,0,0,0),
							Color(255,0,0,0),
							Color(255,0,0,0),
							Color(255,0,0,0) };


	// Path points
	PointF	pointsBack[]={	PointF(0.0f,0.0f),
							PointF(0.0f,rHeight),
							PointF(rWidth,rHeight),
							PointF(rWidth,0.0f) };
	// Set the path
	GraphicsPath	pathBack;
	pathBack.AddLines(pointsBack,4);
	// set the Back brush
	PathGradientBrush	brushBack(&pathBack);
	brushBack.SetSurroundColors(colorBack,&nCount);
	brushBack.SetGammaCorrection(TRUE);
	brushBack.SetCenterColor(colorBack[0]); 
//	SolidBrush brushBack( Color(255,0,0,128) );
//	brushBack.SetCenterPoint(pointsBack[0]);

	///////////////////////////////////////////////////////////////////////
	// Set the light shadow points, path, and brush
	PointF	pointsLight[]={	PointF(0.0f,0.0f),
							PointF(0.0f,rHeight),
							PointF(rWidth*3.2f,rHeight*0.0f),
							PointF(rWidth,0.0f) };
	// Set the path
	GraphicsPath	pathLight;
	pathLight.AddLines(pointsLight,4);
	// set the light brush
	PathGradientBrush	brushLight(&pathLight);
	brushLight.SetSurroundColors(g_colorLight,&nCount);
	brushLight.SetGammaCorrection(TRUE);
	brushLight.SetCenterColor(g_colorLight[0]);
	brushLight.SetCenterPoint(pointsLight[0]);

	///////////////////////////////////////////////////////////////////////
	// Sets the dark shadow points, path and brush
	PointF	pointsDark[]={	PointF(0.0f,rHeight),
							PointF(rWidth,rHeight),
							PointF(rWidth,0.0f),
							PointF(rWidth*0.8f,rHeight*0.8f) };
	// Set the path
	GraphicsPath	pathDark;
	pathDark.AddLines(pointsDark,4);
	// set the Dark brush
	PathGradientBrush	brushDark(&pathDark);
	brushDark.SetSurroundColors(g_colorDark,&nCount);
	brushDark.SetGammaCorrection(TRUE);
	brushDark.SetCenterColor(g_colorDark[1]);
	brushDark.SetCenterPoint(pointsDark[1]);
	
	///////////////////////////////////////////////////////////////////////
	// Draws the bitmap 
	Graphics graph(m_bmBack);
	graph.FillPath(&brushBack,&pathBack);
	graph.FillPath(&brushLight,&pathLight);
	graph.FillPath(&brushDark,&pathDark);
}

void CMainClockWnd::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( !CheckKey(nChar) )
		CStatic::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CMainClockWnd::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( !CheckKey(nChar) )
		CStatic::OnSysKeyUp(nChar, nRepCnt, nFlags);
}
