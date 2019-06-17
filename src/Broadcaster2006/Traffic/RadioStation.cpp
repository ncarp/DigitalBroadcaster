// RadioStation.cpp : implementation file
//

#include "stdafx.h"
#include "RadioStation.h"
#include "..\include\RSRadioStations.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CString g_strMainConnect;
/////////////////////////////////////////////////////////////////////////////
// CRadioStation dialog


CRadioStation::CRadioStation(CWnd* pParent /*=NULL*/)
	: CDialog(CRadioStation::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRadioStation)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CRadioStation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRadioStation)
	DDX_Control(pDX, IDC_LIST2, m_cRadios);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRadioStation, CDialog)
	//{{AFX_MSG_MAP(CRadioStation)
	ON_LBN_DBLCLK(IDC_LIST2, OnDblclkList2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRadioStation message handlers

void CRadioStation::OnOK() 
{
	int Pos=m_cRadios.GetCurSel();
	if( Pos==LB_ERR )
		return;

	long RadioID = m_cRadios.GetItemData(Pos);
	CRSRadioStations rs(g_strMainConnect);
	rs.m_strFilter.Format("ID = %d",RadioID);
	rs.Open();
	if( rs.GetRecordCount()==0 )
	{
		rs.Close();
		return;
	}

	m_lRadioID = rs.m_ID;
	m_strConnect = rs.m_DSN;
	m_strConnect.TrimRight();
	m_strRadio = rs.m_Name;
	m_strRadio.TrimRight();
	m_strDB = rs.m_DB;
	m_strDB.TrimRight();

	rs.Close();
	
	CDialog::OnOK();
}

void CRadioStation::OnDblclkList2() 
{
	OnOK();	
}

BOOL CRadioStation::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	int	Pos;
	CRSRadioStations	rs(g_strMainConnect);
	rs.m_strSort="Name";
	rs.Open();

	while( !rs.IsEOF() )
	{
		rs.m_Name.TrimRight();
		Pos=m_cRadios.AddString(rs.m_Name);
		m_cRadios.SetItemData(Pos,rs.m_ID);
		rs.MoveNext();
	}
	
	rs.Close();

	if( m_cRadios.GetCount()==1 )
	{
		m_cRadios.SetCurSel(0);
		OnOK();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
