// ScheduleSpotDetail.cpp : implementation file
//

#include "stdafx.h"
#include "Traffic.h"
#include "ScheduleSpotDetail.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScheduleSpotDetail dialog


CScheduleSpotDetail::CScheduleSpotDetail(CWnd* pParent /*=NULL*/)
	: CDialog(CScheduleSpotDetail::IDD, pParent)
{
	//{{AFX_DATA_INIT(CScheduleSpotDetail)
	m_strName = _T("");
	m_bSat = FALSE;
	m_dEndingDate = COleDateTime::GetCurrentTime();
	m_bFri = FALSE;
	m_bMon = FALSE;
	m_dStartingDate = COleDateTime::GetCurrentTime();
	m_bSun = FALSE;
	m_bThu = FALSE;
	m_bTue = FALSE;
	m_bWed = FALSE;
	//}}AFX_DATA_INIT
}


void CScheduleSpotDetail::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScheduleSpotDetail)
	DDX_Control(pDX, IDC_STARTINGDATE, m_cStartingDate);
	DDX_Control(pDX, IDC_ENDINGDATE, m_cEndingDate);
	DDX_Text(pDX, IDC_NAME, m_strName);
	DDX_Check(pDX, IDC_SAT, m_bSat);
	DDX_DateTimeCtrl(pDX, IDC_ENDINGDATE, m_dEndingDate);
	DDX_Check(pDX, IDC_FRI, m_bFri);
	DDX_Check(pDX, IDC_MON, m_bMon);
	DDX_DateTimeCtrl(pDX, IDC_STARTINGDATE, m_dStartingDate);
	DDX_Check(pDX, IDC_SUN, m_bSun);
	DDX_Check(pDX, IDC_THU, m_bThu);
	DDX_Check(pDX, IDC_TUE, m_bTue);
	DDX_Check(pDX, IDC_WED, m_bWed);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScheduleSpotDetail, CDialog)
	//{{AFX_MSG_MAP(CScheduleSpotDetail)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScheduleSpotDetail message handlers

void CScheduleSpotDetail::OnOK() 
{
	UpdateData();

	if( (!m_bSun) && (!m_bMon) && (!m_bTue) && (!m_bWed) && (!m_bThu) && (!m_bFri) && (!m_bSat) )
		return;

	if( m_dStartingDate > m_dEndingDate )
		return;

	CDialog::OnOK();
}
