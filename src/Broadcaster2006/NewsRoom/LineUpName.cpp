// LineUpName.cpp : implementation file
//

#include "stdafx.h"
#include "NewsRoom.h"
#include "LineUpName.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLineUpName dialog


CLineUpName::CLineUpName(CWnd* pParent /*=NULL*/)
	: CDialog(CLineUpName::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLineUpName)
	m_Name = _T("");
	//}}AFX_DATA_INIT
}


void CLineUpName::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLineUpName)
	DDX_Text(pDX, IDC_NAME, m_Name);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLineUpName, CDialog)
	//{{AFX_MSG_MAP(CLineUpName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLineUpName message handlers

void CLineUpName::OnOK() 
{
	UpdateData();

	m_Name.TrimRight();
	if( m_Name.GetLength()==0 )
		return;
	
	CDialog::OnOK();
}
