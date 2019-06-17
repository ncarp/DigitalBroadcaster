// OnAirPlayerWnd.cpp : implementation file
//

#include "stdafx.h"

#include <gdiplus.h>
using namespace Gdiplus;

#include "ExternalObjects.h"
#include "..\common\include\utils.h"
#include "..\common\include\defines.h"

#include "OnAir.h"
#include "OnAirPlayerWnd.h"
#include "VolumeSlider.h"
#include "PlayerOptionsWnd.h"
#include "PlayerButton.h"
#include "..\common\include\splitter_utils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ID_VOLUME	1001
#define	ID_CUE		1002
#define ID_PLAY		1003
#define ID_STOP		1004
#define ID_MIX		1005
#define ID_UNCUE	1006

extern LPDIRECTSOUND lpDS_MAIN;

/////////////////////////////////////////////////////////////////////////////
// COnAirPlayerWnd

COnAirPlayerWnd::COnAirPlayerWnd()
{
	m_lpItem = NULL;
	m_bmName = NULL;
	m_bmCrono = NULL;
	m_pDS_Main = lpDS_MAIN;
}

COnAirPlayerWnd::~COnAirPlayerWnd()
{
}


BEGIN_MESSAGE_MAP(COnAirPlayerWnd, CStatic)
	//{{AFX_MSG_MAP(COnAirPlayerWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_COMMAND( ID_CUE,CmCue )
	ON_COMMAND( ID_PLAY,CmPlay )
	ON_COMMAND( ID_STOP,CmStop )
	ON_COMMAND( ID_MIX,CmMix ) 
	ON_COMMAND( ID_UNCUE,OnUnCue )
	ON_MESSAGE( UM_SETPAUSE,OnSetPause )
	ON_MESSAGE( UM_SETLOOP,OnSetLoop )
	ON_MESSAGE( UM_DROP,OnDrop ) 
	ON_MESSAGE( UM_CANDROP,OnCanDrop )
	ON_MESSAGE( UM_VOLUMECHANGE,OnVolumeChange )
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COnAirPlayerWnd message handlers

int COnAirPlayerWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect	rect;
	GetClientRect(&rect);

	//////////////////////////////////////////////////////////////////////////
	//	Volume slider creation
	m_pVolume = new CVolumeSlider();
	m_pVolume->Create(NULL,SS_NOTIFY|WS_VISIBLE,CRect(0,50,rect.right-125,75),this);

	//////////////////////////////////////////////////////////////////////////
	//	Options window
	m_pOptions = new CPlayerOptionsWnd();
	m_pOptions->Create(NULL,WS_VISIBLE,CRect(rect.right-125,50,rect.right-75,75),this);

	///////////////////////////////////////////////////////////////////////
	//	Cue Button
	m_pCue = new CPlayerButton();
	m_pCue->Create("",WS_VISIBLE|BS_OWNERDRAW,CRect(0,0,0,0),this,ID_CUE);
	m_pCue->SetImageList(75,50,0,3);
	m_pCue->AddImage(IDB_CUE);

	////////////////////////////////////////////////////////////////////////
	//	Play Button
	m_pPlay = new CPlayerButton();
	m_pPlay->Create("",WS_VISIBLE|BS_OWNERDRAW,CRect(0,0,0,0),this,ID_PLAY);
	m_pPlay->SetImageList(50,50,0,1);
	m_pPlay->AddImage(IDB_PLAY);

	////////////////////////////////////////////////////////////////////////
	//	UnCue Button
	m_pUnCue = new CPlayerButton();
	m_pUnCue->Create("",WS_VISIBLE|BS_OWNERDRAW,CRect(0,0,0,0),this,ID_UNCUE);
	m_pUnCue->SetImageList(50,50,0,1);
	m_pUnCue->AddImage(IDB_UNCUE);

	////////////////////////////////////////////////////////////////////////
	//	Stop Button
	m_pStop = new CPlayerButton();
	m_pStop->Create("",WS_VISIBLE|BS_OWNERDRAW,CRect(0,0,0,0),this,ID_STOP);
	m_pStop->SetImageList(50,50,0,1);
	m_pStop->AddImage(IDB_STOP,RGB(252,252,252));

	////////////////////////////////////////////////////////////////////////
	//	Mix Button
	m_pMix = new CPlayerButton();
	m_pMix->Create("",WS_VISIBLE|BS_OWNERDRAW,CRect(0,0,0,0),this,ID_MIX);
	m_pMix->SetImageList(50,50,0,1);
	m_pMix->AddImage(IDB_MIX,RGB(252,252,252));

	m_DropTarget.Register(this);
	
	PaintBM();

	SetTimer(69,500,NULL);

	return 0;
}

void COnAirPlayerWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CRect	rect;
	GetClientRect(&rect);

	dc.FillRect(&rect,&CBrush(GetSysColor(COLOR_3DFACE)) );
	rect.DeflateRect(rect.right-150,0,0,0);

	dc.Draw3dRect(0,0,rect.right-151,50,RGB(255,255,255),RGB(128,128,128));
	dc.Draw3dRect(&rect,RGB(255,255,255),RGB(128,128,128));
	
	PaintBM();
	PaintCrono();
	DrawPlayer();
}

