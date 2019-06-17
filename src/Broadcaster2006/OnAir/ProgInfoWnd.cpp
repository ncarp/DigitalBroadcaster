// ProgInfoWnd.cpp : implementation file
//

#include "stdafx.h"
#include <gdiplus.h>
using namespace Gdiplus;

#include "ExternalObjects.h"
#include "OnAirUtils.h"
#include "OnAir.h"
#include "ProgInfoWnd.h"
#include "..\include\Utils.h"
#include "..\include\RSScheduleHeadline.h"
#include "..\include\rsviewschedule.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define CRONO_WIDTH	120
/////////////////////////////////////////////////////////////////////////////
// CProgInfoWnd

CProgInfoWnd::CProgInfoWnd()
{
	m_pNextProg=NULL;

	m_Menu=new CMenu();
	m_Menu->CreatePopupMenu();

	m_ContentMenu = new CMenu();
	m_ContentMenu->CreatePopupMenu();

	m_bmSpot = new CBitmap();
	m_bmSpot->LoadBitmap( IDB_SPOT );

	m_bmJingle = new CBitmap();
	m_bmJingle->LoadBitmap( IDB_JINGLESMALL );

	m_bmMusic = new CBitmap();
	m_bmMusic->LoadBitmap( IDB_MUSICSMALL );

	m_bmRM = new CBitmap();
	m_bmRM->LoadBitmap( IDB_CONTAINER_RMS );

	m_bmVoice = new CBitmap();
	m_bmVoice->LoadBitmap( IDB_VOICEINSERT );

	m_bmTime = new CBitmap();
	m_bmTime->LoadBitmap( IDB_TIMESIGNAL );

	CString str;

	str.LoadString(IDS_REFRESH);
	m_Menu->AppendMenu(MF_STRING,CM_REFRESH,str);
	m_Menu->AppendMenu(MF_SEPARATOR);

	str.LoadString(IDS_MENULINEUP);
	m_Menu->AppendMenu(MF_STRING,CM_LINEUP,str);
	m_Menu->AppendMenu(MF_SEPARATOR);

	str.LoadString(IDS_MENUSKIPSCHEDULE);
	m_Menu->AppendMenu(MF_STRING,CM_SKIP,str);

	str.LoadString(IDS_CONTENT);
	m_Menu->AppendMenu(MF_POPUP,(UINT)m_ContentMenu->m_hMenu,str);

	m_qwStartPlaying=0;
	m_qwStart=0;

	m_nCount=0;
	m_strOnAirConnect = g_strOnAirConnect;
}

CProgInfoWnd::~CProgInfoWnd()
{
}

BEGIN_MESSAGE_MAP(CProgInfoWnd, CStatic)
	//{{AFX_MSG_MAP(CProgInfoWnd)
	ON_WM_CREATE()
	ON_WM_SYSCOLORCHANGE()
	ON_WM_PAINT()
	ON_WM_SYSKEYUP()
	ON_WM_KEYUP()
	ON_WM_TIMER()
	ON_WM_RBUTTONUP()
	ON_COMMAND( CM_REFRESH, OnRefresh )
	ON_COMMAND( CM_LINEUP, OnLineUp )
	ON_COMMAND( CM_SKIP, OnSkip )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProgInfoWnd message handlers

int CProgInfoWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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

	m_bmCrono= ::new Bitmap(120,25,&graph);

	//////////////////////////////////////////////////////////////////////////
	if( m_strOnAirConnect!="" )
	{
		SetTimer(1,90,NULL);
		GetNextProg();
	}

	return 0;
}

