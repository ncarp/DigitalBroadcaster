// TrafficInfoWnd.cpp : implementation file
//

#include "stdafx.h"

#include <gdiplus.h>
using namespace Gdiplus;

//#include "..\include\utils.h"

#include "OnAir.h"
#include "TrafficInfoWnd.h"
#include "ExternalObjects.h"
#include "typeLineUpItem.h"
#include "..\common\include\defines.h"
#include "..\common\include\utils.h"
#include "..\include\RSBlocksDefinition.h"
#include "..\common\include\splitter_utils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define CRONO_WIDTH	120
#define	ID_TIMER_PAINT	1
#define ID_TIMER_TIME	2

/////////////////////////////////////////////////////////////////////////////
// CTrafficInfoWnd

CTrafficInfoWnd::CTrafficInfoWnd()
{
	m_pNextBlock=NULL;
	m_qwLastBlock=0;
	m_strInfo.LoadString(IDS_NOBLOCK);

	m_Menu=new CMenu();
	m_Menu->CreatePopupMenu();

	m_ContentMenu = new CMenu();
	m_ContentMenu->CreatePopupMenu();

	CString str;

	str.LoadString(IDS_REFRESH);
	m_Menu->AppendMenu(MF_STRING,CM_REFRESH,str);
	m_Menu->AppendMenu(MF_SEPARATOR);

	str.LoadString(IDS_MENULINEUP);
	m_Menu->AppendMenu(MF_STRING,CM_LINEUP,str);
	m_Menu->AppendMenu(MF_SEPARATOR);

	str.LoadString(IDS_MENUDELAY1);
	m_Menu->AppendMenu(MF_STRING,CM_DELAY1,str);

	str.LoadString(IDS_MENUDELAY2);
	m_Menu->AppendMenu(MF_STRING,CM_DELAY2,str);

	str.LoadString(IDS_MENUDELAY5);
	m_Menu->AppendMenu(MF_STRING,CM_DELAY5,str);
	m_Menu->AppendMenu(MF_SEPARATOR);

	str.LoadString(IDS_MENUSKIPBLOCK);
	m_Menu->AppendMenu(MF_STRING,CM_SKIP,str);

	m_Menu->AppendMenu(MF_POPUP,(UINT)m_ContentMenu->m_hMenu,"Conteudo");
	m_strOnAirConnect=g_strOnAirConnect;
}

CTrafficInfoWnd::~CTrafficInfoWnd()
{
}


BEGIN_MESSAGE_MAP(CTrafficInfoWnd, CStatic)
	//{{AFX_MSG_MAP(CTrafficInfoWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SYSKEYUP()
	ON_WM_KEYUP()
	ON_WM_TIMER()
	ON_WM_SYSCOLORCHANGE()
	ON_WM_RBUTTONUP()
	ON_COMMAND( CM_REFRESH, OnRefresh )
	ON_COMMAND( CM_LINEUP, OnLineUp )
	ON_COMMAND( CM_DELAY1, OnDelay1 )
	ON_COMMAND( CM_DELAY2, OnDelay2 )
	ON_COMMAND( CM_DELAY5, OnDelay5 )
	ON_COMMAND( CM_SKIP, OnSkip )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrafficInfoWnd message handlers

void CTrafficInfoWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	Graphics	graph(dc);
	CString		strTitle;
	CRect		rect;

	GetClientRect(&rect);
	
	strTitle.LoadString(IDS_NEXTBLOCK);

	WCHAR wchar[200];

	MultiByteConversion(m_strInfo,wchar);

	StringFormat format;
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

int CTrafficInfoWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;

	CClientDC	dc(this);

	SetCronoBitmap(&dc);
	SetBackBitmap(&dc);
	OnSysColorChange();

	m_bmSpot = new CBitmap();
	m_bmSpot->LoadBitmap( IDB_SPOT );

	m_bmJingle = new CBitmap();
	m_bmJingle->LoadBitmap( IDB_JINGLESMALL );

	if( m_strOnAirConnect!="" )
	{
		SetTimer(ID_TIMER_PAINT,90,NULL);
		SetTimer(ID_TIMER_TIME,10,NULL);

		GetNextBlock();
		Sync();
	}

	return 0;
}

void CTrafficInfoWnd::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( nChar==VK_F10 )
		g_wndCartwall->SendMessage(UM_PLAYCART, nChar );
	else
		CStatic::OnSysKeyUp(nChar, nRepCnt, nFlags);
}

