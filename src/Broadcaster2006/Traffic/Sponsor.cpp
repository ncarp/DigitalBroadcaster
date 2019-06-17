// Sponsor.cpp : implementation file
//

#include "stdafx.h"
#include "traffic.h"
#include "Sponsor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSponsor dialog


CSponsor::CSponsor(CWnd* pParent /*=NULL*/)
	: CDialog(CSponsor::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSponsor)
	m_CustomerName = _T("");
	m_dEndingDate = COleDateTime::GetCurrentTime();
	m_dStartingDate = COleDateTime::GetCurrentTime();
	m_SpotName = _T("");
	//}}AFX_DATA_INIT
}


void CSponsor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSponsor)
	DDX_Text(pDX, IDC_CUSTOMER, m_CustomerName);
	DDX_DateTimeCtrl(pDX, IDC_SPONSOR_ENDINGDATE, m_dEndingDate);
	DDX_DateTimeCtrl(pDX, IDC_SPONSOR_STARTINGDATE, m_dStartingDate);
	DDX_Text(pDX, IDC_SPOTNAME, m_SpotName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSponsor, CDialog)
	//{{AFX_MSG_MAP(CSponsor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSponsor message handlers

void CSponsor::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}
