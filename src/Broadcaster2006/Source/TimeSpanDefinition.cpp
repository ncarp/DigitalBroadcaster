// TimeSpanDefinition.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\TimeSpanDefinition.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTimeSpanDefinition dialog


CTimeSpanDefinition::CTimeSpanDefinition(CWnd* pParent /*=NULL*/)
	: CDialog(CTimeSpanDefinition::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTimeSpanDefinition)
	m_EndingDate = COleDateTime::GetCurrentTime();
	m_Name = _T("");
	m_StartingDate = COleDateTime::GetCurrentTime();
	m_Type = _T("");
	//}}AFX_DATA_INIT
}


void CTimeSpanDefinition::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTimeSpanDefinition)
	DDX_DateTimeCtrl(pDX, IDC_ENDINGDATE, m_EndingDate);
	DDX_Text(pDX, IDC_NAME, m_Name);
	DDX_DateTimeCtrl(pDX, IDC_STARTINGDATE, m_StartingDate);
	DDX_Text(pDX, IDC_TYPE, m_Type);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTimeSpanDefinition, CDialog)
	//{{AFX_MSG_MAP(CTimeSpanDefinition)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimeSpanDefinition message handlers

void CTimeSpanDefinition::OnOK() 
{
	UpdateData();

	if( m_StartingDate > m_EndingDate ) 
		return;
	
	CDialog::OnOK();
}
