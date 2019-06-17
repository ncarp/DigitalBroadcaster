// Recorder.cpp : implementation file
//

#include "stdafx.h"
#include <gdiplus.h>

using namespace Gdiplus;

#include "ExternalObjects.h"
#include "Recorder.h"
#include "OnAirUtils.h"
#include "OnAirDefines.h"
//#include "..\include\utils.h"
#include "..\include\SoundUtils.h"
#include "..\common\include\utils.h"
#include "..\common\include\mp3file.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ID_REC		1001
#define ID_PLAY		1002
#define ID_STOP		1003
#define ID_START	1004
#define ID_END		1005
#define ID_FADEIN	1006
#define ID_PAUSE	1007
#define ID_INTRO	1008
#define ID_FADEOUT	1009
#define ID_MIX		1010
#define ID_LOOPA	1012
#define ID_LOOPB	1013
#define ID_SOUNDCHECK	1014
#define ID_LOOPCHECK	1015
#define ID_FINDPLAY		1016

/////////////////////////////////////////////////////////////////////////////
// CRecorder

CRecorder::CRecorder()
{
	m_pSound=NULL;
	m_bCheckSound = FALSE;
	m_bCheckLoop = FALSE;
	m_bCanRec = FALSE;
	m_wMode = 0;
}

CRecorder::~CRecorder()
{
	SAFE_DELETE(m_pSound);
}

BEGIN_MESSAGE_MAP(CRecorder, CStatic)
	//{{AFX_MSG_MAP(CRecorder)
	ON_WM_CREATE()
	ON_WM_HSCROLL()
	ON_COMMAND( ID_REC,		OnRec )
	ON_COMMAND( ID_PLAY,	OnPlay )
	ON_COMMAND( ID_STOP,	OnStop )
	ON_COMMAND( ID_PAUSE,	OnPause )
	ON_COMMAND( ID_FINDPLAY,OnFindPlay )
	ON_COMMAND( ID_SOUNDCHECK,OnCheckSound )
	ON_COMMAND( ID_LOOPCHECK,OnCheckLoop )
	ON_MESSAGE( UM_UPDATETIMERS,OnUpdateTimers )
	ON_MESSAGE( UM_GOTO, OnGoTo )
	ON_STN_CLICKED(ID_START,OnResetStart)
	ON_STN_CLICKED(ID_FADEIN,OnResetFadeIn)
	ON_STN_CLICKED(ID_INTRO,OnResetIntro)
	ON_STN_CLICKED(ID_FADEOUT,OnResetFadeOut)
	ON_STN_CLICKED(ID_MIX,OnResetMix)
	ON_STN_CLICKED(ID_END,OnResetEnd)
	ON_STN_CLICKED(ID_LOOPA,OnResetLoopA)
	ON_STN_CLICKED(ID_LOOPB,OnResetLoopB)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRecorder message handlers