void CTrafficInfoWnd::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( (nChar>=VK_F1) && (nChar<=VK_F12) )
		g_wndCartwall->SendMessage(UM_PLAYCART,nChar);
	else
		CStatic::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CTrafficInfoWnd::OnTimer(UINT nIDEvent )
{
	switch( nIDEvent )
	{
	case ID_TIMER_PAINT:
		PaintCrono();
		break;
	case ID_TIMER_TIME:
		CheckBlockEntry();
		break;
	}
}

void CTrafficInfoWnd::PaintCrono() 
{
	CString strCrono;
	WCHAR	wchar[20];
	CRect	rect;
	DWORD64	qwCurTime=0;

	GetClientRect(&rect);

	if( m_pNextBlock==NULL )
		strCrono="00:00:00.0";
	else
	{
		FILETIME	ftUTC;

		GetSystemTimeAsFileTime(&ftUTC);
		FileTimeToLocalFileTime(&ftUTC,(LPFILETIME)&qwCurTime);

		if( qwCurTime>m_qwBlockTime )
			GetTimeString64((qwCurTime-m_qwBlockTime),&strCrono);
		else
			GetTimeString64((m_qwBlockTime-qwCurTime),&strCrono);

		strCrono.Delete(10,2);
	}

	MultiByteConversion(strCrono,wchar);

	Graphics graph(m_bmCrono);
	StringFormat	format;

	format.SetLineAlignment(StringAlignmentCenter);
	format.SetAlignment(StringAlignmentCenter);

	graph.DrawImage(m_bmBack,0,0,15,25,120,25,UnitPixel);
	graph.DrawString(wchar,-1,g_font24,PointF(62.0f,14.0f),&format,&SolidBrush(Color(128,0,0,0)));

	if( m_qwBlockTime<qwCurTime )
		graph.DrawString(wchar,-1,g_font24,PointF(60.0f,12.0f),&format,&SolidBrush(Color(255,250,0,0)));
	else if( (m_qwBlockTime-qwCurTime) < 100000000 )
		graph.DrawString(wchar,-1,g_font24,PointF(60.0f,12.0f),&format,&SolidBrush(Color(255,250,0,0)));
	else if( (m_qwBlockTime-qwCurTime) < 3000000000 )
		graph.DrawString(wchar,-1,g_font24,PointF(60.0f,12.0f),&format,&SolidBrush(Color(255,250,250,0)));
	else
		graph.DrawString(wchar,-1,g_font24,PointF(60.0f,12.0f),&format,&SolidBrush(Color(255,0,250,0)));

	CClientDC	dc(this);
	Graphics	graphdc(dc);

	//	graphdc.DrawImage(m_bmBack,0,rect.top);
	graphdc.DrawImage(m_bmCrono,15,25);
}

void CTrafficInfoWnd::SetCronoBitmap(CClientDC *dc)
{
	m_bmCrono = ::new Bitmap(CRONO_WIDTH,25,PixelFormat32bppARGB);
}

void CTrafficInfoWnd::SetBackBitmap(CClientDC *dc)
{
	CRect				rect;
	GetClientRect(&rect);

	Graphics			graphdc(*dc);
	m_bmBack = ::new Bitmap(rect.right,rect.Height(),&graphdc);
}

void CTrafficInfoWnd::OnSysColorChange() 
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
	Graphics			graph(m_bmBack);

	graph.FillPath(&brushBack,&pathBack);
	graph.FillPath(&brushLight,&pathLight);
	graph.FillPath(&brushDark,&pathDark);
		
}

UINT CTrafficInfoWnd::GetNextBlockThread( LPVOID lp)
{
	CTrafficInfoWnd *T = (CTrafficInfoWnd *)lp;
	T->GetNextBlock();
	return 0;
}

