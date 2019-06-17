// PFLWnd.cpp : implementation file
//

#include "stdafx.h"
#include <gdiplus.h>
#include "PFLWnd.h"
#include "OnAirDefines.h"
#include "ExternalObjects.h"
#include "..\include\SoundUtils.h"
#include "..\include\Utils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPFLWnd

#define ID_SLIDER	2001
#define ID_PLAY		2002
#define ID_STOP		2003

using namespace Gdiplus;

IMPLEMENT_DYNCREATE(CPFLWnd, CFrameWnd)

CPFLWnd::CPFLWnd()
{
	m_pItem=NULL;
	m_bScrolling = FALSE;
	m_bTopMost = TRUE;
}

CPFLWnd::~CPFLWnd()
{
	SAFE_DELETE( m_pItem );

	::delete m_bmName;
	::delete m_bmCrono;
}


BEGIN_MESSAGE_MAP(CPFLWnd, CFrameWnd)
	//{{AFX_MSG_MAP(CPFLWnd)
	ON_WM_CLOSE()
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_HSCROLL()
	ON_COMMAND( ID_PLAY, OnPlay )
	ON_COMMAND( ID_STOP, OnStop )
	ON_WM_SYSCOMMAND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPFLWnd message handlers

void CPFLWnd::OnClose() 
{
	GetWindowPlacement(&m_Placement);
	MoveWindow(0,0,0,0);
	m_bHide=TRUE;

	if( m_pItem!=NULL )
		OnStop();
}

int CPFLWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rect;
	GetClientRect(&rect);
	GetClientRect(&m_rect);

	rect.DeflateRect(2,52,154,2);
//	rect.bottom=rect.top+25;

	m_pSlider = new CSliderCtrl;	
	m_pSlider->Create(WS_VISIBLE|TBS_AUTOTICKS|TBS_HORZ|TBS_TOP|TBS_ENABLESELRANGE,rect,this,ID_SLIDER);
	m_pSlider->SetRange(0,1000);
	m_pSlider->SetTicFreq(10);

	GetClientRect(&rect);
	rect.left=rect.right-76;
	rect.right--;
	rect.top++;
	rect.bottom--;

	///////////////////////////////////////////////////////////////////////
	//	Play Button
	m_pPlay = new CPlayerButton();
	m_pPlay->Create("",WS_VISIBLE|BS_OWNERDRAW,rect,this,ID_PLAY);
	m_pPlay->SetImageList(50,50,0,1);
	m_pPlay->AddImage(IDB_PLAY);

	////////////////////////////////////////////////////////////////////////
	//	Stop Button
	rect.OffsetRect(-75,0);
	m_pStop = new CPlayerButton();
	m_pStop->Create("",WS_VISIBLE|BS_OWNERDRAW,rect,this,ID_STOP);
	m_pStop->SetImageList(50,50,0,1);
	m_pStop->AddImage(IDB_STOP,RGB(252,252,252));

	/////////////////////////////////////////////////////////////////////////
	//	Create the bitmaps
	CClientDC	dc(this);
	Graphics	graph(dc);

	m_bmName = ::new Bitmap(m_rect.Width(),48,&graph);
	
	Graphics	graphbm(m_bmName);
	graphbm.Clear(Color(198,255,255,255));

	m_bmCrono = ::new Bitmap(69,48,&graph);

	SetTimer(1,250,NULL);
	return 0;
}

void CPFLWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect	rect;
	GetClientRect(&rect);

	dc.FillRect(&rect,&CBrush(GetSysColor(COLOR_3DFACE)) );
	rect.DeflateRect(rect.right-152,0,0,0);

	dc.Draw3dRect(0,0,rect.right-153,50,RGB(255,255,255),RGB(128,128,128));
	dc.Draw3dRect(&rect,RGB(255,255,255),RGB(128,128,128));

	GetClientRect(&rect);
	rect.DeflateRect(1,51,153,1);
	dc.Draw3dRect(&rect,RGB(255,255,255),RGB(128,128,128));

	DrawPlayer();
}

