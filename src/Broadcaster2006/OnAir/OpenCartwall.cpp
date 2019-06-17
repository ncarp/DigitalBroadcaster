// OpenCartwall.cpp : implementation file
//

#include "stdafx.h"
#include "onair.h"
#include "OpenCartwall.h"
#include "ExternalObjects.h"
#include "..\include\RSCartwallDefinition.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COpenCartwall dialog


COpenCartwall::COpenCartwall(CWnd* pParent /*=NULL*/)
	: CDialog(COpenCartwall::IDD, pParent)
{
	//{{AFX_DATA_INIT(COpenCartwall)
	m_Info = FALSE;
	m_Cart = -1;
	//}}AFX_DATA_INIT
}


void COpenCartwall::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COpenCartwall)
	DDX_Control(pDX, IDC_LIST1, m_cList);
	DDX_Check(pDX, IDC_INFO, m_Info);
	DDX_LBIndex(pDX, IDC_LIST1, m_Cart);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COpenCartwall, CDialog)
	//{{AFX_MSG_MAP(COpenCartwall)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
	ON_BN_CLICKED(IDC_INFO, OnInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COpenCartwall message handlers

void COpenCartwall::OnDblclkList1() 
{
	// TODO: Add your control notification handler code here
	
}

void COpenCartwall::OnOK() 
{
	UpdateData();

	if( m_Cart==LB_ERR )
		return;

	m_cList.GetText(m_Cart,m_strCartName);
	m_CartID = m_cList.GetItemData(m_Cart);
	
	CDialog::OnOK();
}

void COpenCartwall::OnInfo() 
{
	UpdateData();

	CRSCartwallDefinition rs( g_strOnAirConnect );

	if( m_Info )
		rs.m_strFilter="Info = 1";
	else
		rs.m_strFilter="Info = 0";

	rs.m_strSort="Name";
	rs.Open();

	int Pos;
	m_cList.ResetContent();

	while( !rs.IsEOF() )
	{
		rs.m_Name.TrimRight();
		
		Pos=m_cList.InsertString(-1,rs.m_Name);
		m_cList.SetItemData(Pos,rs.m_ID);

		rs.MoveNext();
	}
	rs.Close();
	
}

BOOL COpenCartwall::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CRSCartwallDefinition rs( g_strOnAirConnect );
	rs.m_strFilter="Info = 0";
	rs.m_strSort="Name";
	rs.Open();

	int Pos;

	while( !rs.IsEOF() )
	{
		rs.m_Name.TrimRight();
		
		Pos=m_cList.InsertString(-1,rs.m_Name);
		m_cList.SetItemData(Pos,rs.m_ID);

		rs.MoveNext();
	}
	rs.Close();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