void COnAirPlayerWnd::OnSize(UINT nType, int cx, int cy) 
{
	CStatic::OnSize(nType, cx, cy);

	m_pVolume->MoveWindow(0,50,cx-221,25);
	m_pOptions->MoveWindow(cx-221,50,70,25);
	m_pCue->MoveWindow(cx-149,1,145,73);

	/////////////////////////////////////////////////////////////////////////
	//	bitmap creation
	SAFE_DELETE( m_bmName );
	SAFE_DELETE( m_bmCrono );

	GetClientRect(&m_rect);
	
	CClientDC	dc(this);
	Graphics	graph(dc);

	m_bmName = ::new Bitmap(cx-155,48,&graph);
	
	Graphics	graphbm(m_bmName);
	graphbm.Clear(Color(198,255,255,255));

	m_bmCrono = ::new Bitmap(69,48,&graph);
}

void COnAirPlayerWnd::CmCue()
{
#ifdef __DEBUG_LOG
	WriteLogFile("COnAirPlayerWnd::CmCue (Enter)");
#endif
	typeLineUpItem*	lpItem=NULL;
	if( g_wndLineUp!=NULL )
		lpItem = ((CLineUpWnd *)g_wndLineUp)->GetFirstItem();
	else
		lpItem = (typeLineUpItem *)GetParent()->SendMessage(UM_GETNEXTITEM);

	if( lpItem==NULL )
		return;

	m_lpItem=lpItem;

#ifdef __DEBUG_LOG
	CString strLog;
	strLog.Format("(%d - %s - %s)",m_lpItem->m_wType,m_lpItem->m_strName,m_lpItem->m_strName2);
	WriteLogFile("COnAirPlayerWnd::CmCue (FirstItem) "+strLog);
#endif

	if( m_lpItem->m_Sound==NULL )
	{
#ifdef __DEBUG_LOG
		WriteLogFile("COnAirPlayerWnd::CmCue (CueSound) "+strLog);
#endif
		m_lpItem->m_Sound=new CAudioStream(m_pDS_Main,this);

		if( m_lpItem->m_wType == TYPE_TIMESIGNAL )
		{
			m_lpItem->SetTimeFile();
		}

		m_lpItem->m_Sound->SetFile( m_lpItem->m_strFileName.GetBuffer(0) );
		m_lpItem->m_bmSpectrum	= CreateSpectrum();
		m_lpItem->m_Sound->m_pbm= m_lpItem->m_bmSpectrum;
		m_lpItem->m_Sound->m_xres	= m_xres;

		if( m_lpItem->m_Sound->CueSound() == S_OK )
		{
			m_lpItem->m_Sound->SetPosition(m_lpItem->m_lStartPos);
			m_lpItem->m_wState = STATE_CUED;

			if( m_lpItem->m_lFadeInPos > m_lpItem->m_lStartPos )
				m_lpItem->m_Sound->SetVolume(-3000);
			else
				m_lpItem->m_Sound->SetVolume(0);

			m_pVolume->SetVolume( m_lpItem->GetVolume() );

			if( (g_nSplitters>0) && (m_lpItem->m_lBlockPos==0) && (m_lpItem->m_bBlock))
			{
				typeSplitterMsg	Msg;
				CString			strTime;

				GetTimeString(m_lpItem->m_lBlockTime,&strTime);

				memset(&Msg,0,SIZEOFSPLITTERMSG);
				Msg.wAction	= SP_CUE;
				Msg.wType	= TYPE_BLOCK;
				Msg.wFinish = (WORD)m_lpItem->m_lBlockFinish;
				Msg.lTime	= m_lpItem->m_lBlockTime;
				Msg.lLength = m_lpItem->m_lBlockLength;
				
				wsprintf(Msg.pstrMessage,"Cue Block: %s",strTime);
				SendSplitterMessage(&Msg);
			}			
		}
		else
		{
			SAFE_DELETE( m_lpItem->m_Sound );
		}
	}

	if( m_lpItem->m_Sound == NULL )
	{
#ifdef __DEBUG_LOG
		WriteLogFile("COnAirPlayerWnd::CmCue (CueFailes) "+strLog);
#endif
		// Log Item -----------------------------------------------------------------------
		typeLogItem *lpLog=new typeLogItem;
		lpLog->wType = 0;
		lpLog->lID = 0;
		lpLog->lTraffic = 0;
		wsprintf(lpLog->strName,"--> Error on CUE - %s - %s",m_lpItem->m_strName,m_lpItem->m_strName2);
		if( g_wndAired!=NULL )
			g_wndAired->LogItem(lpLog);
		// --------------------------------------------------------------------------------

		SAFE_DELETE( m_lpItem );
		CmCue();

		return;
	}

	if( (g_wAutomationMode==AUTOMATION_FULLAUTO) )
	{
		m_lpItem->m_bLoop	= FALSE;
		m_lpItem->m_bPause	= FALSE;
		m_pOptions->Reset();
	}
	else
	{
		m_pOptions->m_pLoop->m_bLight = lpItem->m_bLoop;
		m_pOptions->m_pPause->m_bLight = lpItem->m_bPause;
		m_pOptions->m_pLoop->Invalidate();
		m_pOptions->m_pPause->Invalidate();
	}

	m_lpItem->m_Sound->SetPosition( m_lpItem->m_lStartPos);

	m_wPlayerState=STATE_CUED;
	GetParent()->SendMessage(UM_SORTPLAYERS,m_wPlayerPos,SORT_CUE );

	// 
	CRect	rect;
	GetClientRect(&rect);
	rect.left=rect.right-75;
	rect.DeflateRect(1,1,1,1);

	m_pCue->MoveWindow(&CRect(10000,0,0,0));
	m_pPlay->MoveWindow(&rect);

	rect.OffsetRect(-75,0);
	m_pUnCue->MoveWindow(&rect);

	PaintBM();
	PaintCrono();

	Invalidate();
	if( g_wndLineUp!=NULL )
		((CLineUpWnd *)g_wndLineUp)->CalcStartingTimes();
	else
		GetParent()->SendMessage(UM_CALCSTARTINGTIMES);
#ifdef __DEBUG_LOG
		WriteLogFile("COnAirPlayerWnd::CmCue (Exit) "+strLog);
#endif
}