int CRecorder::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	lpCreateStruct->lpszClass=_T("Recorder");

	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect crect;
	GetClientRect(&crect);
	CRect	rect=crect;
	CString str;

	crect.left=crect.right/2-140;
	crect.right=crect.left+70;
	crect.bottom-=10;
	crect.top=crect.bottom-60;

	m_pRec = new CPlayerButton();	
	m_pRec->Create(NULL,WS_VISIBLE|BS_OWNERDRAW,crect,this,ID_REC);
	m_pRec->SetImageList(50,50,0,1);
	if( m_bCanRec )
		m_pRec->AddImage(IDB_REC);
	else
		m_pRec->AddImage(IDB_RECOFF);
	
	crect.OffsetRect(70,0);

	m_pPause = new CPlayerButton();	
	m_pPause->Create(NULL,WS_VISIBLE|BS_OWNERDRAW,crect,this,ID_PAUSE);
	m_pPause->SetImageList(50,50,0,1);
	m_pPause->AddImage(IDB_PAUSE_BIG);
	
	crect.OffsetRect(70,0);

	m_pStop = new CPlayerButton();	
	m_pStop->Create(NULL,WS_VISIBLE|BS_OWNERDRAW,crect,this,ID_STOP);
	m_pStop->SetImageList(50,50,0,1);
	m_pStop->AddImage(IDB_STOP,RGB(252,252,252));

	crect.OffsetRect(70,0);

	m_pPlay = new CPlayerButton();	
	m_pPlay->Create(NULL,WS_VISIBLE|BS_OWNERDRAW,crect,this,ID_PLAY);
	m_pPlay->SetImageList(50,50,0,1);
	m_pPlay->AddImage(IDB_PLAY);

	GetClientRect(&crect);

	crect.DeflateRect(5,5,5,200);
	crect.bottom=crect.top+55;
	m_pTimer = new CTimerDefinition();
	m_pTimer->Create(NULL,SS_NOTIFY|WS_VISIBLE,crect,this);
	m_pTimer->m_xres=(float)(crect.Width())/10000.0f;

	crect.OffsetRect(0,55);
	crect.bottom=crect.top+20;
	m_pSlider = new CSliderCtrl();
	m_pSlider->Create(WS_VISIBLE,crect,this,02);
	
	m_pFindPlay = new CButton();
	m_pFindPlay->Create("Find Play",WS_VISIBLE,CRect(5,85,(int)(rect.Width()*0.33f-2),105),this,ID_FINDPLAY);

	m_pSoundCheck = new CButton();
	m_pSoundCheck->Create("Sound Check",BS_PUSHLIKE|BS_AUTORADIOBUTTON|WS_VISIBLE,CRect((int)(rect.Width()*0.33f+2),85,(int)((float)rect.Width()*0.66f-2),105),this,ID_SOUNDCHECK);

	m_pLoopCheck = new CButton();
	m_pLoopCheck->Create("Loop Check",BS_PUSHLIKE|BS_AUTORADIOBUTTON|WS_VISIBLE,CRect((int)(rect.Width()*0.66f+2),85,(int)(rect.Width()-5),105),this,ID_LOOPCHECK);

	crect.OffsetRect(0,55);
	crect.right=crect.right/4-2;

	CStatic	*temp=new CStatic();
	temp->Create("Start:",SS_RIGHT|WS_VISIBLE|WS_CHILD,crect,this);

	crect.OffsetRect(0,20);
	temp=new CStatic();
	temp->Create("Fade In:",SS_RIGHT|WS_VISIBLE|WS_CHILD,crect,this);

	crect.OffsetRect(0,20);
	temp=new CStatic();
	temp->Create("Intro:",SS_RIGHT|WS_VISIBLE|WS_CHILD,crect,this);

	crect.OffsetRect(0,20);
	temp=new CStatic();
	temp->Create("Loop A:",SS_RIGHT|WS_VISIBLE|WS_CHILD,crect,this);

	crect.OffsetRect(crect.Width()+13,-60);
	m_pStart=new CStatic();
	m_pStart->Create("00:00:00.0",WS_VISIBLE|WS_CHILD|SS_NOTIFY|SS_SUNKEN|SS_CENTER,crect,this,ID_START);

	crect.OffsetRect(0,20);
	m_pFadeIn=new CStatic();
	m_pFadeIn->Create("00:00:00.0",WS_VISIBLE|WS_CHILD|SS_NOTIFY|SS_SUNKEN|SS_CENTER,crect,this,ID_FADEIN);

	crect.OffsetRect(0,20);
	m_pIntro=new CStatic();
	m_pIntro->Create("00:00:00.0",WS_VISIBLE|WS_CHILD|SS_NOTIFY|SS_SUNKEN|SS_CENTER,crect,this,ID_INTRO);

	crect.OffsetRect(0,20);
	m_pLoopA=new CStatic();
	m_pLoopA->Create("00:00:00.0",WS_VISIBLE|WS_CHILD|SS_NOTIFY|SS_SUNKEN|SS_CENTER,crect,this,ID_LOOPA);

	crect.OffsetRect(crect.Width()+3,-60);
	temp=new CStatic();
	temp->Create("End:",SS_RIGHT|WS_VISIBLE|WS_CHILD,crect,this);

	crect.OffsetRect(0,20);
	temp=new CStatic();
	temp->Create("Fade Out:",SS_RIGHT|WS_VISIBLE|WS_CHILD,crect,this);

	crect.OffsetRect(0,20);
	temp=new CStatic();
	temp->Create("Mix:",SS_RIGHT|WS_VISIBLE|WS_CHILD,crect,this);

	crect.OffsetRect(0,20);
	temp=new CStatic();
	temp->Create("Loop B:",SS_RIGHT|WS_VISIBLE|WS_CHILD,crect,this);

	crect.OffsetRect(crect.Width()+13,-60);
	m_pEnd=new CStatic();
	m_pEnd->Create("00:00:00.0",WS_VISIBLE|WS_CHILD|SS_NOTIFY|SS_SUNKEN|SS_CENTER,crect,this,ID_END);

	crect.OffsetRect(0,20);
	m_pFadeOut=new CStatic();
	m_pFadeOut->Create("00:00:00.0",WS_VISIBLE|WS_CHILD|SS_NOTIFY|SS_SUNKEN|SS_CENTER,crect,this,ID_FADEOUT);

	crect.OffsetRect(0,20);
	m_pMix=new CStatic();
	m_pMix->Create("00:00:00.0",WS_VISIBLE|WS_CHILD|SS_NOTIFY|SS_SUNKEN|SS_CENTER,crect,this,ID_MIX);

	crect.OffsetRect(0,20);
	m_pLoopB=new CStatic();
	m_pLoopB->Create("00:00:00.0",WS_VISIBLE|WS_CHILD|SS_NOTIFY|SS_SUNKEN|SS_CENTER,crect,this,ID_LOOPB);

	return 0;
}