void CProgInfoWnd::OnSysColorChange() 
{
	CStatic::OnSysColorChange();
	
	REAL				iWidth = (REAL)m_bmBack->GetWidth(),
						iHeight = (REAL)m_bmBack->GetHeight();
	int					iCount=4;

	COLORREF			crefCaption1 = RGB(123,151,223),
						crefCaption2 = RGB(157,185,235); 
	Color				colorBack[4];
	PointF				pointsBack[] = {	PointF(0.0f,0.0f), 
											PointF(0.0f,iHeight), 
											PointF(iWidth,iHeight),
											PointF(iWidth,0.0f) },

						pointsLight[] = {	PointF(0.0f,0.0f),
											PointF(0.0f,iHeight), 
											PointF(iWidth*3.1f,iHeight*0.1f), 
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
	Graphics	graph(m_bmBack);

	graph.FillPath(&brushBack,&pathBack);
	graph.FillPath(&brushLight,&pathLight);
	graph.FillPath(&brushDark,&pathDark);
}

void CProgInfoWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	WCHAR	wchar[200];
	CString	strTitle,
			str;
	CRect	rect;

	strTitle.LoadString(IDS_NEXTPROG);
	GetClientRect(&rect);

	Graphics		graph(dc);
	StringFormat	format;
	
	graph.DrawImage(m_bmBack,0,0);

	if( m_pNextProg==NULL )
		str.LoadString(IDS_NOPROG);
	else
	{
		str=m_pNextProg->strData1+"\n"+m_pNextProg->strName;
	}
	MultiByteConversion(str,wchar);

	format.SetTrimming(StringTrimmingEllipsisCharacter);
	format.SetLineAlignment(StringAlignmentCenter);
	
	graph.DrawImage(m_bmBack,0,rect.top);
	graph.DrawString(wchar,-1,g_font14Bold,RectF(6,39,(REAL)(rect.Width()-10),(REAL)(rect.Height()-33)),&format,&SolidBrush(Color(64,255,255,255)));
	graph.DrawString(wchar,-1,g_font14Bold,RectF(5,38,(REAL)(rect.Width()-10),(REAL)(rect.Height()-33)),&format,&SolidBrush(Color(255,255,255,255)));

	format.SetAlignment(StringAlignmentCenter);
	format.SetLineAlignment(StringAlignmentNear);
	MultiByteConversion(strTitle,wchar);
	graph.DrawString(wchar,-1,g_fontSmallTitle,PointF(75.0f,3.0f),&format,&SolidBrush(Color(255,180,180,180)) );
}

void CProgInfoWnd::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( !CheckKey(nChar) )
		CStatic::OnSysKeyUp(nChar, nRepCnt, nFlags);
}

