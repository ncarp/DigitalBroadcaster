// TimerDefinition.cpp : implementation file
//

#include "stdafx.h"
#include <gdiplus.h>

using namespace Gdiplus;


//#include "OnAirDefines.h"
#include "TimerDefinition.h"
#include "ExternalObjects.h"
#include "..\include\utils.h"
//#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTimerDefinition

CTimerDefinition::CTimerDefinition()
{
	m_bmSpectrum=NULL;
	m_bmTimers=NULL;
	
	m_dwFlags=0xffff;

	CString str;

	m_Menu=new CMenu();
	m_Menu->CreatePopupMenu();

	str.LoadString(IDS_MENUSTART);
	m_Menu->AppendMenu(MF_STRING,MN_START,str);

	str.LoadString(IDS_MENUFADEIN);
	m_Menu->AppendMenu(MF_STRING,MN_FADEIN,str);

	str.LoadString(IDS_MENUINTRO);
	m_Menu->AppendMenu(MF_STRING,MN_INTRO,str);

	str.LoadString(IDS_MENUFADEOUT);
	m_Menu->AppendMenu(MF_STRING,MN_FADEOUT,str);

	str.LoadString(IDS_MENUMIX);
	m_Menu->AppendMenu(MF_STRING,MN_MIX,str);

	str.LoadString(IDS_MENUEND);
	m_Menu->AppendMenu(MF_STRING,MN_END,str);

	str.LoadString(IDS_MENULOOPA);
	m_Menu->AppendMenu(MF_STRING,MN_LOOPA,str);

	str.LoadString(IDS_MENULOOPB);
	m_Menu->AppendMenu(MF_STRING,MN_LOOPB,str);

	m_rectPos.SetRect(0,0,0,0);

	CursorArrow=LoadCursor(NULL,IDC_ARROW);
	CursorSize=LoadCursor(NULL,IDC_SIZEWE);
	m_ItemDrag = 0;
}

CTimerDefinition::~CTimerDefinition()
{
}


BEGIN_MESSAGE_MAP(CTimerDefinition, CStatic)
	//{{AFX_MSG_MAP(CTimerDefinition)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_COMMAND( MN_START, OnSetStart )
	ON_COMMAND( MN_FADEIN, OnSetFadeIn )
	ON_COMMAND( MN_INTRO, OnSetIntro )
	ON_COMMAND( MN_FADEOUT, OnSetFadeOut )
	ON_COMMAND( MN_MIX, OnSetMix )
	ON_COMMAND( MN_END, OnSetEnd )
	ON_COMMAND( MN_LOOPA, OnSetLoopA )
	ON_COMMAND( MN_LOOPB, OnSetLoopB )
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimerDefinition message handlers

void CTimerDefinition::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rect;
	GetClientRect(rect);

	dc.FillRect(&rect,&CBrush(GetSysColor(COLOR_3DFACE)));
	dc.Draw3dRect(0,0,rect.Width(),rect.Height(),RGB(64,64,64),RGB(255,255,255));

	PaintTimerBM();
	PaintAll();
}

void CTimerDefinition::OnTimer(UINT nIDEvent) 
{
	PaintAll();
}

int CTimerDefinition::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;
	
//	SetTimer(1,500,NULL);
	GetClientRect(&m_rect);

	CClientDC	dc(this);
	Graphics	graphdc(dc);

	CString		str;
	WCHAR		wchar[20];
	PointF		pointOrigin((float)m_rect.Width()/2,(float)m_rect.Height()/2);

	GetTimeString(0,&str);
	str.Delete(0,3);
	str.Delete(7,2);
	MultiByteConversion(str,wchar);

	StringFormat	sFormat;
	sFormat.SetAlignment(StringAlignmentCenter);
	sFormat.SetLineAlignment(StringAlignmentCenter);

	graphdc.MeasureString( wchar,-1,g_font36,pointOrigin,&sFormat,&rectf);
	rectf.Inflate(2.0f,2.0f);
	
	// Creates a bitmap big enougth to display the string
	m_bmCrono = ::new Bitmap((UINT)rectf.Width,(UINT)rectf.Height,&graphdc);

	return 0;
}

void CTimerDefinition::SetSpectrum(Bitmap *b)
{
	m_bmSpectrum = b;
	if( m_bmSpectrum!=NULL )
	{
		m_bmTimers = ::new Bitmap( m_bmSpectrum->GetWidth(),m_bmSpectrum->GetHeight(),PixelFormat32bppARGB);
		PaintTimerBM();
	}
}