void CRecorder::SetFile(CString str)
{
	SAFE_DELETE( m_pSound );
	m_pTimer->DeleteBM();

	m_strFileName = str;
	
	long	dwLength=30000;
	CString strFileType = GetFileType(str);
	strFileType.MakeUpper();

	//////////////////////////////////////////////////////////
	// Get the sound length, and create the bitmap
	if( strFileType==".WAV" )
	{
		CWaveFile		*wave=new CWaveFile();
		LPWAVEFORMATEX	pwfx;

		if( wave->Open(str.GetBuffer(0),NULL,WAVEFILE_READ)==S_OK )
		{
			pwfx = wave->GetFormat();

			dwLength=(DWORD)((float)wave->GetSize()/((float)pwfx->nAvgBytesPerSec/1000));
			if( dwLength==0 )
				dwLength=30000;
		}

		delete wave;
	}
	else if( strFileType==".MP3" )
	{
		CMp3File	mp3;

		if( mp3.Open(str)==S_OK )
		{
			dwLength=(DWORD)((float)mp3.m_dwDataSize/((float)mp3.m_pwfx->wfx.nAvgBytesPerSec/1000));
			if( dwLength==0 )
				dwLength=30000;
		}
	}
	else
		return;

	/////////////////////////////////////////////////////////////
	// Create the bitmap
	float	sizebm=(float)(dwLength+10000)*m_pTimer->m_xres;
	int		iSizeBm=(int)sizebm;
	Bitmap	*bm=::new Bitmap( iSizeBm,48,PixelFormat32bppARGB);
	CRect	rect;
	m_pTimer->GetClientRect(&rect);

	m_pSound=new CAudioStream(lpDS_PFL,this);

	m_pSound->SetFile(str.GetBuffer(0));
	m_pSound->m_pbm = bm;
	m_pSound->m_xres=m_pTimer->m_xres;
	m_pSound->m_bDecompressAll=TRUE;
	m_pSound->CueSound();
	m_pSound->SetPosition(0);

	m_pTimer->m_RightPos=0;
	m_pTimer->m_Start=0;
	m_pTimer->m_FadeIn=0;
	m_pTimer->m_Intro=0;

	if( !(MF_GRAYED & m_pTimer->m_Menu->GetMenuState(MN_FADEOUT,MF_BYCOMMAND)) )
		m_pTimer->m_FadeOut=dwLength-5000;

	if( !(MF_GRAYED & m_pTimer->m_Menu->GetMenuState(MN_MIX,MF_BYCOMMAND)) )
		m_pTimer->m_Mix=dwLength-5000;
	else
		m_pTimer->m_Mix=dwLength+15000;
	m_pTimer->m_End=dwLength;
	m_pTimer->m_LoopA=0;
	m_pTimer->m_LoopB=0;
	m_pTimer->SetSpectrum(bm);
	m_pTimer->m_PlayPos=0;

	m_pSlider->SetRange(0,dwLength+10000);
	m_pSlider->SetPos(0);

	SetTimer(1,10,NULL);
}