void COnAirPlayerWnd::CmPlay()
{
	if( m_lpItem== NULL )
		return;

	if( m_lpItem->m_Sound==NULL )
		return;

#ifdef __DEBUG_LOG
	CString strLog;
	strLog.Format("(%d %s-%s)",m_lpItem->m_wType,m_lpItem->m_strName,m_lpItem->m_strName2);
	WriteLogFile("COnAirPlayerWnd::CmPlay (Enter) "+strLog);
#endif

	m_lpItem->m_Sound->SetPosition(m_lpItem->m_lStartPos);
	
	if( !m_lpItem->m_bPause )
		m_lpItem->m_Sound->Play();

	SetTimer(1,40,NULL);
//	m_lpItem->m_Sound->SetVolume(0);

	if( m_lpItem->m_lFadeInPos > m_lpItem->m_lStartPos )
		if( m_lpItem->m_bFadeInOutOfTake )
			m_lpItem->m_Sound->Fade(g_iFadeOnIntro,m_lpItem->m_lFadeInPos - m_lpItem->m_lStartPos );
		else
			m_lpItem->m_Sound->Fade(0,m_lpItem->m_lFadeInPos - m_lpItem->m_lStartPos );

	if( m_lpItem->m_bBlock )
	{
#ifdef __DEBUG_LOG
		WriteLogFile("COnAirPlayerWnd::CmPlay (Block) "+strLog);
#endif
		if( (g_nSplitters>0) && (m_lpItem->m_lBlockPos==0) )
		{
			typeSplitterMsg	Msg;
			CString			strTime;

			GetTimeString(m_lpItem->m_lBlockTime,&strTime);

			memset(&Msg,0,SIZEOFSPLITTERMSG);
			Msg.wAction	= SP_PLAY;
			Msg.wType	= TYPE_BLOCK;
			Msg.lTime	= m_lpItem->m_lBlockTime;
			wsprintf(Msg.pstrMessage,"Block Play: %s",strTime);
			SendSplitterMessage(&Msg);
		}
		g_wndTrafficInfo->Sync();
	}

	// Mandar informação para o Splitter
	if( g_nSplitters>0 )
	{
		typeSplitterMsg	Msg;

		memset(&Msg,0,SIZEOFSPLITTERMSG);
		Msg.wAction	= SP_PLAY;
		Msg.wType	= m_lpItem->m_wType;
		wsprintf(Msg.pstrMessage,"Play - %s - %s",m_lpItem->m_strName,m_lpItem->m_strName2);
		SendSplitterMessage(&Msg);
	}

	m_wPlayerState=STATE_PLAYING;
	m_lpItem->m_wState=STATE_PLAYING;

	GetParent()->SendMessage(UM_SORTPLAYERS,m_wPlayerPos,SORT_PLAY );

	// Teste
	CRect	rect;
	GetClientRect(&rect);
	rect.left=rect.right-75;
	rect.DeflateRect(1,1,1,1);

	m_pPlay->MoveWindow(CRect(10000,0,0,0));
	m_pUnCue->MoveWindow(CRect(10000,0,0,0));

	m_pStop->MoveWindow(&rect);

	rect.OffsetRect(-75,0);
	m_pMix->MoveWindow(&rect);

	// Log Item -----------------------------------------------------------------------
	typeLogItem *lpLog=new typeLogItem;
	lpLog->wType = m_lpItem->m_wType;
	lpLog->lID = m_lpItem->m_lItemID;
	lpLog->lTraffic = m_lpItem->m_lTrafficID;
	wsprintf(lpLog->strName,"%s - %s",m_lpItem->m_strName,m_lpItem->m_strName2);

	if( g_wndAired!=NULL )
	{
		typeLineUpItem *pAiredItem=new typeLineUpItem(m_lpItem->m_wType,m_lpItem->m_lItemID);
		SYSTEMTIME st;
		COleDateTime date=COleDateTime::GetCurrentTime();

		date.GetAsSystemTime(st);
		SystemTimeToFileTime(&st,(FILETIME *)&pAiredItem->m_qwStartTime);

		g_wndAired->m_pList->InsertString(0,(LPCTSTR)pAiredItem);
		g_wndAired->LogItem(lpLog);
	}
	else
		GetParent()->SendMessage(UM_LOGMESSAGE,0,(LPARAM)lpLog);
	// --------------------------------------------------------------------------------

	if( g_wndLineUp!=NULL )
		((CLineUpWnd *)g_wndLineUp)->CalcStartingTimes();
	else
		GetParent()->SendMessage(UM_CALCSTARTINGTIMES);
#ifdef __DEBUG_LOG
	WriteLogFile("COnAirPlayerWnd::CmPlay (Exit) "+strLog);
#endif
}

