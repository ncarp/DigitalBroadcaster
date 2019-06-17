// Schedule.cpp : implementation file
//

#include "stdafx.h"

#include "Schedule.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Schedule dialog


Schedule::Schedule(CWnd* pParent /*=NULL*/)
	: CDialog(Schedule::IDD, pParent)
{
	//{{AFX_DATA_INIT(Schedule)
	m_EndingDate = COleDateTime::GetCurrentTime();
	m_Length = COleDateTime::GetCurrentTime();
	m_Name = _T("");
	m_Precision = -1;
	m_StartingTime = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
}


void Schedule::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Schedule)
	DDX_DateTimeCtrl(pDX, IDC_ENDINGDATE, m_EndingDate);
	DDX_DateTimeCtrl(pDX, IDC_LENGTH, m_Length);
	DDX_Text(pDX, IDC_NAME, m_Name);
	DDX_CBIndex(pDX, IDC_PRECISION, m_Precision);
	DDX_DateTimeCtrl(pDX, IDC_STARTINGTIME, m_StartingTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Schedule, CDialog)
	//{{AFX_MSG_MAP(Schedule)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_STARTINGTIME, OnDatetimechangeStartingtime)
	ON_NOTIFY(NM_KILLFOCUS, IDC_STARTINGTIME, OnKillfocusStartingtime)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_LENGTH, OnDatetimechangeLength)
	ON_NOTIFY(NM_KILLFOCUS, IDC_LENGTH, OnKillfocusLength)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Schedule message handlers

void Schedule::OnDatetimechangeStartingtime(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	ComputeEndingTime();
	*pResult = 0;
}

void Schedule::OnKillfocusStartingtime(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	ComputeEndingTime();
	*pResult = 0;
}

void Schedule::OnDatetimechangeLength(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	ComputeEndingTime();
	*pResult = 0;
}

void Schedule::OnKillfocusLength(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	ComputeEndingTime();
	*pResult = 0;
}

void Schedule::ComputeEndingTime()
{
	UpdateData();

	m_EndingDate = m_StartingTime + COleDateTimeSpan(0,m_Length.GetHour(),m_Length.GetMinute(),m_Length.GetMinute() );

	UpdateData(FALSE);
}

BOOL Schedule::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CString str;
	str.Format(IDS_FORMAT_SCHEDULETO,m_Year,m_Month,m_Day);
	SetWindowText(str);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Schedule::OnOK() 
{
	UpdateData();
	
	m_Name.TrimRight();

	if( m_Name.GetLength()==0 ) return;
	if( m_Precision==CB_ERR ) return;
	
	CDialog::OnOK();
}
