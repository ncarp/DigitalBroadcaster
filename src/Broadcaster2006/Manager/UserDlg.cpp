// UserDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Manager.h"
#include "UserDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserDlg dialog


CUserDlg::CUserDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUserDlg)
	m_bDeleteMusic = FALSE;
	m_bDiscography = FALSE;
	m_bEditMusic = FALSE;
	m_bNewMusic = FALSE;
	m_strName = _T("");
	m_bJinglesCut = FALSE;
	m_bJinglesOnAir = FALSE;
	m_bJinglesNew = FALSE;
	m_bJinglesEdit = FALSE;
	m_bOnAirManagement = FALSE;
	m_bBlocksAdd = FALSE;
	m_bBlocksCut = FALSE;
	m_bBlocksEdit = FALSE;
	m_bPlayListAdd = FALSE;
	m_bPlayListCut = FALSE;
	m_bPlayListEditContents = FALSE;
	m_bPlayListEdit = FALSE;
	m_bTraffic = FALSE;
	m_bSpotsAdd = FALSE;
	m_bSpotsEdit = FALSE;
	m_bSpotsCut = FALSE;
	m_bSponsors = FALSE;
	m_bTrafficAdd = FALSE;
	m_bTrafficCut = FALSE;
	m_bTrafficEdit = FALSE;
	m_bTrafficView = FALSE;
	m_bCriteriaAdd = FALSE;
	m_bCriteriaCut = FALSE;
	m_bCriteriaEdit = FALSE;
	m_bScheduleAuto = FALSE;
	m_bScheduleEdit = FALSE;
	m_bLineupAdd = FALSE;
	m_bLineupCut = FALSE;
	m_bLineupEdit = FALSE;
	m_bScheduler = FALSE;
	m_bVoiceAdd = FALSE;
	m_bVoiceCut = FALSE;
	m_bVoiceEdit = FALSE;
	m_bNewsRoom = FALSE;
	m_bRmsAdd = FALSE;
	m_bRmsCut = FALSE;
	m_bRmsLineup = FALSE;
	m_bRmsOnAir = FALSE;
	m_bTextCut = FALSE;
	m_bTextEdit = FALSE;
	m_bTextLineup = FALSE;
	m_bTextAdd = FALSE;
	m_bTextOnAir = FALSE;
	m_bRmsEdit = FALSE;
	m_bManagerLog = FALSE;
	m_bManagerFolder = FALSE;
	m_bManagerTime = FALSE;
	m_bManagerUser = FALSE;
	m_bInstrumentals = FALSE;
	//}}AFX_DATA_INIT
}


void CUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserDlg)
	DDX_Control(pDX, IDC_INSTRUMENTALS, m_cInstrumentals);
	DDX_Control(pDX, IDC_TEXT_ONAIR, m_cTextOnAir);
	DDX_Control(pDX, IDC_TEXT_NEW, m_cTextAdd);
	DDX_Control(pDX, IDC_TEXT_LINEUP, m_cTextLineup);
	DDX_Control(pDX, IDC_TEXT_EDIT, m_cTextEdit);
	DDX_Control(pDX, IDC_TEXT_CUT, m_cTextCut);
	DDX_Control(pDX, IDC_RMS_ONAIR, m_cRmsOnAir);
	DDX_Control(pDX, IDC_RMS_LINEUP, m_cRmsLineup);
	DDX_Control(pDX, IDC_RMS_EDIT, m_cRmsEdit);
	DDX_Control(pDX, IDC_RMS_CUT, m_cRmsCut);
	DDX_Control(pDX, IDC_RMS_ADD, m_cRmsAdd);
	DDX_Control(pDX, IDC_AUTO_SCHEDULE, m_cScheduleAuto);
	DDX_Control(pDX, IDC_VOICE_EDIT, m_cVoiceEdit);
	DDX_Control(pDX, IDC_VOICE_CUT, m_cVoiceCut);
	DDX_Control(pDX, IDC_VOICE_ADD, m_cVoiceAdd);
	DDX_Control(pDX, IDC_LINEUP_EDIT, m_cLineupEdit);
	DDX_Control(pDX, IDC_LINEUP_CUT, m_cLineupCut);
	DDX_Control(pDX, IDC_LINEUP_ADD, m_cLineupAdd);
	DDX_Control(pDX, IDC_EDIT_SCHEDULE, m_cScheduleEdit);
	DDX_Control(pDX, IDC_CRITERIA_EDIT, m_cCriteriaEdit);
	DDX_Control(pDX, IDC_CRITERIA_CUT, m_cCriteriaCut);
	DDX_Control(pDX, IDC_CRITERIA_ADD, m_cCriteriaAdd);
	DDX_Control(pDX, IDC_TRAFFIC_VIEW, m_cTrafficView);
	DDX_Control(pDX, IDC_TRAFFIC_EDIT, m_cTrafficEdit);
	DDX_Control(pDX, IDC_TRAFFIC_CUT, m_cTrafficCut);
	DDX_Control(pDX, IDC_TRAFFIC_ADD, m_cTrafficAdd);
	DDX_Control(pDX, IDC_SPONSORS, m_cSponsors);
	DDX_Control(pDX, IDC_SPOTS_CUT, m_cSpotsCut);
	DDX_Control(pDX, IDC_SPOTS_EDIT, m_cSpotsEdit);
	DDX_Control(pDX, IDC_SPOTS_NEW, m_cSpotsAdd);
	DDX_Control(pDX, IDC_PLAYLISTEDITCONTENT, m_cPlayListEditContents);
	DDX_Control(pDX, IDC_PLAYLISTEDIT, m_cPlayListEdit);
	DDX_Control(pDX, IDC_PLAYLISTCUT, m_cPlayListCut);
	DDX_Control(pDX, IDC_PLAYLISTADD, m_cPlayListAdd);
	DDX_Control(pDX, IDC_BLOCKS_EDIT, m_cBlocksEdit);
	DDX_Control(pDX, IDC_BLOCKS_CUT, m_cBlocksCut);
	DDX_Control(pDX, IDC_BLOCKS_ADD, m_cBlocksAdd);
	DDX_Control(pDX, IDC_JINGLES_EDIT, m_cJinglesEdit);
	DDX_Control(pDX, IDC_JINGLES_NEW, m_cJinglesNew);
	DDX_Control(pDX, IDC_JINGLES_ONAIR, m_cJinglesOnAir);
	DDX_Control(pDX, IDC_JINGLES_CUT, m_cJinglesCut);
	DDX_Control(pDX, IDC_DISCOGRAPHY, m_cDiscography);
	DDX_Control(pDX, IDC_NEWMUSIC, m_cNewMusic);
	DDX_Control(pDX, IDC_EDITMUSIC, m_cEditMusic);
	DDX_Control(pDX, IDC_DELETEMUSIC, m_cDeleteMusic);
	DDX_Check(pDX, IDC_DELETEMUSIC, m_bDeleteMusic);
	DDX_Check(pDX, IDC_DISCOGRAPHY, m_bDiscography);
	DDX_Check(pDX, IDC_EDITMUSIC, m_bEditMusic);
	DDX_Check(pDX, IDC_NEWMUSIC, m_bNewMusic);
	DDX_Text(pDX, IDC_USER, m_strName);
	DDX_Check(pDX, IDC_JINGLES_CUT, m_bJinglesCut);
	DDX_Check(pDX, IDC_JINGLES_ONAIR, m_bJinglesOnAir);
	DDX_Check(pDX, IDC_JINGLES_NEW, m_bJinglesNew);
	DDX_Check(pDX, IDC_JINGLES_EDIT, m_bJinglesEdit);
	DDX_Check(pDX, IDC_ONAIRMANAGMENT, m_bOnAirManagement);
	DDX_Check(pDX, IDC_BLOCKS_ADD, m_bBlocksAdd);
	DDX_Check(pDX, IDC_BLOCKS_CUT, m_bBlocksCut);
	DDX_Check(pDX, IDC_BLOCKS_EDIT, m_bBlocksEdit);
	DDX_Check(pDX, IDC_PLAYLISTADD, m_bPlayListAdd);
	DDX_Check(pDX, IDC_PLAYLISTCUT, m_bPlayListCut);
	DDX_Check(pDX, IDC_PLAYLISTEDITCONTENT, m_bPlayListEditContents);
	DDX_Check(pDX, IDC_PLAYLISTEDIT, m_bPlayListEdit);
	DDX_Check(pDX, IDC_TRAFFIC, m_bTraffic);
	DDX_Check(pDX, IDC_SPOTS_NEW, m_bSpotsAdd);
	DDX_Check(pDX, IDC_SPOTS_EDIT, m_bSpotsEdit);
	DDX_Check(pDX, IDC_SPOTS_CUT, m_bSpotsCut);
	DDX_Check(pDX, IDC_SPONSORS, m_bSponsors);
	DDX_Check(pDX, IDC_TRAFFIC_ADD, m_bTrafficAdd);
	DDX_Check(pDX, IDC_TRAFFIC_CUT, m_bTrafficCut);
	DDX_Check(pDX, IDC_TRAFFIC_EDIT, m_bTrafficEdit);
	DDX_Check(pDX, IDC_TRAFFIC_VIEW, m_bTrafficView);
	DDX_Check(pDX, IDC_CRITERIA_ADD, m_bCriteriaAdd);
	DDX_Check(pDX, IDC_CRITERIA_CUT, m_bCriteriaCut);
	DDX_Check(pDX, IDC_CRITERIA_EDIT, m_bCriteriaEdit);
	DDX_Check(pDX, IDC_AUTO_SCHEDULE, m_bScheduleAuto);
	DDX_Check(pDX, IDC_EDIT_SCHEDULE, m_bScheduleEdit);
	DDX_Check(pDX, IDC_LINEUP_ADD, m_bLineupAdd);
	DDX_Check(pDX, IDC_LINEUP_CUT, m_bLineupCut);
	DDX_Check(pDX, IDC_LINEUP_EDIT, m_bLineupEdit);
	DDX_Check(pDX, IDC_SCHEDULER, m_bScheduler);
	DDX_Check(pDX, IDC_VOICE_ADD, m_bVoiceAdd);
	DDX_Check(pDX, IDC_VOICE_CUT, m_bVoiceCut);
	DDX_Check(pDX, IDC_VOICE_EDIT, m_bVoiceEdit);
	DDX_Check(pDX, IDC_NEWSROOM, m_bNewsRoom);
	DDX_Check(pDX, IDC_RMS_ADD, m_bRmsAdd);
	DDX_Check(pDX, IDC_RMS_CUT, m_bRmsCut);
	DDX_Check(pDX, IDC_RMS_LINEUP, m_bRmsLineup);
	DDX_Check(pDX, IDC_RMS_ONAIR, m_bRmsOnAir);
	DDX_Check(pDX, IDC_TEXT_CUT, m_bTextCut);
	DDX_Check(pDX, IDC_TEXT_EDIT, m_bTextEdit);
	DDX_Check(pDX, IDC_TEXT_LINEUP, m_bTextLineup);
	DDX_Check(pDX, IDC_TEXT_NEW, m_bTextAdd);
	DDX_Check(pDX, IDC_TEXT_ONAIR, m_bTextOnAir);
	DDX_Check(pDX, IDC_RMS_EDIT, m_bRmsEdit);
	DDX_Check(pDX, IDC_MANAGER_LOG, m_bManagerLog);
	DDX_Check(pDX, IDC_MANAGER_FOLDERS, m_bManagerFolder);
	DDX_Check(pDX, IDC_MANAGER_TIME, m_bManagerTime);
	DDX_Check(pDX, IDC_MANAGER_USER, m_bManagerUser);
	DDX_Check(pDX, IDC_INSTRUMENTALS, m_bInstrumentals);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUserDlg, CDialog)
	//{{AFX_MSG_MAP(CUserDlg)
	ON_BN_CLICKED(IDC_DISCOGRAPHY, OnDiscography)
	ON_BN_CLICKED(IDC_ONAIRMANAGMENT, OnOnairmanagment)
	ON_BN_CLICKED(IDC_TRAFFIC, OnTraffic)
	ON_BN_CLICKED(IDC_SCHEDULER, OnScheduler)
	ON_BN_CLICKED(IDC_NEWSROOM, OnNewsroom)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserDlg message handlers