void COnAirPlayerWnd::CmStop()
{
#ifdef __DEBUG_LOG
	CString strLog;
	strLog.Format("(%d %s-%s)",m_lpItem->m_wType,m_lpItem->m_strName,m_lpItem->m_strName2);
	WriteLogFile("COnAirPlayerWnd::CmStop (Enter) "+strLog);
#endif

	KillTimer(1);
	
	CRect	rect;
	GetClientRect(&rect);
	rect.left=rect.right-150;
	rect.DeflateRect(1,1,1,1);

	m_pStop->MoveWindow(CRect(10000,0,0,0));
	m_pMix->MoveWindow(CRect(10000,0,0,0));
	m_pCue->MoveWindow(rect);
	m_pOptions->Reset();

	m_lpItem->m_Sound->Stop();

	SAFE_DELETE( m_lpItem );

	PaintBM();
	PaintCrono();

	Invalidate();

	m_wPlayerState=STATE_UNCUED;
	GetParent()->SendMessage(UM_SORTPLAYERS,m_wPlayerPos,SORT_UNCUE );

	if( g_wAutomationMode!=AUTOMATION_MANUAL )
		CmCue();
	
	GetParent()->SendMessage(UM_PLAYERSTOPED);

#ifdef __DEBUG_LOG
	WriteLogFile("COnAirPlayerWnd::CmStop (Exit) "+strLog);
#endif

}

void COnAirPlayerWnd::CmMix()
{
	m_lpItem->m_Sound->Fade(-3000,2000);

	m_lpItem->m_bLoop=FALSE;
	m_lpItem->m_nMixCount=1;
	m_lpItem->m_lMixPos=m_lpItem->m_lCurrentPos;
	m_lpItem->m_lEndPos=m_lpItem->m_lCurrentPos+2500;
}

void COnAirPlayerWnd::PaintBM()
{
	if( m_bmName==NULL )
		return; 

	Graphics	graph(m_bmName);
	Bitmap		*bmIcon;
	
	ImageAttributes imageAtt;
	ColorMap cMap[1];
	cMap[0].oldColor = Color(255, 212,208,200); // red 
	cMap[0].newColor = Color(  0, 255,255,255);  // blue
	imageAtt.SetRemapTable(1,cMap,ColorAdjustTypeDefault);

	graph.Clear(Color(198,255,255,255));

	if( m_lpItem!=NULL )
	{
		switch( m_lpItem->m_wType )
		{
		case TYPE_MUSIC:
			bmIcon=::new Bitmap(AfxGetInstanceHandle(),(WCHAR*)MAKEINTRESOURCE(IDB_CONTAINER_MUSIC));
			break;
		case TYPE_JINGLE:
			bmIcon=::new Bitmap(AfxGetInstanceHandle(),(WCHAR*)MAKEINTRESOURCE(IDB_CONTAINER_JINGLES));
			break;
		case TYPE_SPOT:
			bmIcon=::new Bitmap(AfxGetInstanceHandle(),(WCHAR*)MAKEINTRESOURCE(IDB_CONTAINER_TRAFFIC));
			break;
		case TYPE_VOICEINSERT:
			bmIcon=::new Bitmap(AfxGetInstanceHandle(),(WCHAR*)MAKEINTRESOURCE(IDB_CONTAINER_VOICEINSERT));
			break;
		case TYPE_RM:
			bmIcon=::new Bitmap(AfxGetInstanceHandle(),(WCHAR*)MAKEINTRESOURCE(IDB_CONTAINER_RMS));
			break;
		case TYPE_TIMESIGNAL:
			bmIcon=::new Bitmap(AfxGetInstanceHandle(),(WCHAR*)MAKEINTRESOURCE(IDB_TIMESIGNAL));
			break;
		default:
			bmIcon=::new Bitmap(AfxGetInstanceHandle(),(WCHAR*)MAKEINTRESOURCE(IDB_CONTAINER_MUSIC));
			break;
		}

		WCHAR		wchar[250];
		
		CString	strTemp=m_lpItem->m_strName+"\n"+m_lpItem->m_strName2;

		MultiByteConversion(strTemp,wchar);

		graph.DrawString(wchar,-1,g_font12,PointF(33,3),&SolidBrush(Color(128,0,0,0)));
		graph.DrawString(wchar,-1,g_font12,PointF(32,2),&SolidBrush(Color(255,0,0,0)));
		graph.DrawImage(bmIcon,Rect(2,10,bmIcon->GetWidth(), bmIcon->GetHeight()),  // dest rect
							0, 0, bmIcon->GetWidth(), bmIcon->GetHeight(),           // source rect
						UnitPixel,
						&imageAtt);

		::delete bmIcon;
	} 
}