void CRecorder::KillFile()
{
	KillTimer(1);
	SAFE_DELETE( m_pSound );
	m_pTimer->DeleteBM();	
}

void CRecorder::OnPlay()
{
	if( m_pSound == NULL )
		return;

	m_pTimer->PaintAll();

	if( m_wMode == STATE_PLAYING )
		return;

	m_wMode = STATE_PLAYING;
	
	m_pSound->SetPosition(m_pTimer->m_PlayPos);
	m_pSound->Play();
}

void CRecorder::OnRec()
{
	if( !m_bCanRec )
		return;

	if( AfxMessageBox(IDS_CONFIRMRECORDING,MB_YESNO)==IDNO )
		return;

	SAFE_DELETE( m_pSound );

	m_pSound = new CAudioStream(lpDS_PFL);
	m_pSound->SetFile(m_strFileName.GetBuffer(0));
	
	if( m_pSound->Rec()!=0 )
	{
		SAFE_DELETE( m_pSound );
		return;
	} 
	m_pSound->m_xres = m_pTimer->m_xres;
	
	m_pTimer->SetSpectrum(m_pSound->m_pbm);
	m_pTimer->SetViewPoint(0);

	SetTimer(1,200,NULL);
	m_wMode = STATE_RECORDING; 
}

void CRecorder::OnStop()
{
	if( m_wMode == STATE_RECORDING )
	{
		m_pSound->StopRec();
		m_wMode = 0;
		m_pTimer->SetSpectrum(NULL);
		SetFile( m_strFileName );

		m_pTimer->PaintAll();

		return ;
	}

	if( m_pSound != NULL )
	{
		m_pSound->Pause();
		m_pSound->SetPosition(0);
		m_wMode=0;
	}
}

void CRecorder::OnPause()
{
	if( m_pSound != NULL )
	{
		m_pSound->Pause();
		m_pSound->SetPosition(m_pTimer->m_PlayPos);
		m_wMode = 0;
	}
}

void CRecorder::OnFindPlay()
{
	if( m_pSound!=NULL )
	{
		long int lPos=m_pSound->GetPosition();

		if( lPos<5000 )
			lPos=0;
		else
			lPos-=5000;

		m_pTimer->SetViewPoint( lPos );
		m_pSlider->SetPos( lPos );
	}
}

void CRecorder::OnCheckSound()
{
	m_bCheckSound = !m_bCheckSound;
	m_pSoundCheck->SetCheck( m_bCheckSound );
}

void CRecorder::OnCheckLoop()
{
	m_bCheckLoop = !m_bCheckLoop;
	m_pLoopCheck->SetCheck(m_bCheckLoop);
}

void CRecorder::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	int Pos=m_pSlider->GetPos();
	m_pTimer->SetViewPoint(Pos);
}

void CRecorder::OnResetStart()
{
	m_pTimer->m_Start=0;
	m_pTimer->PaintAll();
	m_pStart->SetWindowText("00:00:00.0");
}

void CRecorder::OnResetFadeIn()
{
	m_pTimer->m_FadeIn=0;
	m_pTimer->PaintAll();
	m_pFadeIn->SetWindowText("00:00:00.0");
}

void CRecorder::OnResetIntro()
{
	m_pTimer->m_Intro=0;
	m_pTimer->PaintAll();
	m_pIntro->SetWindowText("00:00:00.0");
}