void CTrafficInfoWnd::GetNextBlock()
{
#ifdef __DEBUG_LOG
	WriteLogFile("CTraffciInfoWnd::GetNextBlock (Enter)");
#endif
	COleDateTime		StartDate;
	COleDateTimeSpan	OneDay(1,0,0,0);
	CString				Days[7]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"},
						strTemp;
	long				lCurrentTime,
						lHour,
						lMinute,
						lSecond;
	DWORD64				qwBlockTime;
	SYSTEMTIME			st;
	FILETIME			ft;
	CDatabase			db;

	do{
		try {
			db.OpenEx("DSN="+m_strOnAirConnect,CDatabase::noOdbcDialog);
		}
		catch(...) {};
	}while( !db.IsOpen() );

	db.SetQueryTimeout(360);


 	m_pNextBlock = NULL;

	if( m_qwLastBlock<=0 )
	{
		StartDate=COleDateTime::GetCurrentTime();
	}
	else
	{
		LocalFileTimeToFileTime((LPFILETIME)&m_qwLastBlock,&ft);
//		memcpy(&ft,&m_qwLastBlock,sizeof(FILETIME));
		StartDate = COleDateTime(ft);
	}
	lHour=StartDate.GetHour();
	lMinute=StartDate.GetMinute();
	lSecond=StartDate.GetSecond();

	strTemp.Format("%d:%d:%d",lHour,lMinute,lSecond);
//	AfxMessageBox(strTemp);

	lCurrentTime = lHour*3600000+lMinute*60000+lSecond*1000+999;

	CRSBlocksDefinition rs("",&db);
	rs.m_strFilter.Format("%s = '1' AND Time > '%d' AND Sponsor = 0",Days[StartDate.GetDayOfWeek()-1],lCurrentTime);
	rs.m_strSort = "Time";

	do
	{
		try {
			rs.Open();
		}catch(...) {};
	} while( !rs.IsOpen() );

	if( rs.GetRecordCount() )
	{
		st.wYear=StartDate.GetYear();
		st.wMonth=StartDate.GetMonth();
		st.wDay=StartDate.GetDay();
		st.wHour=0;
		st.wMinute=0; 
		st.wSecond=0;
		st.wMilliseconds=0;
		SystemTimeToFileTime(&st,(LPFILETIME)(&qwBlockTime));

		qwBlockTime+=(DWORD64)rs.m_Time*10000;
		m_qwLastBlock=qwBlockTime;

		m_pNextBlock=new typeLineUpItem(TYPE_BLOCK,rs.m_ID,qwBlockTime,m_strOnAirConnect);

		if( m_pNextBlock->m_iBlockSize== 0 )
			GetNextBlock();
	}
	else
	{
		for( int I=0; I<7; I++ )
		{
			StartDate = StartDate+OneDay;
			rs.m_strFilter.Format("%s = '1' AND Sponsor = 0",Days[StartDate.GetDayOfWeek()-1]);

			try {
				rs.Requery();
			} catch(...) {};

			if( rs.GetRecordCount() )
			{
				st.wYear=StartDate.GetYear();
				st.wMonth=StartDate.GetMonth();
				st.wDay=StartDate.GetDay();
				st.wHour=0;
				st.wMinute=0;
				st.wSecond=0;
				st.wMilliseconds=0;
				SystemTimeToFileTime(&st,(LPFILETIME)(&qwBlockTime));

				qwBlockTime+=(DWORD64)rs.m_Time*10000;
				m_qwLastBlock=qwBlockTime;

				m_pNextBlock=new typeLineUpItem(TYPE_BLOCK,rs.m_ID,qwBlockTime,m_strOnAirConnect);

				if( m_pNextBlock->m_iBlockSize== 0 )
					GetNextBlock();
				break;
			}
		}
	}
	rs.Close();

	if( (m_pNextBlock!=NULL) && (g_nSplitters>0) )
	{
		typeSplitterMsg	Msg;

		memset(&Msg,0,SIZEOFSPLITTERMSG);
		Msg.wAction	= SP_OPEN;
		Msg.wType	= TYPE_BLOCK;
		Msg.lID		= m_pNextBlock->m_lItemID;
		Msg.wFinish	= m_pNextBlock->m_wPrecision;
		Msg.lTime	= m_pNextBlock->m_lBlockTime;
		Msg.lLength	= m_pNextBlock->m_lEndPos;
		strcpy(Msg.strDate,m_pNextBlock->m_strName);

		wsprintf(Msg.pstrMessage,"Open Block - %s - %s",m_pNextBlock->m_strName,m_pNextBlock->m_strName2);
		SendSplitterMessage(&Msg);
	}

	Invalidate();
#ifdef __DEBUG_LOG
	WriteLogFile("CTrafficInfoWnd::CheckBlockEntry (Exit)");
#endif
}