void COnAirPlayerWnd::OnTimer(UINT nIDEvent) 
{
	if( nIDEvent==69 )
	{
		DrawPlayer();

		if( m_lpItem!=NULL )
			m_pVolume->SetVolume( m_lpItem->GetVolume() );

		return;
	}

	if( m_lpItem==NULL )
		return;

	m_pVolume->SetVolume( m_lpItem->GetVolume() );

	PaintCrono();
	DrawPlayer();

	if( m_lpItem->m_Sound==NULL )
		return;

	///////////////////////////////////////////////////////////////////////
	//	Do we need to fade in after after a take?
	if( (m_lpItem->m_bFadeInOutOfTake) && (m_lpItem->GetTimeToIntro()<250) )
	{
		m_lpItem->m_bFadeInOutOfTake=FALSE;
		m_lpItem->m_Sound->Fade(0,500);
	}

	///////////////////////////////////////////////////////////////////////
	// Do we need to fade out to the start of a voice insert?
	if( (m_lpItem->m_bFadeOutIntoTake) && (m_lpItem->GetTimeToMix()==0) )
	{
		m_lpItem->m_bFadeOutIntoTake=FALSE;
		m_lpItem->m_lMixPos = m_lpItem->m_lOriginalMix;
		m_lpItem->m_Sound->Fade(g_iFadeToTake,500);
		GetParent()->SendMessage(UM_STARTNEXTPLAYER,m_wPlayerPos);
		m_lpItem->m_nMixCount--;
	}

	///////////////////////////////////////////////////////////////////////
	//	Did we just reached the mix?
//	if( (m_lpItem->GetTimeToIntro()==0) && (m_lpItem->m_bLoop) && (m_lpItem->m_lIntroPos>m_lpItem->m_lStartPos) )
//		CmPlay();

	if( (m_lpItem->m_lCurrentPos>=m_lpItem->m_lLoopB) && (m_lpItem->m_bLoop) )
	{
		m_lpItem->m_Sound->SetPosition(m_lpItem->m_lLoopA);
	}

	if( m_lpItem->GetTimeToMix()==0 )
	{
		if( (m_lpItem->m_nMixCount) && (!m_lpItem->m_bPause) )
		{
			GetParent()->SendMessage(UM_STARTNEXTPLAYER,m_wPlayerPos);
			m_lpItem->m_nMixCount--;
		}
	}

	///////////////////////////////////////////////////////////////////////
	//	Check for fades
	m_lpItem->CheckFadeOut();

	///////////////////////////////////////////////////////////////////////
	//	Check for end of sound
	if( m_lpItem->GetTimeToEnd()==0 )
	{
		if( m_lpItem->m_bLoop )
		{
			CmPlay();
		}
		else
		{
			if( (m_lpItem->m_nMixCount) && (!m_lpItem->m_bPause) )
			{
				GetParent()->SendMessage(UM_STARTNEXTPLAYER,m_wPlayerPos);
				m_lpItem->m_nMixCount--;
			}
			CmStop();
		}
	}
}

void COnAirPlayerWnd::PaintCrono()
{
	Graphics graph(m_bmCrono);
	
	graph.Clear(Color(200,236,233,216));

	if( m_lpItem!=NULL )
	{
		WCHAR		wchar[250];
		WCHAR		wchar2[250];
		
		if( m_lpItem->m_Sound!=NULL )
		{
			CString	strTemp1;
			CString strTemp2="";
			long lTimeToIntro=m_lpItem->GetTimeToIntro();

			GetTimeString(m_lpItem->GetTimeToEnd(),&strTemp1);
			strTemp1.Delete(0,3);
			strTemp1.Delete(7,2);

			MultiByteConversion(strTemp1,wchar);

			graph.DrawString(wchar,-1,g_font12,PointF(2,2),&SolidBrush(Color(255,0,0,0)));

			if( lTimeToIntro )
			{
				GetTimeString(lTimeToIntro,&strTemp2);
				strTemp2.Delete(0,3);
				strTemp2.Delete(7,2);

				MultiByteConversion(strTemp2,wchar2);
				graph.DrawString(wchar2,-1,g_font12,PointF(2,24),&SolidBrush(Color(255,200,0,0)));
			}
	
		}
	}
}

void COnAirPlayerWnd::DrawPlayer()
{
	CClientDC	dc(this);
	Graphics	graphdc(dc);

	Bitmap		bm(m_rect.Width(),m_rect.Height(),&graphdc);
	Graphics	graph(&bm);

	graph.Clear(Color(255,212,208,200)) ;

	if( m_lpItem!=NULL )
		graph.DrawImage(m_lpItem->m_bmSpectrum,2.0f,1.0f,(REAL)(m_lpItem->m_Sound->GetPosition()*m_xres),0.0f,(REAL)m_rect.Width()-156,48.0f,UnitPixel);

	graph.DrawImage(m_bmName,2,1);
	graph.DrawImage(m_bmCrono,m_rect.right-222,1);

	graphdc.DrawImage(&bm,2,2,2,2,m_rect.Width()-154,48,UnitPixel);
}

