// DaysDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Scheduler.h"
#include "DaysDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDaysDlg dialog


CDaysDlg::CDaysDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDaysDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDaysDlg)
	m_nDays = 0;
	//}}AFX_DATA_INIT
}


void CDaysDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDaysDlg)
	DDX_Text(pDX, IDC_EDIT1, m_nDays);
	DDV_MinMaxInt(pDX, m_nDays, 1, 366);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDaysDlg, CDialog)
	//{{AFX_MSG_MAP(CDaysDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDaysDlg message handlers