void CProgInfoWnd::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( !CheckKey(nChar) )
		CStatic::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CProgInfoWnd::OnTimer(UINT nIDEvent) 
{
	CString strCrono;
	WCHAR	wchar[20];
	DWORD64 qwCurTime;
	CRect	rect;

	GetClientRect(&rect);

	if( m_pNextProg==NULL )
		strCrono="00:00:00.0";
	else
	{
		FILETIME	ftUTC;

		GetSystemTimeAsFileTime(&ftUTC);
		FileTimeToLocalFileTime(&ftUTC,(LPFILETIME)&qwCurTime);

		if( qwCurTime>m_qwStart )
			GetTimeString64(qwCurTime-m_qwStart,&strCrono);
		else
			GetTimeString64(m_qwStart-qwCurTime,&strCrono);

		strCrono.Delete(10,2);
	}

	MultiByteConversion(strCrono,wchar);

	Graphics		graph(m_bmCrono);
	StringFormat	format;

	format.SetLineAlignment(StringAlignmentCenter);
	format.SetAlignment(StringAlignmentCenter);

	graph.DrawImage(m_bmBack,0,0,rect.right-120,20,120,25,UnitPixel);
	graph.DrawString(wchar,-1,g_font24,PointF(62.0f,14.0f),&format,&SolidBrush(Color(128,0,0,0)));
	
	graph.DrawString(wchar,-1,g_font24,PointF(62.0f,14.0f),&format,&SolidBrush(Color(128,0,0,0)));
	graph.DrawString(wchar,-1,g_font24,PointF(60.0f,12.0f),&format,&SolidBrush(Color(255,220,220,220)));
	CClientDC	dc(this);
	Graphics	graphdc(dc);

	graphdc.DrawImage(m_bmCrono,15,25);

	if( m_pNextProg==NULL )
	{
		m_nCount++;
		if( m_nCount>100 )
		{
			m_nCount=0;
			OnRefresh();
		}

		return;
	}

	if( g_wAutomationMode != AUTOMATION_FULLAUTO )
	{
		if( (m_qwNextProg!=0) && (m_qwNextProg<qwCurTime+100000000) )
			OnRefresh();

		return;
	}

	if( g_wndLineUp==NULL )
		return;

	if( ( qwCurTime + ((CLineUpWnd *)g_wndLineUp)->GetPlayersTime() ) > (m_qwStart-50000000) )
	{
		int nCount=0;

		((CLineUpWnd *)g_wndLineUp)->RemoveLeftOvers();
		((CLineUpWnd *)g_wndLineUp)->m_pList->SetCurSel(-1);
		nCount=((CLineUpWnd *)g_wndLineUp)->m_pList->GetCount();
		((CLineUpWnd *)g_wndLineUp)->AddSchedule(m_pNextProg->lID,m_qwMinLength );

		if(nCount<((CLineUpWnd *)g_wndLineUp)->m_pList->GetCount())
		{
			// Schedule is not empty
			g_bIsAcceptingCommands=FALSE;
		}
		else
		{
			// Empty Schedule -> Enter remote mode
			g_bIsAcceptingCommands=g_bIsOnNetwork;
		}
		
		for( int i=0; i<4; i ++ )
			if( ((CLineUpWnd *)g_wndLineUp)->m_wndPlayer[3]->m_wPlayerState==STATE_UNCUED )
				((CLineUpWnd *)g_wndLineUp)->m_wndPlayer[3]->CmCue();

		m_qwStartPlaying = m_qwStart;

		GetNextProg();
	}

	if( (m_qwStartPlaying!=0) && ( (qwCurTime+((CLineUpWnd *)g_wndLineUp)->GetPlayersTime()) > m_qwStartPlaying) )
	{
		if( ((CLineUpWnd *)g_wndLineUp)->m_wndPlayer[0]->m_wPlayerState!=STATE_PLAYING )
			if( ((CLineUpWnd *)g_wndLineUp)->m_wndPlayer[0]->m_wPlayerState!=STATE_UNCUED )
				((CLineUpWnd *)g_wndLineUp)->m_wndPlayer[0]->CmPlay();
		m_qwStartPlaying=0;
	} 
}