void CTrafficInfoWnd::CheckBlockEntry() 
{
	if( g_wAutomationMode==AUTOMATION_MANUAL )
		return;

	if( m_pNextBlock==NULL )
		return;

	if( g_wndLineUp==NULL )
		return;

	FILETIME	ft;
	DWORD64		qwTime;

	GetSystemTimeAsFileTime(&ft);
	FileTimeToLocalFileTime(&ft,(LPFILETIME)&qwTime);
//	qwTime+=g_wndLineUp->GetPlayersTime()+100000000;

//	if( !g_wndLineUp->m_pList->GetCount() )
//	{
		if( ((CLineUpWnd *)g_wndLineUp)->m_wndPlayer[0]->m_wPlayerState!=STATE_UNCUED )
		{
			if( !((CLineUpWnd *)g_wndLineUp)->m_pList->GetCount() )

			{
				qwTime+=((CLineUpWnd *)g_wndLineUp)->GetPlayersTime();
				if( qwTime > m_pNextBlock->m_qwStartTime )
				{
					CString strTemp = m_pNextBlock->m_strName2;

					if( m_pNextBlock->m_wPrecision!=3 )
						((CLineUpWnd *)g_wndLineUp)->CutOnPlayer( (long)((qwTime-m_pNextBlock->m_qwStartTime)/10000) );

					((CLineUpWnd *)g_wndLineUp)->m_pList->InsertString(0,(LPCTSTR)m_pNextBlock);
					// Send Message to Splitter -------------------------------------------------------
					if( g_nSplitters>0 )
					{
						typeSplitterMsg	Msg;

						memset(&Msg,0,SIZEOFSPLITTERMSG);
						Msg.wAction	= SP_CUE;
						Msg.wType	= TYPE_BLOCK;
						Msg.lID		= m_pNextBlock->m_lItemID;
						Msg.wFinish	= m_pNextBlock->m_wPrecision;
						Msg.lLength	= m_pNextBlock->m_lEndPos;

						wsprintf(Msg.pstrMessage,"Cue Block: %s - %s",m_pNextBlock->m_strName,m_pNextBlock->m_strName2);
						SendSplitterMessage(&Msg);
					}
				
					while( (((CLineUpWnd *)g_wndLineUp)->m_pList->GetCount()) && (((CLineUpWnd *)g_wndLineUp)->m_wndPlayer[3]->m_wPlayerState==STATE_UNCUED) )
						((CLineUpWnd *)g_wndLineUp)->m_wndPlayer[3]->CmCue();

					if( (((CLineUpWnd *)g_wndLineUp)->m_wndPlayer[0]->m_wPlayerState==STATE_CUED) && (m_bAutoStartBlock) )
						((CLineUpWnd *)g_wndLineUp)->m_wndPlayer[0]->CmPlay();
					
					// Log Item -----------------------------------------------------------------------
					typeLogItem *lpLog=new typeLogItem;
					lpLog->wType = 0;
					lpLog->lID = 0;
					lpLog->lTraffic = 0;
					wsprintf(lpLog->strName,"--> Block auto inserted  - %s",strTemp);
					g_wndAired->LogItem(lpLog);
					// --------------------------------------------------------------------------------

					GetNextBlockThread( (LPVOID)this );
				}
			}
		}
		else
		{
			qwTime+=((CLineUpWnd *)g_wndLineUp)->GetPlayersTime()+100000000;
			if( qwTime > m_pNextBlock->m_qwStartTime )
			{
				CString strTemp = m_pNextBlock->m_strName2;

				((CLineUpWnd *)g_wndLineUp)->m_pList->InsertString(0,(LPCTSTR)m_pNextBlock);

				// Send Message to Splitter ----------------------------------------------------------
				if( g_nSplitters>0 )
				{
					typeSplitterMsg	Msg;

					memset(&Msg,0,SIZEOFSPLITTERMSG);
					Msg.wAction	= SP_CUE;
					Msg.wType	= TYPE_BLOCK;
					Msg.lID		= m_pNextBlock->m_lItemID;
					Msg.wFinish	= m_pNextBlock->m_wPrecision;
					Msg.lLength	= m_pNextBlock->m_lEndPos;

					wsprintf(Msg.pstrMessage,"Cue Block: %s - %s",m_pNextBlock->m_strName,m_pNextBlock->m_strName2);
					SendSplitterMessage(&Msg);
				}
	
				while( (((CLineUpWnd *)g_wndLineUp)->m_pList->GetCount()) && (((CLineUpWnd *)g_wndLineUp)->m_wndPlayer[3]->m_wPlayerState==STATE_UNCUED) )
					((CLineUpWnd *)g_wndLineUp)->m_wndPlayer[3]->CmCue();

				// Log Item -----------------------------------------------------------------------
				typeLogItem *lpLog=new typeLogItem;
				lpLog->wType = 0;
				lpLog->lID = 0;
				lpLog->lTraffic = 0;
				wsprintf(lpLog->strName,"--> Block auto inserted 2 - %s",strTemp);
				g_wndAired->LogItem(lpLog);
				// --------------------------------------------------------------------------------

				GetNextBlockThread( (LPVOID)this );
			}
		}
//	}

	GetSystemTimeAsFileTime(&ft);
	FileTimeToLocalFileTime(&ft,(LPFILETIME)&qwTime);

	if( (qwTime > m_qwBlockTime) && (m_bAutoStartBlock) )
		if( (((CLineUpWnd *)g_wndLineUp)->m_wndPlayer[0]->m_wPlayerState!=STATE_PLAYING) && (((CLineUpWnd *)g_wndLineUp)->m_wndPlayer[0]->m_wPlayerState==STATE_CUED) )
		{
			((CLineUpWnd *)g_wndLineUp)->m_wndPlayer[0]->CmPlay();
			// Log Item -----------------------------------------------------------------------
			typeLogItem *lpLog=new typeLogItem;
			lpLog->wType = 0;
			lpLog->lID = 0;
			lpLog->lTraffic = 0;
			strcpy(lpLog->strName,"--> Block auto Start");
			g_wndAired->LogItem(lpLog);
			// --------------------------------------------------------------------------------
		}

}

