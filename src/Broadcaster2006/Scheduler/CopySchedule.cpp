// CopySchedule.cpp : implementation file
//
#include "stdafx.h"
#include "Scheduler.h"
#include "CopySchedule.h"
#include ".\copyschedule.h"
#include "..\include\rsradiostations.h"
#include "..\common\include\global.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCopySchedule dialog


CCopySchedule::CCopySchedule(CWnd* pParent /*=NULL*/)
	: CDialog(CCopySchedule::IDD, pParent)
	, m_bBlocked(FALSE)
{
	//{{AFX_DATA_INIT(CCopySchedule)
	m_bJingles = FALSE;
	m_bMusic = FALSE;
	m_bOther = FALSE;
	m_bVoice = FALSE;
	//}}AFX_DATA_INIT
	m_Data.bNewMusic=TRUE;	
	m_Data.bNewJingles=TRUE;
	m_Data.bNewVoice=TRUE;
	m_Copy = -1;
	m_bCopyAll = FALSE;
	m_bBlocked = FALSE;
}

void CCopySchedule::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCopySchedule)
	DDX_Control(pDX, IDC_NEWVOICE, m_cNewVoice);
	DDX_Control(pDX, IDC_SAMEVOICE, m_cSameVoice);
	DDX_Control(pDX, IDC_NEWJINGLE, m_cNewJingles);
	DDX_Control(pDX, IDC_SAMEJINGLE, m_cSameJingles);
	DDX_Control(pDX, IDC_SAMEMUSIC, m_cSameMusic);
	DDX_Control(pDX, IDC_NEWMUSIC, m_cNewMusic);
	DDX_Control(pDX, IDC_COPYALL, m_cCopyAll);
	DDX_Check(pDX, IDC_JINGLES, m_bJingles);
	DDX_Check(pDX, IDC_MUSIC, m_bMusic);
	DDX_Check(pDX, IDC_OTHER, m_bOther);
	DDX_Check(pDX, IDC_VOICE, m_bVoice);
	DDX_Check(pDX, IDC_COPYALL, m_bCopyAll);
	//}}AFX_DATA_MAP
	DDX_Check(pDX, IDC_BLOCKED, m_bBlocked);
}

BEGIN_MESSAGE_MAP(CCopySchedule, CDialog)
	//{{AFX_MSG_MAP(CCopySchedule)
	ON_BN_CLICKED(IDC_MUSIC, OnMusic)
	ON_BN_CLICKED(IDC_NEWMUSIC, OnNewmusic)
	ON_BN_CLICKED(IDC_SAMEMUSIC, OnSamemusic)
	ON_BN_CLICKED(IDC_JINGLES, OnJingles)
	ON_BN_CLICKED(IDC_VOICE, OnVoice)
	ON_BN_CLICKED(IDC_NEWJINGLE, OnNewjingle)
	ON_BN_CLICKED(IDC_SAMEJINGLE, OnSamejingle)
	ON_BN_CLICKED(IDC_NEWVOICE, OnNewvoice)
	ON_BN_CLICKED(IDC_SAMEVOICE, OnSamevoice)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCopySchedule message handlers

void CCopySchedule::OnOK() 
{
	UpdateData();

	if( !m_bMusic && !m_bJingles && !m_bVoice && !m_bOther)
		return;
	
	m_Data.bMusic = m_bMusic;
	m_Data.bJingles = m_bJingles;
	m_Data.bVoice = m_bVoice;
	m_Data.bOthers = m_bOther;
	m_Data.bBlocked = m_bBlocked;
	CDialog::OnOK();
}

void CCopySchedule::OnMusic() 
{
	UpdateData();

	m_cNewMusic.EnableWindow(m_bMusic);
	m_cSameMusic.EnableWindow(m_bMusic);
}

BOOL CCopySchedule::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_cNewMusic.SetCheck(1);
	m_cNewJingles.SetCheck(1);
	m_cNewVoice.SetCheck(1);
	
	CRSRadioStations	rs(g_strMainConnect);
	rs.Open();
	rs.MoveFirst();
	if( rs.IsEOF() )
		m_cCopyAll.EnableWindow(0);
	else
		m_cCopyAll.EnableWindow(1);
	rs.Close();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCopySchedule::OnNewmusic() 
{
	m_Data.bNewMusic=TRUE;	
}

void CCopySchedule::OnSamemusic() 
{
	m_Data.bNewMusic=FALSE;	
}

void CCopySchedule::OnJingles() 
{
	UpdateData();
	m_cNewJingles.EnableWindow(m_bJingles);
	m_cSameJingles.EnableWindow(m_bJingles);
}

void CCopySchedule::OnVoice() 
{
	UpdateData();
	m_cNewVoice.EnableWindow(m_bVoice);
	m_cSameVoice.EnableWindow(m_bVoice);	
}

void CCopySchedule::OnNewjingle() 
{
	m_Data.bNewJingles=TRUE;	
}

void CCopySchedule::OnSamejingle() 
{
	m_Data.bNewJingles=FALSE;	
}

void CCopySchedule::OnNewvoice() 
{
	m_Data.bNewVoice=TRUE;	
}

void CCopySchedule::OnSamevoice() 
{
	m_Data.bNewVoice=FALSE;	
}