Bitmap* COnAirPlayerWnd::CreateSpectrum()
{
	CClientDC	dc(this);
	Graphics	graph(dc);

	int			iViewZone=m_rect.Width()-154;
	float		sizebm;
	
	m_xres=(float)iViewZone/10000.0f;

	sizebm=(float)(m_lpItem->m_lEndPos+10000)*m_xres;
	

	int iSizeBm=(int)sizebm;

	Bitmap		*bm=::new Bitmap( iSizeBm,48,&graph);
	Graphics	graphbm(bm);

	RectF		rectIntro(m_lpItem->m_lStartPos*m_xres,0.0f,m_lpItem->GetTimeToIntro()*m_xres,48);
	RectF		rectMix((REAL)(m_lpItem->m_lMixPos)*m_xres,0.0f,(REAL)(m_lpItem->m_lEndPos-m_lpItem->m_lMixPos)*m_xres,48.0f);
	RectF		rectEnd(m_lpItem->m_lEndPos*m_xres,0.0f,2.0f,48.0f);

	LinearGradientBrush	brushRed(	PointF( (REAL)(m_lpItem->m_lIntroPos-5000)*m_xres,0),
									PointF( (REAL)(m_lpItem->m_lIntroPos)*m_xres,0),
									Color(255,255,255,0),
									Color(255,255,0,0) );

	LinearGradientBrush	brushYellow(PointF( (REAL)(m_lpItem->m_lIntroPos-10000)*m_xres,0),
									PointF( (REAL)(m_lpItem->m_lIntroPos-5000)*m_xres,0),
									Color(255,0,255,0),
									Color(255,255,255,0) );


	graphbm.Clear(Color(255,212,208,200));
	
	if( m_lpItem->GetTimeToIntro()>10000 )
	{
		// the intro has green, yellow and red
		graphbm.FillRectangle(&SolidBrush(Color(255,0,255,0)),RectF(m_lpItem->m_lStartPos*m_xres,0.0f,(m_lpItem->GetTimeToIntro()-10000)*m_xres,48) );
		graphbm.FillRectangle(&brushYellow,RectF((m_lpItem->m_lIntroPos-10000)*m_xres,0.0f,5000*m_xres,48) );
		graphbm.FillRectangle(&brushRed,RectF((m_lpItem->m_lIntroPos-5000)*m_xres,0.0f,5000*m_xres,48) );
	}
	else if( m_lpItem->GetTimeToIntro()>5000 )
	{
		// Yellow and red
		graphbm.FillRectangle(&brushYellow,RectF((m_lpItem->m_lStartPos)*m_xres,0.0f,(m_lpItem->GetTimeToIntro()-5000)*m_xres,48) );
		graphbm.FillRectangle(&brushRed,RectF((m_lpItem->m_lIntroPos-5000)*m_xres,0.0f,5000*m_xres,48) );
	}
	else if( m_lpItem->GetTimeToIntro()>0 )
	{
		// red
		graphbm.FillRectangle(&brushRed,RectF((m_lpItem->m_lStartPos)*m_xres,0.0f,m_lpItem->GetTimeToIntro()*m_xres,48) );
	}

	graphbm.FillRectangle(&SolidBrush(Color(255,222,222,0)),rectMix);

	if( (m_lpItem->m_lFadeInPos) && (m_lpItem->m_lFadeInPos>m_lpItem->m_lStartPos) )
	{
		// draws a path
		PointF	points[]={ PointF(0.0f,0.0f),
							PointF(0.0f,48.0f),
							PointF(m_lpItem->m_lStartPos*m_xres,48.0f),
							PointF(m_lpItem->m_lFadeInPos*m_xres,0.0f) };

		GraphicsPath	path;
		path.AddLines(points,4);
		graphbm.FillPath(&SolidBrush(Color(128,128,128)),&path);
	}
	else
		// Draws a rectangle
		graphbm.FillRectangle(&SolidBrush(Color(128,128,128)),RectF(0.0f,0.0f,m_lpItem->m_lStartPos*m_xres,48) );

	if( (m_lpItem->m_lFadeOutPos) && (m_lpItem->m_lFadeOutPos<m_lpItem->m_lEndPos) )
	{
		// Draw a path
		PointF	points[]={ PointF(m_lpItem->m_lFadeOutPos*m_xres,0.0f),
							PointF(m_lpItem->m_lEndPos*m_xres,48.0f),
							PointF((m_lpItem->m_lEndPos+10000)*m_xres,48.0f),
							PointF((m_lpItem->m_lEndPos+10000)*m_xres,0.0f) };

		GraphicsPath	path;
		path.AddLines(points,4);
		graphbm.FillPath(&SolidBrush(Color(128,128,128)),&path);
	}
	else
	{
		// draws a rectangle
		graphbm.FillRectangle(&SolidBrush(Color(128,128,128)),RectF(m_lpItem->m_lEndPos*m_xres,0.0f,10000.0f*m_xres,48) );
	}

	if( (m_lpItem->m_lLoopB > m_lpItem->m_lLoopA) && (m_lpItem->m_lLoopA!=m_lpItem->m_lStartPos) && (m_lpItem->m_lLoopB!=m_lpItem->m_lIntroPos) )
	{
		graphbm.FillRectangle(&SolidBrush(Color(200,0,0,255)),RectF(m_lpItem->m_lLoopA*m_xres,0.0f,(m_lpItem->m_lLoopB-m_lpItem->m_lLoopA)*m_xres,5) );
	}

	graphbm.FillRectangle(&SolidBrush(Color(255,180,0,0)),rectEnd);

	return bm;
}

void COnAirPlayerWnd::OnSwitchPause()
{
	if( (!m_lpItem) || (g_wAutomationMode==AUTOMATION_FULLAUTO) )
		return ;

	m_lpItem->m_bPause = !m_lpItem->m_bPause;
	m_pOptions->m_pPause->m_bLight = m_lpItem->m_bPause;
	m_pOptions->m_pPause->Invalidate();

	if( m_lpItem->m_bPause )
	{
		m_lpItem->m_Sound->Pause();
		m_lpItem->m_Sound->SetPosition(m_lpItem->m_lCurrentPos);
	}
	else
		m_lpItem->m_Sound->Play();
}