void CUserDlg::OnDiscography() 
{
	BOOL	bDiscography = (m_cDiscography.GetCheck()==1);
	
	m_cNewMusic.EnableWindow(bDiscography);
	m_cEditMusic.EnableWindow(bDiscography);
	m_cDeleteMusic.EnableWindow(bDiscography);

	if( !bDiscography )
	{
		m_cNewMusic.SetCheck(0);
		m_cEditMusic.SetCheck(0);
		m_cDeleteMusic.SetCheck(0);
	}
}

BOOL CUserDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	OnDiscography();
	OnOnairmanagment();
	OnTraffic();
	OnScheduler();
	OnNewsroom();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CUserDlg::OnOK() 
{
	UpdateData();

	if( m_bDiscography ) m_bDiscography=1;
	if( m_bNewMusic ) m_bNewMusic=1;
	if( m_bEditMusic ) m_bEditMusic=1;
	if( m_bDeleteMusic ) m_bDeleteMusic=1;

	if( m_bOnAirManagement ) m_bOnAirManagement=1;
	if( m_bJinglesNew ) m_bJinglesNew=1;
	if( m_bJinglesEdit ) m_bJinglesEdit=1;
	if( m_bJinglesCut ) m_bJinglesCut=1;
	if( m_bJinglesOnAir ) m_bJinglesOnAir=1;

	if( m_bBlocksAdd ) m_bBlocksAdd = 1;
	if( m_bBlocksEdit ) m_bBlocksEdit = 1;
	if( m_bBlocksCut ) m_bBlocksCut = 1;
	
	if( m_bPlayListAdd ) m_bPlayListAdd = 1;
	if( m_bPlayListEdit) m_bPlayListEdit = 1;
	if( m_bPlayListCut ) m_bPlayListCut = 1;
	if( m_bPlayListEditContents ) m_bPlayListEditContents = 1;

	if( m_bInstrumentals ) m_bInstrumentals = 1;

	if( m_bTraffic ) m_bTraffic = 1;
	if( m_bSpotsAdd ) m_bSpotsAdd = 1;
	if( m_bSpotsEdit) m_bSpotsEdit = 1;
	if( m_bSpotsCut ) m_bSpotsCut = 1;
	if( m_bSponsors ) m_bSponsors = 1;
	if( m_bTrafficView ) m_bTrafficView = 1;
	if( m_bTrafficAdd ) m_bTrafficAdd = 1;
	if( m_bTrafficCut ) m_bTrafficCut = 1;
	if( m_bTrafficEdit ) m_bTrafficEdit = 1;

	if( m_bScheduler )		m_bScheduler = 1;
	if( m_bScheduleEdit )	m_bScheduleEdit = 1;
	if( m_bScheduleAuto )	m_bScheduleAuto = 1;
	if( m_bLineupAdd )		m_bLineupAdd = 1;
	if( m_bLineupEdit )		m_bLineupEdit = 1;
	if( m_bLineupCut )		m_bLineupCut = 1;
	if( m_bCriteriaAdd )	m_bCriteriaAdd = 1;
	if( m_bCriteriaEdit )	m_bCriteriaEdit = 1;
	if( m_bCriteriaCut )	m_bCriteriaCut = 1;
	if( m_bVoiceAdd )		m_bVoiceAdd = 1;
	if( m_bVoiceEdit )		m_bVoiceEdit = 1;
	if( m_bVoiceCut )		m_bVoiceCut = 1;

	if( m_bRmsAdd )			m_bRmsAdd = 1;
	if( m_bRmsEdit )		m_bRmsEdit = 1;
	if( m_bRmsCut )			m_bRmsCut = 1;
	if( m_bRmsOnAir )		m_bRmsOnAir = 1;
	if( m_bRmsLineup )		m_bRmsLineup = 1;

	if( m_bTextAdd )		m_bTextAdd = 1;
	if( m_bTextEdit )		m_bTextEdit = 1;
	if( m_bTextCut )		m_bTextCut = 1;
	if( m_bTextOnAir )		m_bTextOnAir = 1;
	if( m_bTextLineup )		m_bTextLineup = 1;

	if( m_bManagerUser )	m_bManagerUser = 1;
	if( m_bManagerFolder )	m_bManagerFolder = 1;
	if( m_bManagerLog )		m_bManagerLog = 1;
	if( m_bManagerTime )	m_bManagerTime = 1;

	CDialog::OnOK();
}