void CPFLWnd::CueSound()
{
	if( m_pItem==NULL )
		return;

	if( m_pItem->m_Sound==NULL )
	{
		m_pItem->m_Sound=new CAudioStream(lpDS_PFL,this);

		m_pItem->m_Sound->SetFile(m_pItem->m_strFileName.GetBuffer(0));
		m_pItem->m_bmSpectrum = CreateSpectrum();
		m_pItem->m_Sound->m_pbm = m_pItem->m_bmSpectrum;
		m_pItem->m_Sound->m_xres = m_xres;

		if( m_pItem->m_Sound->CueSound() == S_OK )
		{
			m_pItem->m_Sound->SetPosition(m_pItem->m_lStartPos);
			m_pItem->m_wState = STATE_CUED;

			if( m_pItem->m_lFadeInPos>m_pItem->m_lStartPos )
				m_pItem->m_Sound->SetVolume(-3000);
			else
				m_pItem->m_Sound->SetVolume(0);

		}
		else
		{
			SAFE_DELETE( m_pItem->m_Sound );
		}
	}

	if( m_pItem->m_Sound == NULL )
	{
		SAFE_DELETE( m_pItem );
		Invalidate();
		return;
	}

	m_pItem->m_Sound->SetPosition( m_pItem->m_lStartPos);

//	m_wPlayerState=STATE_CUED;
//	GetParent()->SendMessage(UM_SORTPLAYERS,m_wPlayerPos,SORT_CUE );

	PaintBM();
//	PaintCrono();

	Invalidate();
}

void CPFLWnd::PaintBM()
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

	if( m_pItem!=NULL )
	{
		switch( m_pItem->m_wType )
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
		default:
			bmIcon=::new Bitmap(AfxGetInstanceHandle(),(WCHAR*)MAKEINTRESOURCE(IDB_CONTAINER_MUSIC));
			break;
		}

		WCHAR		wchar[250];
		
		CString	strTemp=m_pItem->m_strName+"\n"+m_pItem->m_strName2;

		MultiByteConversion(strTemp,wchar);

		graph.DrawString(wchar,-1,g_font12,PointF(34,4),&SolidBrush(Color(64,0,0,0)));
		graph.DrawString(wchar,-1,g_font12,PointF(32,2),&SolidBrush(Color(255,0,0,0)));
		graph.DrawImage(bmIcon,Rect(2,10,bmIcon->GetWidth(), bmIcon->GetHeight()),  // dest rect
							0, 0, bmIcon->GetWidth(), bmIcon->GetHeight(),           // source rect
						UnitPixel,
						&imageAtt);

		::delete bmIcon;
	}
}


void CPFLWnd::DrawPlayer()
{
	CClientDC	dc(this);
	Graphics	graphdc(dc);

	Bitmap		bm(m_rect.Width(),m_rect.Height(),&graphdc);
	Graphics	graph(&bm);

	graph.Clear(Color(255,212,208,200)) ;

	if( m_pItem!=NULL )
		graph.DrawImage(m_pItem->m_bmSpectrum,2.0f,1.0f,(REAL)(m_pItem->m_Sound->GetPosition()*m_xres),0.0f,(REAL)m_rect.Width()-158,48.0f,UnitPixel);

	graph.DrawImage(m_bmName,2,1);
	graph.DrawImage(m_bmCrono,m_rect.right-222,1);

	graphdc.DrawImage(&bm,2,2,2,2,m_rect.Width()-158,47,UnitPixel);
}

void CPFLWnd::OnTimer(UINT nIDEvent) 
{
	PaintCrono();
	DrawPlayer();

	if( m_pItem!=NULL )
		if( m_pItem->m_Sound!=NULL )
		{
			if( m_pItem->m_wState == STATE_PLAYING )
			{
				float	fVol;
				long	lPos = m_pItem->m_Sound->GetPosition();

				if( !m_bScrolling )
				{
					m_pSlider->SetPos((int)((float)(lPos-m_pItem->m_lStartPos)/(float)m_pItem->GetLength()*1000.0f));
				}

				if( (lPos < m_pItem->m_lStartPos) || (lPos > m_pItem->m_lEndPos) )
					m_pItem->m_Sound->SetVolume(-10000);
				else if( lPos < m_pItem->m_lFadeInPos )
				{
					fVol=-3000*(float)(m_pItem->m_lFadeInPos-lPos)/(m_pItem->m_lFadeInPos-m_pItem->m_lStartPos);
					m_pItem->m_Sound->SetVolume((long)fVol);
				}
				else if( (lPos > m_pItem->m_lFadeOutPos) && (m_pItem->m_lFadeOutPos) )
				{	
					fVol=-3000*(float)(lPos-m_pItem->m_lFadeOutPos)/(m_pItem->m_lEndPos-m_pItem->m_lFadeOutPos);
					m_pItem->m_Sound->SetVolume((long)fVol);
				}
				else
					m_pItem->m_Sound->SetVolume(0);
			}
			else
				if( m_bAutoStart && (m_pItem->m_Sound->GetDecompressedSize()>m_pItem->m_lStartPos/1000+2) )
					OnPlay();
		}

}