void CTimerDefinition::SetViewPoint( long pos )
{
	m_RightPos=pos;
	PaintAll();
}

void CTimerDefinition::PaintCrono()
{
	CClientDC	dc(this);
	
	dc.InvertRect(&m_rectPos);

	if( (m_PlayPos>=m_RightPos) && (m_PlayPos<m_RightPos+10000) )
	{
		float X = (float)(m_PlayPos-m_RightPos)*m_xres;
		m_rectPos.SetRect( (int)X,4,(int)X+2,52);
		dc.InvertRect(&m_rectPos);
	}
	else
		m_rectPos.SetRect(0,0,0,0);
}

void CTimerDefinition::PaintAll() 
{
	PaintTimerBM();

	CClientDC	dc(this);
	Graphics	graphdc(dc);
	
	Bitmap		bm(m_rect.Width(),m_rect.Height(),&graphdc);
	
	Graphics	graph(&bm);
	
	graph.Clear(Color(255,212,208,200)) ;

	if( m_bmSpectrum!=NULL )
	{
		graph.DrawImage(m_bmTimers  ,2,2,(int)((float)m_RightPos*m_xres),0,(int)((REAL)m_rect.Width()-2),48,UnitPixel);
		graph.DrawImage(m_bmSpectrum,2,2,(int)((float)m_RightPos*m_xres),0,(int)((REAL)m_rect.Width()-2),48,UnitPixel);
	}

	graphdc.DrawImage(&bm,2,4,2,2,m_rect.Width()-4,48,UnitPixel);
	m_rectPos.SetRect(0,0,0,0);
}