LRESULT COnAirPlayerWnd::OnSetPause(WPARAM,LPARAM)
{
	if( (!m_lpItem) || (g_wAutomationMode==AUTOMATION_FULLAUTO) )
		return 0;

	m_lpItem->m_bPause=m_pOptions->m_pPause->m_bLight;

	if( m_wPlayerState!=STATE_PLAYING )
		return 1;

	if( m_lpItem->m_bPause )
	{
		m_lpItem->m_Sound->Pause();
		m_lpItem->m_Sound->SetPosition(m_lpItem->m_lCurrentPos);
	}
	else
		m_lpItem->m_Sound->Play();

	return 1;
}

void COnAirPlayerWnd::OnSwitchLoop()
{
	if( (!m_lpItem) || (g_wAutomationMode==AUTOMATION_FULLAUTO) )
		return ;

	m_lpItem->m_bLoop = !m_lpItem->m_bLoop;
	m_pOptions->m_pLoop->m_bLight = m_lpItem->m_bLoop;
	m_pOptions->m_pLoop->Invalidate();
}

LRESULT COnAirPlayerWnd::OnSetLoop(WPARAM,LPARAM)
{
	if( (!m_lpItem) || (g_wAutomationMode==AUTOMATION_FULLAUTO) )
		return 0;

	m_lpItem->m_bLoop=m_pOptions->m_pLoop->m_bLight;
	return 0;
}

void COnAirPlayerWnd::OnUnCue()
{
	if( m_lpItem==NULL )
		return;

	if( g_wndLineUp )
		((CLineUpWnd *)g_wndLineUp)->AddItemByUnload( m_lpItem );
	else
		GetParent()->SendMessage(UM_ADDITEMBYUNCUE,0,(LPARAM)m_lpItem);

	m_lpItem=NULL;
	PaintBM();
	PaintCrono();
	m_wPlayerState=STATE_UNCUED;
	GetParent()->SendMessage(UM_SORTPLAYERS,m_wPlayerPos,SORT_UNCUE );

	CRect	rect;
	GetClientRect(&rect);
	rect.left=rect.right-150;
	rect.DeflateRect(1,1,1,1);

	m_pUnCue->MoveWindow(CRect(10000,0,0,0));
	m_pPlay->MoveWindow(CRect(10000,0,0,0));
	m_pCue->MoveWindow(rect);
	m_pOptions->Reset();
}

LRESULT COnAirPlayerWnd::OnDrop(WPARAM, LPARAM lParam)
{
#ifdef __DEBUG_LOG
	WriteLogFile("COnAirPlayerWnd::OnDrop (Enter)");
#endif
	typeDRAG_ITEM* lpDropItem=(typeDRAG_ITEM*)lParam;
	typeLineUpItem* lpNewItem;

	if( lpDropItem->wType==DRAG_ARCHIVE )
	{
		typeArchiveItem* lpItem=(typeArchiveItem*)lpDropItem->lpItem;
		if( lpItem->wType==TYPE_BLOCK )
			return 0;
		lpNewItem = new typeLineUpItem(lpItem->wType,lpItem->lID);
		lpNewItem->m_lTrafficID = lpItem->lTraffID;
	}
	else if( lpDropItem->wType == DRAG_BLOCK )
		return 0;
	else
		lpNewItem = (typeLineUpItem*)lpDropItem->lpItem;

#ifdef __DEBUG_LOG
	CString strLog;
	strLog.Format(" (%d %s-%s)",lpNewItem->m_wType,lpNewItem->m_strName,lpNewItem->m_strName2);
#endif

	if( lpNewItem->m_bItemIsValid )
	{
#ifdef __DEBUG_LOG
		WriteLogFile("COnAirPlayerWnd::OnDrop (ItemIsValid)"+strLog);
#endif
		GetParent()->SendMessage(UM_MAKESPACE,m_wPlayerPos);

		m_lpItem = lpNewItem;

		if( m_lpItem->m_Sound==NULL )
		{
#ifdef __DEBUG_LOG
			WriteLogFile("COnAirPlayerWnd::OnDrop (Sound is null)"+strLog);
#endif
			m_lpItem->m_Sound=new CAudioStream(lpDS_MAIN,this);

			m_lpItem->m_Sound->SetFile(m_lpItem->m_strFileName.GetBuffer(0));
			m_lpItem->m_bmSpectrum = CreateSpectrum();
			m_lpItem->m_Sound->m_pbm=m_lpItem->m_bmSpectrum;
			m_lpItem->m_Sound->m_xres=m_xres;

			if( m_lpItem->m_Sound->CueSound() == S_OK )
			{
				m_lpItem->m_Sound->SetPosition(m_lpItem->m_lStartPos);
				m_lpItem->m_wState = STATE_CUED;

				if( m_lpItem->m_lFadeInPos>m_lpItem->m_lStartPos )
					m_lpItem->m_Sound->SetVolume(-3000);
				else
					m_lpItem->m_Sound->SetVolume(0);

				m_pVolume->SetVolume( m_lpItem->GetVolume() );

			}
			else
			{
				SAFE_DELETE( m_lpItem->m_Sound );
				m_lpItem->m_Sound=NULL;
			}
		}
	
		if( m_lpItem->m_Sound == NULL )
		{
#ifdef __DEBUG_LOG
			WriteLogFile("COnAirPlayerWnd::OnDrop (Cue failed)"+strLog);
#endif
			// Log Item -----------------------------------------------------------------------
			typeLogItem *lpLog=new typeLogItem;
			lpLog->wType = 0;
			lpLog->lID = 0;
			lpLog->lTraffic = 0;
			wsprintf(lpLog->strName,"--> Error on DROP - %s - %s",m_lpItem->m_strName,m_lpItem->m_strName2);
			if( g_wndAired)
				g_wndAired->LogItem(lpLog);
			// --------------------------------------------------------------------------------

			SAFE_DELETE( m_lpItem );

			m_lpItem=NULL;
			PaintBM();
			PaintCrono();
			m_wPlayerState=STATE_UNCUED;
			GetParent()->SendMessage(UM_SORTPLAYERS,m_wPlayerPos,SORT_UNCUE );

			CRect	rect;
			GetClientRect(&rect);
			rect.left=rect.right-150;
			rect.DeflateRect(1,1,1,1);

			m_pUnCue->MoveWindow(CRect(10000,0,0,0));
			m_pPlay->MoveWindow(CRect(10000,0,0,0));
			m_pCue->MoveWindow(rect);
			m_pOptions->Reset();
			
			CmCue();

			return 1;
		}

		if( (g_wAutomationMode==AUTOMATION_FULLAUTO) )
		{
			m_lpItem->m_bLoop=FALSE;
			m_lpItem->m_bPause=FALSE;
			m_pOptions->Reset();
		}
		else
		{
			m_pOptions->m_pLoop->m_bLight = m_lpItem->m_bLoop;
			m_pOptions->m_pPause->m_bLight = m_lpItem->m_bPause;
			m_pOptions->m_pLoop->Invalidate();
			m_pOptions->m_pPause->Invalidate();
		}
		m_lpItem->m_Sound->SetPosition( m_lpItem->m_lStartPos);

		m_wPlayerState=STATE_CUED;
		GetParent()->SendMessage(UM_SORTPLAYERS,m_wPlayerPos,SORT_CUE );

	// 
		CRect	rect;
		GetClientRect(&rect);
		rect.left=rect.right-75;
		rect.DeflateRect(1,1,1,1);

		m_pCue->MoveWindow(&CRect(10000,0,0,0));
		m_pPlay->MoveWindow(&rect);

		rect.OffsetRect(-75,0);
		m_pUnCue->MoveWindow(&rect);

		PaintBM();
		PaintCrono();

		Invalidate();
	}
	else
	{
#ifdef __DEBUG_LOG
		WriteLogFile("COnAirPlayerWnd::OnDrop (Item Not Valid)"+strLog);
#endif
		SAFE_DELETE( lpNewItem );
	}

#ifdef __DEBUG_LOG
	WriteLogFile("COnAirPlayerWnd::OnDrop (Exit)");
#endif
	return 1;
}