void CRecorder::OnResetFadeOut()
{
	m_pTimer->m_FadeOut=0;
	m_pTimer->PaintAll();
	m_pFadeOut->SetWindowText("00:00:00.0");
}

void CRecorder::OnResetMix()
{
	m_pTimer->m_Mix=0;
	m_pTimer->PaintAll();
	m_pMix->SetWindowText("00:00:00.0");
}

void CRecorder::OnResetEnd()
{
	m_pTimer->m_End=0;
	m_pTimer->PaintAll();
	m_pEnd->SetWindowText("00:00:00.0");
}

void CRecorder::OnResetLoopA()
{
	m_pTimer->m_LoopA=0;
	m_pTimer->PaintAll();
	m_pLoopA->SetWindowText("00:00:00.0");
}

void CRecorder::OnResetLoopB()
{
	m_pTimer->m_LoopB=0;
	m_pTimer->PaintAll();
	m_pLoopB->SetWindowText("00:00:00.0");
}

LRESULT CRecorder::OnUpdateTimers(WPARAM,LPARAM)
{
	if( m_pSound==NULL )
		return 0;

	CString str;

	GetTimeString(m_pTimer->m_Start,&str);
	m_pStart->SetWindowText(str);

	GetTimeString(m_pTimer->m_FadeIn,&str);
	m_pFadeIn->SetWindowText(str);

	GetTimeString(m_pTimer->m_Intro,&str);
	m_pIntro->SetWindowText(str);

	GetTimeString(m_pTimer->m_FadeOut,&str);
	m_pFadeOut->SetWindowText(str);

	GetTimeString(m_pTimer->m_Mix,&str);
	m_pMix->SetWindowText(str);

	GetTimeString(m_pTimer->m_End,&str);
	m_pEnd->SetWindowText(str);

	GetTimeString(m_pTimer->m_LoopA,&str);
	m_pLoopA->SetWindowText(str);

	GetTimeString(m_pTimer->m_LoopB,&str);
	m_pLoopB->SetWindowText(str);

	return 0;
}

LRESULT CRecorder::OnGoTo(WPARAM,LPARAM Pos)
{
	if( m_pSound!=NULL )
		m_pSound->SetPosition(Pos);

	return 0;
}

void CRecorder::OnTimer(UINT nIDEvent) 
{
	if( m_wMode == STATE_RECORDING )
	{
		if( (long)m_pSound->GetPosition() > m_pTimer->m_RightPos+10000 ) 
			m_pTimer->SetViewPoint(m_pSound->GetPosition() );
		else
			m_pTimer->PaintAll();

		return;
	}

	if( m_pSound==NULL )
		return;

	m_pTimer->m_PlayPos=m_pSound->GetPosition();
	m_pTimer->PaintCrono();

	if( (m_bCheckLoop) && (m_pTimer->m_LoopB > m_pTimer->m_LoopA) && (m_pTimer->m_LoopB<=m_pTimer->m_PlayPos) )
		m_pSound->SetPosition(m_pTimer->m_LoopA);

	if( m_bCheckSound )
	{
		float fVol;

		if( (m_pTimer->m_PlayPos<m_pTimer->m_Start) || (m_pTimer->m_PlayPos>m_pTimer->m_End) )
			m_pSound->SetVolume(-10000);
		else if( m_pTimer->m_PlayPos < m_pTimer->m_FadeIn ) 
		{
			fVol=-3000*(float)(m_pTimer->m_FadeIn-m_pTimer->m_PlayPos)/(m_pTimer->m_FadeIn-m_pTimer->m_Start);
			m_pSound->SetVolume((long)fVol);
		}
		else if( (m_pTimer->m_PlayPos > m_pTimer->m_FadeOut) && (m_pTimer->m_FadeOut) )
		{
			fVol=-3000*(float)(m_pTimer->m_PlayPos-m_pTimer->m_FadeOut)/(m_pTimer->m_End-m_pTimer->m_FadeOut);
			m_pSound->SetVolume((long)fVol);
		}
		else
			m_pSound->SetVolume(0);
	}

	CStatic::OnTimer(nIDEvent);
}