void CProgInfoWnd::GetNextProg()
{
	CDatabase db;
	do{
		try {
			db.OpenEx("DSN="+m_strOnAirConnect,CDatabase::noOdbcDialog);
		}
		catch(...) {};
	}while( !db.IsOpen() );

	db.SetQueryTimeout(60);

	CRSScheduleHeadline rs( "",&db );
	m_qwNextProg=0;

	if( m_qwStart==0 )
	{
		COleDateTime	dt;

		dt=COleDateTime::GetCurrentTime();
		rs.m_strFilter.Format("Date > '%d-%d-%d %d:%d:%d'",dt.GetYear(),dt.GetMonth(),dt.GetDay(),dt.GetHour(),dt.GetMinute(),dt.GetSecond() );
	}
	else
	{
		SYSTEMTIME st;
		FileTimeToSystemTime( (FILETIME*)&m_qwStart,&st);
		rs.m_strFilter.Format("Date > '%d-%d-%d %d:%d:%d'",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
	}
	

	int nCount = m_ContentMenu->GetMenuItemCount();
	for( int I=0; I<nCount; I++ )
		m_ContentMenu->DeleteMenu(0,MF_BYPOSITION);

	rs.m_strSort="Date";

	do
	{
		try {
			rs.Open();
		}
		catch(...){};
	} while( !rs.IsOpen() );

	if( rs.GetRecordCount()==0 )
	{
		m_pNextProg=NULL;
		rs.Close();
		return;
	}

	rs.m_Name.TrimRight();

	CString str;

	str.Format("%d-%d-%d %d:%d:%d",rs.m_Date.GetYear(),rs.m_Date.GetMonth(),rs.m_Date.GetDay(),rs.m_Date.GetHour(),rs.m_Date.GetMinute(),rs.m_Date.GetSecond() );

	SYSTEMTIME	st;
	rs.m_Date.GetAsSystemTime(st);
	SystemTimeToFileTime(&st,(FILETIME *)&m_qwStart);
	
	if( rs.m_Priority== 1 )
	{
		rs.m_EndingDate.GetAsSystemTime(st);
		SystemTimeToFileTime(&st,(FILETIME*)&m_qwMinLength);
		m_qwMinLength -= m_qwStart;
	}
	else
		m_qwMinLength = 0;

	m_pNextProg = new typeArchiveItem(TYPE_SCHEDULE,rs.m_ID,rs.m_Name,0,str);
	
	CRSViewSchedule	rsView( "",&db );

	rsView.m_strFilter.Format("ScheduleID='%d'",m_pNextProg->lID);
	rsView.m_strSort = "ItemOrder";

	do
	{
		try 
		{
			rsView.Open();
		}
		catch(...) {};
	} while(!rsView.IsOpen());

	int I=0;

	while( !rsView.IsEOF() )
	{
		rsView.m_Type.TrimRight();
		rsView.m_Name.TrimRight();

		m_ContentMenu->AppendMenu(MF_STRING,2000+I,rsView.m_Type+" - "+rsView.m_Name);

		switch( rsView.m_ItemType )
		{
		case TYPE_SPOT:
			m_ContentMenu->SetMenuItemBitmaps(2000+I,MF_BYCOMMAND,m_bmSpot,m_bmSpot);
			break;
		case TYPE_JINGLE:
			m_ContentMenu->SetMenuItemBitmaps(2000+I,MF_BYCOMMAND,m_bmJingle,m_bmJingle);
			break;
		case TYPE_MUSIC:
			m_ContentMenu->SetMenuItemBitmaps(2000+I,MF_BYCOMMAND,m_bmMusic,m_bmMusic);
			break;
		case TYPE_RM:
			m_ContentMenu->SetMenuItemBitmaps(2000+I,MF_BYCOMMAND,m_bmRM,m_bmRM);
			break;
		case TYPE_TIMESIGNAL:
			m_ContentMenu->SetMenuItemBitmaps(2000+I,MF_BYCOMMAND,m_bmTime,m_bmTime);
			break;
		case TYPE_VOICEINSERT:
			m_ContentMenu->SetMenuItemBitmaps(2000+I,MF_BYCOMMAND,m_bmVoice,m_bmVoice);
			break;
		}	

		rsView.MoveNext();
		I++;
	}

	rs.MoveNext();

	if( !rs.IsEOF() )
	{
		rs.m_Date.GetAsSystemTime(st);
		SystemTimeToFileTime(&st,(FILETIME *)&m_qwNextProg);
	}

	Invalidate();
}

void CProgInfoWnd::OnRButtonUp(UINT nFlags, CPoint point) 
{
	CRect Rect;
	GetWindowRect( &Rect );
	
	m_Menu->TrackPopupMenu(TPM_LEFTALIGN,point.x+Rect.left,point.y+Rect.top,this);
}


void CProgInfoWnd::OnRefresh()
{
	m_qwStart = 0;
	GetNextProg();
	Invalidate();
}

void CProgInfoWnd::OnLineUp()
{
	if( m_pNextProg==NULL )
		return;

	((CLineUpWnd *)g_wndLineUp)->AddSchedule(m_pNextProg->lID);
	GetNextProg();
	Invalidate();
}

void CProgInfoWnd::OnSkip()
{
	GetNextProg();
	Invalidate();
}