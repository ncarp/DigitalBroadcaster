// OnAirUser.cpp : implementation file
//

#include "stdafx.h"
#include "Manager.h"
#include "OnAirUser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COnAirUser dialog


COnAirUser::COnAirUser(CWnd* pParent /*=NULL*/)
	: CDialog(COnAirUser::IDD, pParent)
{
	//{{AFX_DATA_INIT(COnAirUser)
	m_Blocks = FALSE;
	m_MusicEditing = FALSE;
	m_Name = _T("");
	m_Pass1 = _T("");
	m_Pass2 = _T("");
	m_Schedule = FALSE;
	m_SoundRecorder = FALSE;
	//}}AFX_DATA_INIT
}


void COnAirUser::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COnAirUser)
	DDX_Check(pDX, IDC_BLOCKS, m_Blocks);
	DDX_Check(pDX, IDC_MUSICEDITING, m_MusicEditing);
	DDX_Text(pDX, IDC_NAME, m_Name);
	DDX_Text(pDX, IDC_PASS1, m_Pass1);
	DDX_Text(pDX, IDC_PASS2, m_Pass2);
	DDX_Check(pDX, IDC_SCHEDULE, m_Schedule);
	DDX_Check(pDX, IDC_SOUNDRECORDER, m_SoundRecorder);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COnAirUser, CDialog)
	//{{AFX_MSG_MAP(COnAirUser)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COnAirUser message handlers

void COnAirUser::OnOK() 
{
	UpdateData();

	m_Pass1.TrimRight();
	m_Pass2.TrimRight();
	if( m_Pass1!=m_Pass2 )
		return;

	m_Name.TrimRight();
	if( m_Name.GetLength()==0 )
		return;
	
	CDialog::OnOK();
}