void CTrafficInfoWnd::Sync()
{
#ifdef __DEBUG_LOG
	WriteLogFile("CTrafficInfo::Sync (Enter)");
#endif
	if( m_pNextBlock!=NULL )
	{
		CString str;
		str.LoadString(IDS_STARTEXACT+m_pNextBlock->m_wPrecision-1);

		m_qwBlockTime = m_pNextBlock->m_qwStartTime;
		m_strInfo = str+"\n"+m_pNextBlock->m_strName2;
		m_bAutoStartBlock = (m_pNextBlock->m_wPrecision!=3);
		
		int nCount = m_ContentMenu->GetMenuItemCount();
		for( int I=0; I<nCount; I++ )
			m_ContentMenu->DeleteMenu(0,MF_BYPOSITION);

		for( int I=0; I<m_pNextBlock->m_iBlockSize; I++ )
		{
			typeLineUpItem *lpItem = (typeLineUpItem *)m_pNextBlock->m_pBlock[I];
			if( lpItem!=NULL )
			{
				m_ContentMenu->AppendMenu(MF_STRING,2000+I,lpItem->m_strName+" - "+lpItem->m_strName2);

				switch( lpItem->m_wType )
				{
				case TYPE_SPOT:
					m_ContentMenu->SetMenuItemBitmaps(2000+I,MF_BYCOMMAND,m_bmSpot,m_bmSpot);
					break;
				case TYPE_JINGLE:
					m_ContentMenu->SetMenuItemBitmaps(2000+I,MF_BYCOMMAND,m_bmJingle,m_bmJingle);
					break;
				}
			}
		}
		Invalidate();
	}
#ifdef __DEBUG_LOG
	WriteLogFile("CTrafficInfo::Sync (Exit)");
#endif
}

void CTrafficInfoWnd::OnRButtonUp(UINT nFlags, CPoint point) 
{
	CRect Rect;
	GetWindowRect( &Rect );
	
	m_Menu->TrackPopupMenu(TPM_LEFTALIGN,point.x+Rect.left,point.y+Rect.top,this);
}

