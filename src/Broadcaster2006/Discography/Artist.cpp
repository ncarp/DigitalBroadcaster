// Artist.cpp : implementation file
//

#include "stdafx.h"
#include "Discography.h"
#include "Artist.h"
#include "..\include\RSRecordLabel.h"
#include "..\include\RSNationalities.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CArtist dialog
extern CString	g_strMainConnect;

CArtist::CArtist(CWnd* pParent /*=NULL*/)
	: CDialog(CArtist::IDD, pParent)
{
	//{{AFX_DATA_INIT(CArtist)
	m_Adress = _T("");
	m_Date = COleDateTime::GetCurrentTime();
	m_eMail = _T("");
	m_FanClub = _T("");
	m_Label = _T("");
	m_Name = _T("");
	m_Nationality = _T("");
	m_Remarks = _T("");
	m_WWW = _T("");
	//}}AFX_DATA_INIT
}


void CArtist::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CArtist)
	DDX_Control(pDX, IDC_NATIONALITY, m_cNationality);
	DDX_Control(pDX, IDC_LABEL, m_cLabel);
	DDX_Text(pDX, IDC_ADRESS, m_Adress);
	DDX_DateTimeCtrl(pDX, IDC_DATE, m_Date);
	DDX_Text(pDX, IDC_EMAIL, m_eMail);
	DDX_Text(pDX, IDC_FANCLUB, m_FanClub);
	DDX_CBString(pDX, IDC_LABEL, m_Label);
	DDX_Text(pDX, IDC_NAME, m_Name);
	DDX_CBString(pDX, IDC_NATIONALITY, m_Nationality);
	DDX_Text(pDX, IDC_REMARCKS, m_Remarks);
	DDX_Text(pDX, IDC_WWW, m_WWW);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CArtist, CDialog)
	//{{AFX_MSG_MAP(CArtist)
	ON_CBN_KILLFOCUS(IDC_LABEL, OnKillfocusLabel)
	ON_CBN_SELCHANGE(IDC_LABEL, OnSelchangeLabel)
	ON_CBN_KILLFOCUS(IDC_NATIONALITY, OnKillfocusNationality)
	ON_CBN_SELCHANGE(IDC_NATIONALITY, OnSelchangeNationality)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CArtist message handlers

BOOL CArtist::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CString str;
	
	str.LoadString(IDS_REFRESH);
	m_cNationality.AddString(str);
	m_cNationality.SetItemData(0,0);

	m_cLabel.AddString(str);
	m_cLabel.SetItemData(0,0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CArtist::OnKillfocusLabel() 
{
	CString str;
	m_cLabel.GetWindowText(str);
	str.TrimRight();
	str.Replace("'","''");

	if(str.GetLength()==0)
	{
		m_LabelID=0;
		return;	
	}

	CRSRecordLabel	rs(g_strMainConnect);
	rs.m_strFilter.Format("Name = '%s'",str);
	rs.Open();

	if( rs.GetRecordCount() )
	{
		rs.m_Name.TrimRight();
		m_cLabel.SetWindowText(rs.m_Name);
		m_LabelID=rs.m_ID;
	}
	else
	{
		if( AfxMessageBox(IDS_NEWLABEL,MB_YESNO)==IDYES )
		{
			m_cLabel.GetWindowText(str);
			str.TrimRight();

			rs.AddNew();
			rs.m_Activ=1;
			rs.m_Name=str;
			rs.Update();

			rs.Requery();
			m_LabelID=rs.m_ID;
		}
		else
		{
			m_cLabel.SetWindowText("");
			m_LabelID=0;
		}
	}
}

void CArtist::OnSelchangeLabel() 
{
	long Pos=m_cLabel.GetCurSel();
	long Data=m_cLabel.GetItemData(Pos);

	m_LabelID=Data;

	if( Data==0 )
	{
		CRSRecordLabel	rs(g_strMainConnect);
		rs.m_strFilter="Activ <> 0";
		rs.m_strSort="Name";
		rs.Open();

		m_cLabel.ResetContent();
	
		while( !rs.IsEOF() )
		{
			rs.m_Name.TrimRight();
			Pos=m_cLabel.AddString(rs.m_Name);
			m_cLabel.SetItemData(Pos,rs.m_ID);
			rs.MoveNext();
		}

		CString str;
		str.LoadString(IDS_REFRESH);

		Pos=m_cLabel.AddString(str);
		m_cLabel.SetItemData(Pos,0);
	}
}

void CArtist::OnKillfocusNationality() 
{
	CString str;
	m_cNationality.GetWindowText(str);
	str.TrimRight();
	str.Replace("'","''");

	if(str.GetLength()==0)
	{
		m_NationalityID=0;
		return;	
	}

	CRSNationalities	rs(g_strMainConnect);
	rs.m_strFilter.Format("Nationality = '%s'",str);
	rs.Open();

	if( rs.GetRecordCount() )
	{
		rs.m_Nationality.TrimRight();
		m_cNationality.SetWindowText(rs.m_Nationality);
		m_NationalityID=rs.m_ID;
	}
	else
	{
		if( AfxMessageBox(IDS_NEWNATIONALITY,MB_YESNO)==IDYES )
		{
			m_cNationality.GetWindowText(str);
			str.TrimRight();

			rs.AddNew();
			rs.m_Activ=1;
			rs.m_Nationality=str;
			rs.m_ZoneID=0;
			rs.Update();

			rs.Requery();
			m_NationalityID=rs.m_ID;
		}
		else
		{
			m_cNationality.SetWindowText("");
			m_NationalityID=0;
		}
	}
}

void CArtist::OnSelchangeNationality() 
{
	long Pos=m_cNationality.GetCurSel();
	long Data=m_cNationality.GetItemData(Pos);

	m_NationalityID=Data;

	if( Data==0 )
	{
		CRSNationalities	rs(g_strMainConnect);
		rs.m_strFilter="Activ <> 0";
		rs.m_strSort="Nationality";
		rs.Open();

		m_cNationality.ResetContent();
	
		while( !rs.IsEOF() )
		{
			rs.m_Nationality.TrimRight();
			Pos=m_cNationality.AddString(rs.m_Nationality);
			m_cNationality.SetItemData(Pos,rs.m_ID);
			rs.MoveNext();
		}

		CString str;
		str.LoadString(IDS_REFRESH);

		Pos=m_cNationality.AddString(str);
		m_cNationality.SetItemData(Pos,0);
	}
}
