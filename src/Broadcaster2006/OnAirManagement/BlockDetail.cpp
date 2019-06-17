// BlockDetail.cpp : implementation file
//

#include "stdafx.h"
#include "OnAirManagement.h"
#include "BlockDetail.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBlockDetail dialog


CBlockDetail::CBlockDetail(CWnd* pParent /*=NULL*/)
	: CDialog(CBlockDetail::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBlockDetail)
	m_EndingDate = COleDateTime::GetCurrentTime();
	m_Fri = FALSE;
	m_Mon = FALSE;
	m_Name = _T("");
	m_Sat = FALSE;
	m_StartingDate = COleDateTime::GetCurrentTime();
	m_Sun = FALSE;
	m_Thu = FALSE;
	m_Tue = FALSE;
	m_Wed = FALSE;
	//}}AFX_DATA_INIT
}


void CBlockDetail::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBlockDetail)
	DDX_DateTimeCtrl(pDX, IDC_ENDINGDATE, m_EndingDate);
	DDX_Check(pDX, IDC_FRI, m_Fri);
	DDX_Check(pDX, IDC_MON, m_Mon);
	DDX_Text(pDX, IDC_NAME, m_Name);
	DDX_Check(pDX, IDC_SAT, m_Sat);
	DDX_DateTimeCtrl(pDX, IDC_STARTINGDATE, m_StartingDate);
	DDX_Check(pDX, IDC_SUN, m_Sun);
	DDX_Check(pDX, IDC_THU, m_Thu);
	DDX_Check(pDX, IDC_TUE, m_Tue);
	DDX_Check(pDX, IDC_WED, m_Wed);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBlockDetail, CDialog)
	//{{AFX_MSG_MAP(CBlockDetail)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBlockDetail message handlers