LRESULT COnAirPlayerWnd::OnCanDrop(WPARAM, LPARAM)
{
	if( m_wPlayerState!=STATE_PLAYING )
		return 1;
	else
		return 0;
}

void COnAirPlayerWnd::UpdateButtons()
{
	CRect	rect;
	GetClientRect(&rect);

	switch( m_wPlayerState )
	{
	case STATE_UNCUED:
		rect.left=rect.right-150;
		rect.DeflateRect(1,1,1,1);
		m_pCue->MoveWindow(&rect);

		m_pPlay->MoveWindow(10000,0,0,0);
		m_pStop->MoveWindow(10000,0,0,0);
		m_pMix->MoveWindow(10000,0,0,0);
		m_pUnCue->MoveWindow(10000,0,0,0);
		break;
	case STATE_CUED:
		rect.left=rect.right-75;
		rect.DeflateRect(1,1,1,1);

		m_pPlay->MoveWindow(&rect);

		rect.OffsetRect(-75,0);
		m_pUnCue->MoveWindow(&rect);

		m_pStop->MoveWindow(10000,0,0,0);
		m_pMix->MoveWindow(10000,0,0,0);
		m_pCue->MoveWindow(10000,0,0,0);
		break;
	case STATE_PLAYING:
		m_pPlay->MoveWindow(10000,0,0,0);
		m_pCue->MoveWindow(10000,0,0,0);
		m_pUnCue->MoveWindow(10000,0,0,0);
		break;
	}

	if( m_lpItem==NULL ) 
		return;

	if( (g_wAutomationMode==AUTOMATION_FULLAUTO) )
	{
		m_lpItem->m_bLoop=FALSE;
		m_lpItem->m_bPause=FALSE;
		m_pOptions->Reset();
	}
	else
	{
		m_pOptions->m_pLoop->m_bLight = m_lpItem->m_bLoop;
		m_pOptions->m_pPause->m_bLight = m_lpItem->m_bPause;
		m_pOptions->m_pLoop->Invalidate();
		m_pOptions->m_pPause->Invalidate();
	}
}

DWORD64 COnAirPlayerWnd::GetTimeToMix()
{
	if( m_lpItem==NULL )
		return 0;
	else
		return (DWORD64)(m_lpItem->GetTimeToMix())*10000;
}

LRESULT	COnAirPlayerWnd::OnVolumeChange(WPARAM wParam,LPARAM)
{
	if( m_lpItem )
		if( m_lpItem->m_Sound!=NULL )
		{
			m_lpItem->m_Sound->SetVolume((DWORD)wParam);
		}

	return 0;
}

void COnAirPlayerWnd::ResetMixAndIntro()
{
	if( m_lpItem!=NULL )
	{
		m_lpItem->m_lIntroPos = m_lpItem->m_lOriginalIntro;
		if( m_lpItem->m_wType != TYPE_VOICEINSERT )
			m_lpItem->m_lMixPos = m_lpItem->m_lOriginalMix;
	}
}