void CTimerDefinition::PaintTimerBM()
{
	if( m_bmSpectrum==NULL )
		return;

	Graphics	graphbm(m_bmTimers);

	RectF		rectIntro(m_Start*m_xres,0.0f,(m_Intro-m_Start)*m_xres,48);
	RectF		rectMix(m_Mix*m_xres,0.0f,(m_End-m_Mix)*m_xres,48.0f);
	RectF		rectEnd(m_End*m_xres,0.0f,2.0f,48.0f);

	LinearGradientBrush	brushRed(	PointF( (REAL)(m_Intro-5000)*m_xres,0),
									PointF( (REAL)(m_Intro)*m_xres,0),
									Color(255,255,255,0),
									Color(255,255,0,0) );

	LinearGradientBrush	brushYellow(PointF( (REAL)(m_Intro-10000)*m_xres,0),
									PointF( (REAL)(m_Intro-5000)*m_xres,0),
									Color(255,0,255,0),
									Color(255,255,255,0) );


	graphbm.Clear(Color(255,212,208,200));
	
	if( (m_Intro-m_Start)>10000 )
	{
		// the intro has green, yellow and red
		graphbm.FillRectangle(&SolidBrush(Color(255,0,255,0)),
								RectF(m_Start*m_xres,0.0f,(m_Intro-m_Start-10000)*m_xres,48) );
		graphbm.FillRectangle(&brushYellow,
								RectF((m_Intro-10000)*m_xres,0.0f,5000*m_xres,48) );
		graphbm.FillRectangle(&brushRed,
								RectF((m_Intro-5000)*m_xres,0.0f,5000*m_xres,48) );
	}
	else if( (m_Intro-m_Start)>5000 )
	{
		// Yellow and red
		graphbm.FillRectangle(&brushYellow,
								RectF( (m_Start)*m_xres,0.0f,(m_Intro-m_Start-5000)*m_xres,48) );
		graphbm.FillRectangle(&brushRed,
								RectF( (m_Intro-5000)*m_xres,0.0f,5000*m_xres,48) );
	}
	else if( (m_Intro-m_Start)>0 )
	{
		// red
		graphbm.FillRectangle(&brushRed,
								RectF((m_Start)*m_xres,0.0f,(m_Intro-m_Start)*m_xres,48) );
	}

	graphbm.FillRectangle(&SolidBrush(Color(255,222,222,0)),rectMix);

	if( (m_FadeIn) && (m_FadeIn>m_Start) )
	{
		// draws a path
		PointF	points[]={ PointF(0.0f,0.0f),
							PointF(0.0f,48.0f),
							PointF(m_Start*m_xres,48.0f),
							PointF(m_FadeIn*m_xres,0.0f) };

		GraphicsPath	path;
		path.AddLines(points,4);
		graphbm.FillPath(&SolidBrush(Color(128,128,128)),&path);
	}
	else
		// Draws a rectangle
		graphbm.FillRectangle(&SolidBrush(Color(128,128,128)),RectF(0.0f,0.0f,m_Start*m_xres,48) );

	if( (m_FadeOut) && (m_FadeOut<m_End) )
	{
		// Draw a path
		PointF	points[]={ PointF(m_FadeOut*m_xres,0.0f),
							PointF(m_End*m_xres,48.0f),
							PointF((m_End+10000)*m_xres,48.0f),
							PointF((m_End+10000)*m_xres,0.0f) };

		GraphicsPath	path;
		path.AddLines(points,4);
		graphbm.FillPath(&SolidBrush(Color(128,128,128)),&path);
	}
	else
	{
		// draws a rectangle
		graphbm.FillRectangle(&SolidBrush(Color(128,128,128)),RectF(m_End*m_xres,0.0f,10000.0f*m_xres,48) );
	}

	if( m_LoopB > m_LoopA )
	{
		graphbm.FillRectangle(&SolidBrush(Color(192,255,255,255)),RectF(m_LoopA*m_xres,0.0f,(m_LoopB-m_LoopA)*m_xres,48) );
	}

	graphbm.FillRectangle(&SolidBrush(Color(255,0,0,0)),RectF(m_Start*m_xres,0.0f,2.0f,48.0f));
	graphbm.FillRectangle(&SolidBrush(Color(255,0,0,0)),RectF(m_FadeIn*m_xres,0.0f,2.0f,48.0f));
	graphbm.FillRectangle(&SolidBrush(Color(255,0,0,0)),RectF(m_Intro*m_xres,0.0f,2.0f,48.0f));
	graphbm.FillRectangle(&SolidBrush(Color(255,0,0,0)),RectF(m_FadeOut*m_xres,0.0f,2.0f,48.0f));
	graphbm.FillRectangle(&SolidBrush(Color(255,0,0,0)),RectF(m_Mix*m_xres,0.0f,2.0f,48.0f));
	graphbm.FillRectangle(&SolidBrush(Color(255,0,0,0)),RectF(m_End*m_xres,0.0f,2.0f,48.0f));
	graphbm.FillRectangle(&SolidBrush(Color(255,0,0,255)),RectF(m_LoopA*m_xres,0.0f,2.0f,48.0f));
	graphbm.FillRectangle(&SolidBrush(Color(255,0,0,255)),RectF(m_LoopB*m_xres,0.0f,2.0f,48.0f));
}

void CTimerDefinition::OnRButtonUp(UINT nFlags, CPoint point) 
{
	CRect Rect;
	GetWindowRect( &Rect );
	
	m_LastClickPos=(long)((float)(point.x/m_xres)+m_RightPos);
	m_Menu->TrackPopupMenu(TPM_LEFTALIGN,point.x+Rect.left,point.y+Rect.top,this);
}

void CTimerDefinition::OnLButtonDown(UINT nFlags, CPoint point) 
{
	long tpos=m_RightPos+(long)((float)point.x/m_xres);
	GetParent()->SendMessage(UM_GOTO,0,tpos);
	
	if( (tpos>m_Start-100) && (tpos<m_Start+100) )
		m_ItemDrag=1;
	else if( (tpos>m_FadeIn-100) && (tpos<m_FadeIn+100) )
		m_ItemDrag=2;
	else if( (tpos>m_Intro-100) && (tpos<m_Intro+100) )
		m_ItemDrag=3;
	else if( (tpos>m_FadeOut-100) && (tpos<m_FadeOut+100) )
		m_ItemDrag=4;
	else if( (tpos>m_Mix-100) && (tpos<m_Mix+100) )
		m_ItemDrag=5;
	else if( (tpos>m_End-100) && (tpos<m_End+100) )
		m_ItemDrag=6;
	else if( (tpos>m_LoopA-100) && (tpos<m_LoopA+100) )
		m_ItemDrag=7;
	else if( (tpos>m_LoopB-100) && (tpos<m_LoopB+100) )
		m_ItemDrag=8;
	else
		m_ItemDrag=0;

	CStatic::OnLButtonDown(nFlags, point);
}