void CPFLWnd::SetSound(WORD wType,long lID,CString str)
{
	SAFE_DELETE( m_pItem);

	m_pItem = new typeLineUpItem(wType,lID,0,str);
	if( m_pItem->m_bItemIsValid )
	{
		CueSound();
		m_bAutoStart=TRUE;
	}
	else
	{
		SAFE_DELETE( m_pItem );
		Invalidate();
	}
}

void CPFLWnd::SetSound( typeArchiveItem* lpItem)
{
	SAFE_DELETE(m_pItem);

	m_pItem = new typeLineUpItem(lpItem->wType,lpItem->lID);
	if( m_pItem->m_bItemIsValid )
	{
		CueSound();
		m_bAutoStart = TRUE;
	}
	else
	{
		SAFE_DELETE( m_pItem );
		Invalidate();
	}
}

void CPFLWnd::SetSound(typeLineUpItem *lpItem)
{
	SAFE_DELETE(m_pItem);

	m_pItem = new typeLineUpItem(lpItem->m_wType,lpItem->m_lItemID);
	if( m_pItem->m_bItemIsValid )
	{
		CueSound();
		m_bAutoStart = TRUE;
	}
	else
	{
		SAFE_DELETE( m_pItem );
		Invalidate();
	}
}


void CPFLWnd::OnPlay()
{
	m_bAutoStart=FALSE;

	if( m_pItem!=NULL )
		if( m_pItem->m_Sound!=NULL )
		{
			m_pItem->m_Sound->SetPosition(m_pItem->m_lStartPos);
			m_pItem->m_Sound->Play();

			if( m_pItem->m_wState != STATE_PLAYING )
			{
				m_pItem->m_wState=STATE_PLAYING;
				SetTimer(2,10,NULL);
			}
		}
}

void CPFLWnd::OnStop()
{
	if( m_pItem!=NULL )
		if( m_pItem->m_Sound!=NULL )
		{
			m_pItem->m_Sound->Pause();
			m_pItem->m_wState=STATE_CUED;
		}

	KillTimer(2);
}