void CTrafficInfoWnd::OnRefresh()
{
#ifdef __DEBUG_LOG
	WriteLogFile("CTrafficInfo::OnRefresh (Enter)");
#endif
	if( m_qwLastBlock!=0 )
		m_qwLastBlock-=10000000;

	GetNextBlock();
	Sync();

	// Log Item -----------------------------------------------------------------------
	typeLogItem *lpLog=new typeLogItem;
	lpLog->wType = 0;
	lpLog->lID = 0;
	lpLog->lTraffic = 0;
	strcpy(lpLog->strName,"--> Block Refresh");
	g_wndAired->LogItem(lpLog);
	// --------------------------------------------------------------------------------

#ifdef __DEBUG_LOG
	WriteLogFile("CTrafficInfo::OnRefresh (Exit)");
#endif
}

void CTrafficInfoWnd::OnLineUp()
{
#ifdef __DEBUG_LOG
	WriteLogFile("CTrafficInfo::OnLineUp (Enter)");
#endif
	if( m_pNextBlock==NULL )
		return;

	if( g_wndLineUp==NULL )
		return;

	int nPos=((CLineUpWnd *)g_wndLineUp)->m_pList->GetCurSel();

	if( nPos==LB_ERR ) nPos=0;

	((CLineUpWnd *)g_wndLineUp)->m_pList->InsertString(nPos,(LPCTSTR)m_pNextBlock);
	((CLineUpWnd *)g_wndLineUp)->CalcStartingTimes();

	GetNextBlockThread( (LPVOID)this );

	// Log Item -----------------------------------------------------------------------
	typeLogItem *lpLog=new typeLogItem;
	lpLog->wType = 0;
	lpLog->lID = 0;
	lpLog->lTraffic = 0;
	wsprintf(lpLog->strName,"--> Block Lined up - %s",m_pNextBlock->m_strName2);
	g_wndAired->LogItem(lpLog);
	// --------------------------------------------------------------------------------

#ifdef __DEBUG_LOG
	WriteLogFile("CTrafficInfo::OnLineUp (Exit)");
#endif
}

void CTrafficInfoWnd::OnDelay1() 
{
	if( !g_bUserCanDelayBlocks )
		return;

	if( m_pNextBlock==NULL )
		return;

	// Log Item -----------------------------------------------------------------------
	typeLogItem *lpLog=new typeLogItem;
	lpLog->wType = 0;
	lpLog->lID = 0;
	lpLog->lTraffic = 0;
	wsprintf(lpLog->strName,"--> Block delayed 1 minute - %s",m_pNextBlock->m_strName2);
	g_wndAired->LogItem(lpLog);
	// --------------------------------------------------------------------------------

	m_qwBlockTime += 600000000;
}

void CTrafficInfoWnd::OnDelay2() 
{
	if( !g_bUserCanDelayBlocks )
		return;

	if( m_pNextBlock==NULL )
		return;

	m_qwBlockTime += 1200000000;

	// Log Item -----------------------------------------------------------------------
	typeLogItem *lpLog=new typeLogItem;
	lpLog->wType = 0;
	lpLog->lID = 0;
	lpLog->lTraffic = 0;
	wsprintf(lpLog->strName,"--> Block delayed 2 minutes - %s"+m_pNextBlock->m_strName2);
	g_wndAired->LogItem(lpLog);
	// --------------------------------------------------------------------------------
}

void CTrafficInfoWnd::OnDelay5() 
{
	if( !g_bUserCanDelayBlocks )
		return;

	if( m_pNextBlock==NULL )
		return;

	m_qwBlockTime += 3000000000;

	// Log Item -----------------------------------------------------------------------
	typeLogItem *lpLog=new typeLogItem;
	lpLog->wType = 0;
	lpLog->lID = 0;
	lpLog->lTraffic = 0;
	wsprintf(lpLog->strName,"--> Block delayed 5 minutes - %s",m_pNextBlock->m_strName2);
	g_wndAired->LogItem(lpLog);
	// --------------------------------------------------------------------------------
}

void CTrafficInfoWnd::OnSkip()
{
	if( !g_bUserCanDelayBlocks )
		return;

	if( m_pNextBlock==NULL )
		return;

//	m_qwLastBlock = m_pNextBlock->m_qwStartTime;
	GetNextBlock();
	Sync();

	// Log Item -----------------------------------------------------------------------
	typeLogItem *lpLog=new typeLogItem;
	lpLog->wType = 0;
	lpLog->lID = 0;
	lpLog->lTraffic = 0;
	wsprintf(lpLog->strName,"--> Block Skiped - %s",m_pNextBlock->m_strName2);
	g_wndAired->LogItem(lpLog);
	// --------------------------------------------------------------------------------
}