void CTimerDefinition::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_ItemDrag=0;
}

void CTimerDefinition::OnMouseMove(UINT nFlags, CPoint point) 
{
	long tpos=m_RightPos+(long)((float)point.x/m_xres);
	m_LastClickPos=tpos;
	
	switch( m_ItemDrag )
	{
	case 0:
		if( ( (tpos>m_Start-100) && (tpos<m_Start+100) ) ||
			( (tpos>m_FadeIn-100) && (tpos<m_FadeIn+100) ) ||
			( (tpos>m_Intro-100) && (tpos<m_Intro+100) ) ||
			( (tpos>m_FadeOut-100) && (tpos<m_FadeOut+100) ) ||
			( (tpos>m_Mix-100) && (tpos<m_Mix+100) ) ||
			( (tpos>m_End-100) && (tpos<m_End+100) ) ||
			( (tpos>m_LoopA-100) && (tpos<m_LoopA+100) ) ||
			( (tpos>m_LoopB-100) && (tpos<m_LoopB+100) ) )

			SetClassLong(m_hWnd,GCL_HCURSOR,(LONG)CursorSize);
		else
			SetClassLong(m_hWnd,GCL_HCURSOR,(LONG)CursorArrow);
		break;
	case 1:
		OnSetStart();
		GetParent()->SendMessage(UM_GOTO,0,tpos);
		break;
	case 2:
		OnSetFadeIn();
		GetParent()->SendMessage(UM_GOTO,0,tpos);
		break;
	case 3:
		OnSetIntro();
		GetParent()->SendMessage(UM_GOTO,0,tpos);
		break;
	case 4:
		OnSetFadeOut();
		GetParent()->SendMessage(UM_GOTO,0,tpos);
		break;
	case 5:
		OnSetMix();
		GetParent()->SendMessage(UM_GOTO,0,tpos);
		break;
	case 6:
		OnSetEnd();
		GetParent()->SendMessage(UM_GOTO,0,tpos);
		break;
	case 7:
		OnSetLoopA();
		GetParent()->SendMessage(UM_GOTO,0,tpos);
		break;
	case 8:
		OnSetLoopB();
		GetParent()->SendMessage(UM_GOTO,0,tpos);
		break;
	}

	CStatic::OnMouseMove(nFlags, point);
}

void CTimerDefinition::OnSetStart()
{
	m_Start = m_LastClickPos;
	PaintTimerBM();
	PaintAll();
	GetParent()->SendMessage(UM_UPDATETIMERS);
}

void CTimerDefinition::OnSetFadeIn()
{
	m_FadeIn = m_LastClickPos;
	PaintTimerBM();
	PaintAll();
	GetParent()->SendMessage(UM_UPDATETIMERS);
}

void CTimerDefinition::OnSetIntro()
{
	m_Intro = m_LastClickPos;
	PaintTimerBM();
	PaintAll();
	GetParent()->SendMessage(UM_UPDATETIMERS);
}

void CTimerDefinition::OnSetFadeOut()
{
	m_FadeOut = m_LastClickPos;
	PaintTimerBM();
	PaintAll();
	GetParent()->SendMessage(UM_UPDATETIMERS);
}

void CTimerDefinition::OnSetMix()
{
	m_Mix = m_LastClickPos;
	PaintTimerBM();
	PaintAll();
	GetParent()->SendMessage(UM_UPDATETIMERS);
}

void CTimerDefinition::OnSetEnd()
{
	m_End = m_LastClickPos;
	PaintTimerBM();
	PaintAll();
	GetParent()->SendMessage(UM_UPDATETIMERS);
}

void CTimerDefinition::OnSetLoopA()
{
	m_LoopA = m_LastClickPos;
	PaintTimerBM();
	PaintAll();
	GetParent()->SendMessage(UM_UPDATETIMERS);
}

void CTimerDefinition::OnSetLoopB()
{
	m_LoopB = m_LastClickPos;
	PaintTimerBM();
	PaintAll();
	GetParent()->SendMessage(UM_UPDATETIMERS);
}

void CTimerDefinition::DeleteBM()
{
	if( m_bmSpectrum != NULL )
		::delete m_bmSpectrum;

	if( m_bmTimers != NULL )
		::delete m_bmTimers;

	m_bmSpectrum=NULL;
	m_bmTimers=NULL;
}