Bitmap* CPFLWnd::CreateSpectrum()
{
	CClientDC	dc(this);
	Graphics	graph(dc);

	int			iViewZone=m_rect.Width()-154;
	float		sizebm;
	
	m_xres=(float)iViewZone/10000.0f;

	sizebm=(float)(m_pItem->m_lEndPos+10000)*m_xres;
	

	int iSizeBm=(int)sizebm;
	Bitmap		*bmTeste = ::new Bitmap( iSizeBm,48,&graph) ;
	::delete bmTeste;

	Bitmap		*bm = ::new Bitmap( iSizeBm,48,&graph) ;
	Graphics	graphbm(bm);

	RectF		rectIntro(m_pItem->m_lStartPos*m_xres,0.0f,m_pItem->GetTimeToIntro()*m_xres,48);
	RectF		rectMix((REAL)(m_pItem->m_lMixPos)*m_xres,0.0f,(REAL)(m_pItem->m_lEndPos-m_pItem->m_lMixPos)*m_xres,48.0f);
	RectF		rectEnd(m_pItem->m_lEndPos*m_xres,0.0f,2.0f,48.0f);

	LinearGradientBrush	brushRed(	PointF( (REAL)(m_pItem->m_lIntroPos-5000)*m_xres,0),
									PointF( (REAL)(m_pItem->m_lIntroPos)*m_xres,0),
									Color(255,255,255,0),
									Color(255,255,0,0) );

	LinearGradientBrush	brushYellow(PointF( (REAL)(m_pItem->m_lIntroPos-10000)*m_xres,0),
									PointF( (REAL)(m_pItem->m_lIntroPos-5000)*m_xres,0),
									Color(255,0,255,0),
									Color(255,255,255,0) );


	graphbm.Clear(Color(255,212,208,200));
	
	if( m_pItem->GetTimeToIntro()>10000 )
	{
		// the intro has green, yellow and red
		graphbm.FillRectangle(&SolidBrush(Color(255,0,255,0)),RectF(m_pItem->m_lStartPos*m_xres,0.0f,(m_pItem->GetTimeToIntro()-10000)*m_xres,48) );
		graphbm.FillRectangle(&brushYellow,RectF((m_pItem->m_lIntroPos-10000)*m_xres,0.0f,5000*m_xres,48) );
		graphbm.FillRectangle(&brushRed,RectF((m_pItem->m_lIntroPos-5000)*m_xres,0.0f,5000*m_xres,48) );
	}
	else if( m_pItem->GetTimeToIntro()>5000 )
	{
		// Yellow and red
		graphbm.FillRectangle(&brushYellow,RectF((m_pItem->m_lStartPos)*m_xres,0.0f,(m_pItem->GetTimeToIntro()-5000)*m_xres,48) );
		graphbm.FillRectangle(&brushRed,RectF((m_pItem->m_lIntroPos-5000)*m_xres,0.0f,5000*m_xres,48) );
	}
	else if( m_pItem->GetTimeToIntro()>0 )
	{
		// red
		graphbm.FillRectangle(&brushRed,RectF((m_pItem->m_lStartPos)*m_xres,0.0f,m_pItem->GetTimeToIntro()*m_xres,48) );
	}

	graphbm.FillRectangle(&SolidBrush(Color(255,222,222,0)),rectMix);

	if( (m_pItem->m_lFadeInPos) && (m_pItem->m_lFadeInPos>m_pItem->m_lStartPos) )
	{
		// draws a path
		PointF	points[]={ PointF(0.0f,0.0f),
							PointF(0.0f,48.0f),
							PointF(m_pItem->m_lStartPos*m_xres,48.0f),
							PointF(m_pItem->m_lFadeInPos*m_xres,0.0f) };

		GraphicsPath	path;
		path.AddLines(points,4);
		graphbm.FillPath(&SolidBrush(Color(128,128,128)),&path);
	}
	else
		// Draws a rectangle
		graphbm.FillRectangle(&SolidBrush(Color(128,128,128)),RectF(0.0f,0.0f,m_pItem->m_lStartPos*m_xres,48) );

	if( (m_pItem->m_lFadeOutPos) && (m_pItem->m_lFadeOutPos<m_pItem->m_lEndPos) )
	{
		// Draw a path
		PointF	points[]={ PointF(m_pItem->m_lFadeOutPos*m_xres,0.0f),
							PointF(m_pItem->m_lEndPos*m_xres,48.0f),
							PointF((m_pItem->m_lEndPos+10000)*m_xres,48.0f),
							PointF((m_pItem->m_lEndPos+10000)*m_xres,0.0f) };

		GraphicsPath	path;
		path.AddLines(points,4);
		graphbm.FillPath(&SolidBrush(Color(128,128,128)),&path);
	}
	else
	{
		// draws a rectangle
		graphbm.FillRectangle(&SolidBrush(Color(128,128,128)),RectF(m_pItem->m_lEndPos*m_xres,0.0f,10000.0f*m_xres,48) );
	}

	graphbm.FillRectangle(&SolidBrush(Color(255,180,0,0)),rectEnd);

	return bm;

}

void CPFLWnd::PaintCrono()
{
	Graphics graph(m_bmCrono);
	
	graph.Clear(Color(200,236,233,216));

	if( m_pItem!=NULL )
	{
		WCHAR		wchar[250];
		WCHAR		wchar2[250];
		
		if( m_pItem->m_Sound!=NULL )
		{
			CString	strTemp1;
			CString strTemp2="";
			long lTimeToIntro=m_pItem->GetTimeToIntro();

			GetTimeString(m_pItem->GetTimeToEnd(),&strTemp1);
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

void CPFLWnd::RestoreWindow()
{
	if( m_bHide )
	{
		SetWindowPlacement(&m_Placement);
		if( m_bTopMost )
			SetWindowPos(&wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
		else
			BringWindowToTop();
	}
	m_bHide=FALSE;
}

void CPFLWnd::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if( m_pItem==NULL )
		return;

	float fNewPos=(float)m_pItem->GetLength()*(float)nPos/(float)1000;

	switch( nSBCode )
	{
//	case SB_PAGELEFT:
//	case SB_PAGERIGHT:
	case TB_THUMBTRACK:
		m_pItem->m_Sound->SetPosition((DWORD)fNewPos+m_pItem->m_lStartPos);
		m_pSlider->SetPos(nPos);
		m_bScrolling = TRUE;
		break;
	case SB_ENDSCROLL:
		m_bScrolling = FALSE;
	default:
		break;
	}
}

void CPFLWnd::OnSysCommand(UINT nID, LPARAM lParam) 
{
	CFrameWnd::OnSysCommand(nID,lParam);
}