void CUserDlg::OnOnairmanagment() 
{
	UpdateData();

	m_cJinglesNew.EnableWindow( m_bOnAirManagement );
	m_cJinglesEdit.EnableWindow( m_bOnAirManagement );
	m_cJinglesCut.EnableWindow( m_bOnAirManagement );
	m_cJinglesOnAir.EnableWindow( m_bOnAirManagement );

	m_cBlocksAdd.EnableWindow(m_bOnAirManagement );
	m_cBlocksEdit.EnableWindow(m_bOnAirManagement );
	m_cBlocksCut.EnableWindow(m_bOnAirManagement );

	m_cPlayListAdd.EnableWindow( m_bOnAirManagement );
	m_cPlayListEdit.EnableWindow( m_bOnAirManagement );
	m_cPlayListCut.EnableWindow( m_bOnAirManagement );
	m_cPlayListEditContents.EnableWindow( m_bOnAirManagement );

	m_cInstrumentals.EnableWindow( m_bOnAirManagement );

	if( !m_bOnAirManagement )
	{
		m_cJinglesNew.SetCheck(0);
		m_cJinglesEdit.SetCheck(0);
		m_cJinglesCut.SetCheck(0);
		m_cJinglesOnAir.SetCheck(0);

		m_cBlocksAdd.SetCheck(0);
		m_cBlocksEdit.SetCheck(0);
		m_cBlocksCut.SetCheck(0);

		m_cPlayListAdd.SetCheck(0);
		m_cPlayListEdit.SetCheck(0);
		m_cPlayListCut.SetCheck(0);
		m_cPlayListEditContents.SetCheck(0);

		m_cInstrumentals.SetCheck(0);
	}
}

