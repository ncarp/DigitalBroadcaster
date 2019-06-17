// NewCartwall.cpp : implementation file
//

#include "stdafx.h"
#include "onair.h"
#include "NewCartwall.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewCartwall dialog


CNewCartwall::CNewCartwall(CWnd* pParent /*=NULL*/)
	: CDialog(CNewCartwall::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewCartwall)
	m_Name = _T("");
	//}}AFX_DATA_INIT
}


void CNewCartwall::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewCartwall)
	DDX_Text(pDX, IDC_NAME, m_Name);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewCartwall, CDialog)
	//{{AFX_MSG_MAP(CNewCartwall)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewCartwall message handlers

void CNewCartwall::OnOK() 
{
	UpdateData();

	m_Name.TrimRight();
	if( m_Name.GetLength()==0 )
		return;
	
	CDialog::OnOK();
}