void CUserDlg::OnTraffic() 
{
	UpdateData();
	
	m_cSpotsAdd.EnableWindow( m_bTraffic );
	m_cSpotsEdit.EnableWindow( m_bTraffic );
	m_cSpotsCut.EnableWindow( m_bTraffic );
	m_cSponsors.EnableWindow( m_bTraffic );
	m_cTrafficView.EnableWindow( m_bTraffic );
	m_cTrafficAdd.EnableWindow( m_bTraffic );
	m_cTrafficEdit.EnableWindow( m_bTraffic );
	m_cTrafficCut.EnableWindow( m_bTraffic );

	if( !m_bTraffic )
	{
		m_cSpotsAdd.SetCheck(0);
		m_cSpotsEdit.SetCheck(0);
		m_cSpotsCut.SetCheck(0);
		m_cSponsors.SetCheck(0);
		m_cTrafficView.SetCheck(0);
		m_cTrafficAdd.SetCheck(0);
		m_cTrafficEdit.SetCheck(0);
		m_cTrafficCut.SetCheck(0);
	}
}

void CUserDlg::OnScheduler() 
{
	UpdateData();

	m_cLineupAdd.EnableWindow( m_bScheduler );
	m_cLineupEdit.EnableWindow( m_bScheduler );
	m_cLineupCut.EnableWindow( m_bScheduler );
	
	m_cCriteriaAdd.EnableWindow( m_bScheduler );
	m_cCriteriaEdit.EnableWindow( m_bScheduler );
	m_cCriteriaCut.EnableWindow( m_bScheduler );

	m_cVoiceAdd.EnableWindow( m_bScheduler );
	m_cVoiceEdit.EnableWindow( m_bScheduler );
	m_cVoiceCut.EnableWindow( m_bScheduler );
	
	m_cScheduleAuto.EnableWindow( m_bScheduler );
	m_cScheduleEdit.EnableWindow( m_bScheduler );

	if( !m_bScheduler )
	{
		m_cLineupAdd.SetCheck(0);
		m_cLineupEdit.SetCheck(0);
		m_cLineupCut.SetCheck(0);
	
		m_cCriteriaAdd.SetCheck(0);
		m_cCriteriaEdit.SetCheck(0);
		m_cCriteriaCut.SetCheck(0);

		m_cVoiceAdd.SetCheck(0);
		m_cVoiceEdit.SetCheck(0);
		m_cVoiceCut.SetCheck(0);
	
		m_cScheduleAuto.SetCheck(0);
		m_cScheduleEdit.SetCheck(0);
	}
}

void CUserDlg::OnNewsroom() 
{
	UpdateData();
	
	m_cRmsAdd.EnableWindow( m_bNewsRoom );
	m_cRmsEdit.EnableWindow( m_bNewsRoom );
	m_cRmsCut.EnableWindow( m_bNewsRoom );
	m_cRmsOnAir.EnableWindow( m_bNewsRoom );
	m_cRmsLineup.EnableWindow( m_bNewsRoom );

	m_cTextAdd.EnableWindow( m_bNewsRoom );
	m_cTextEdit.EnableWindow( m_bNewsRoom );
	m_cTextCut.EnableWindow( m_bNewsRoom );
	m_cTextOnAir.EnableWindow( m_bNewsRoom );
	m_cTextLineup.EnableWindow( m_bNewsRoom );

	if( !m_bNewsRoom )
	{
		m_cRmsAdd.SetCheck( 0 );
		m_cRmsEdit.SetCheck( 0 );
		m_cRmsCut.SetCheck( 0 );
		m_cRmsOnAir.SetCheck( 0 );
		m_cRmsLineup.SetCheck( 0 );

		m_cTextAdd.SetCheck( 0 );
		m_cTextEdit.SetCheck( 0 );
		m_cTextCut.SetCheck( 0 );
		m_cTextOnAir.SetCheck( 0 );
		m_cTextLineup.SetCheck( 0 );
	}
}
