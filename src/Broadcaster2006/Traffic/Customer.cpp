// Customer.cpp : implementation file
//

#include "stdafx.h"
#include "Traffic.h"
#include "Customer.h"
#include "TrafficExternals.h"
#include "..\include\RSBusiness.h"
#include "..\include\RSSalesman.h"
#include "..\include\RSAgency.h"
#include "..\common\include\defines.h"
#include "..\common\include\permissions.h"
#include "..\common\include\global.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomer dialog


CCustomer::CCustomer(CWnd* pParent /*=NULL*/)
	: CDialog(CCustomer::IDD, pParent)
	, m_strNumber(_T(""))
	, m_strName2(_T(""))
	, m_strCelPhone(_T(""))
	, m_strNC2(_T(""))
{
	//{{AFX_DATA_INIT(CCustomer)
	m_strAdress = _T("");
	m_strAgency = _T("");
	m_strBusiness = _T("");
	m_strContact = _T("");
	m_stremail = _T("");
	m_strFax = _T("");
	m_strFN = _T("");
	m_strName = _T("");
	m_strOBS = _T("");
	m_strPhone = _T("");
	m_strSales = _T("");
	m_strZIP = _T("");
	m_strWWW = _T("");
	//}}AFX_DATA_INIT
}


void CCustomer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustomer)
	DDX_Control(pDX, IDC_CUSTOMER_SALES, m_cSales);
	DDX_Control(pDX, IDC_CUSTOMER_BUSINESS, m_cBusiness);
	DDX_Control(pDX, IDC_CUSTOMER_AGENCY, m_cAgency);
	DDX_Text(pDX, IDC_CUSTOMER_ADRESS, m_strAdress);
	DDV_MaxChars(pDX, m_strAdress, 255);
	DDX_CBString(pDX, IDC_CUSTOMER_AGENCY, m_strAgency);
	DDV_MaxChars(pDX, m_strAgency, 100);
	DDX_CBString(pDX, IDC_CUSTOMER_BUSINESS, m_strBusiness);
	DDV_MaxChars(pDX, m_strBusiness, 100);
	DDX_Text(pDX, IDC_CUSTOMER_CONTACT, m_strContact);
	DDV_MaxChars(pDX, m_strContact, 100);
	DDX_Text(pDX, IDC_CUSTOMER_EMAIL, m_stremail);
	DDV_MaxChars(pDX, m_stremail, 100);
	DDX_Text(pDX, IDC_CUSTOMER_FAX, m_strFax);
	DDV_MaxChars(pDX, m_strFax, 100);
	DDX_Text(pDX, IDC_CUSTOMER_FN, m_strFN);
	DDV_MaxChars(pDX, m_strFN, 20);
	DDX_Text(pDX, IDC_CUSTOMER_NAME, m_strName);
	DDV_MaxChars(pDX, m_strName, 100);
	DDX_Text(pDX, IDC_CUSTOMER_OBS, m_strOBS);
	DDX_Text(pDX, IDC_CUSTOMER_PHONE, m_strPhone);
	DDV_MaxChars(pDX, m_strPhone, 100);
	DDX_CBString(pDX, IDC_CUSTOMER_SALES, m_strSales);
	DDV_MaxChars(pDX, m_strSales, 100);
	DDX_Text(pDX, IDC_CUSTOMER_ZIP, m_strZIP);
	DDV_MaxChars(pDX, m_strZIP, 100);
	DDX_Text(pDX, IDC_CUSTOMER_WWW, m_strWWW);
	DDV_MaxChars(pDX, m_strWWW, 100);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_CUSTOMER_NUMBER, m_strNumber);
	DDV_MaxChars(pDX, m_strNumber, 20);
	DDX_Text(pDX, IDC_CUSTOMER_NAME2, m_strName2);
	DDV_MaxChars(pDX, m_strName2, 100);
	DDX_Text(pDX, IDC_CUSTOMER_CELPHONE, m_strCelPhone);
	DDV_MaxChars(pDX, m_strCelPhone, 100);
	DDX_Text(pDX, IDC_CUSTOMER_FN2, m_strNC2);
}


BEGIN_MESSAGE_MAP(CCustomer, CDialog)
	//{{AFX_MSG_MAP(CCustomer)
	ON_CBN_KILLFOCUS(IDC_CUSTOMER_BUSINESS, OnKillfocusCustomerBusiness)
	ON_CBN_SELCHANGE(IDC_CUSTOMER_BUSINESS, OnSelchangeCustomerBusiness)
	ON_CBN_KILLFOCUS(IDC_CUSTOMER_AGENCY, OnKillfocusCustomerAgency)
	ON_CBN_SELCHANGE(IDC_CUSTOMER_AGENCY, OnSelchangeCustomerAgency)
	ON_CBN_KILLFOCUS(IDC_CUSTOMER_SALES, OnKillfocusCustomerSales)
	ON_CBN_SELCHANGE(IDC_CUSTOMER_SALES, OnSelchangeCustomerSales)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomer message handlers

void CCustomer::OnKillfocusCustomerBusiness() 
{
	CString str;
	m_cBusiness.GetWindowText(str);
	str.TrimRight();
	str.Replace("'","''");

	if( str.GetLength()==0 )
		return;

	CRSBusiness	rs(g_strMainConnect);
	rs.m_strFilter.Format("Name = '%s'",str);
	rs.Open();

	if( rs.GetRecordCount() )
	{
		rs.m_Name.TrimRight();
		m_cBusiness.SetWindowText(rs.m_Name);
		m_BusinessID=rs.m_ID;
	}
	else
	{
		if( AfxMessageBox(IDS_NEWBUSINESS,MB_YESNO)==IDYES )
		{
			rs.AddNew();
			m_cBusiness.GetWindowText(rs.m_Name);
			rs.Update();

			rs.Requery();
			m_BusinessID=rs.m_ID;
			WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_ADD,TYPE_BUSINESS,m_BusinessID);
		}
		else
		{
			m_cBusiness.SetWindowText("");
			m_BusinessID=0;
		}
	}
	rs.Close();
}

void CCustomer::OnSelchangeCustomerBusiness() 
{
	int Pos=m_cBusiness.GetCurSel();
	if( Pos==CB_ERR )
		return;

	long lData=m_cBusiness.GetItemData(Pos);
	if( lData==0 )
		FillBusinessList();
}

void CCustomer::OnKillfocusCustomerAgency() 
{
	CString str;
	m_cAgency.GetWindowText(str);
	str.TrimRight();
	str.Replace("'","''");

	if( str.GetLength()==0 )
		return;

	CRSAgency	rs(g_strMainConnect);
	rs.m_strFilter.Format("Name = '%s'",str);
	rs.Open();

	if( rs.GetRecordCount() )
	{
		rs.m_Name.TrimRight();
		m_cAgency.SetWindowText(rs.m_Name);
		m_AgencyID=rs.m_ID;
	}
	else
	{
		if( AfxMessageBox(IDS_NEWAGENCY,MB_YESNO)==IDYES )
		{
			rs.AddNew();
			m_cAgency.GetWindowText(rs.m_Name);
			rs.Update();

			rs.Requery();
			m_AgencyID=rs.m_ID;
			WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_ADD,TYPE_AGENCY,m_AgencyID);
		}
		else
		{
			m_cAgency.SetWindowText("");
			m_AgencyID=0;
		}
	}
	rs.Close();
}

void CCustomer::OnSelchangeCustomerAgency() 
{
	int Pos=m_cAgency.GetCurSel();
	if( Pos==CB_ERR )
		return;

	long lData=m_cAgency.GetItemData(Pos);
	if( lData==0 )
		FillAgencyList();
}

void CCustomer::OnKillfocusCustomerSales() 
{
	CString str;
	m_cSales.GetWindowText(str);
	str.TrimRight();
	str.Replace("'","''");

	if( str.GetLength()==0 )
		return;

	CRSSalesman	rs(g_strMainConnect);
	rs.m_strFilter.Format("Name = '%s'",str);
	rs.Open();

	if( rs.GetRecordCount() )
	{
		rs.m_Name.TrimRight();
		m_cSales.SetWindowText(rs.m_Name);
		m_SalesID=rs.m_ID;
	}
	else
	{
		if( AfxMessageBox(IDS_NEWSALESMAN,MB_YESNO)==IDYES )
		{
			rs.AddNew();
			m_cSales.GetWindowText(rs.m_Name);
			rs.Update();

			rs.Requery();
			m_SalesID=rs.m_ID;
			WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_ADD,TYPE_SALESMAN,m_SalesID);
		}
		else
		{
			m_cSales.SetWindowText("");
			m_SalesID=0;
		}
	}
	rs.Close();
}

void CCustomer::OnSelchangeCustomerSales() 
{
	int Pos=m_cSales.GetCurSel();
	if( Pos==CB_ERR )
		return;

	long lData=m_cSales.GetItemData(Pos);
	if( lData==0 )
		FillSalesmanList();
}

void CCustomer::FillBusinessList()
{
	CString	str;
	long	Pos;
	CRSBusiness rs(g_strMainConnect);
	rs.m_strFilter="Activ = 1";
	rs.m_strSort="Name";
	rs.Open();

	m_cBusiness.ResetContent();

	while( !rs.IsEOF() )
	{
		rs.m_Name.TrimRight();

		Pos=m_cBusiness.AddString(rs.m_Name);
		m_cBusiness.SetItemData(Pos,rs.m_ID);

		rs.MoveNext();
	}
	
	str.LoadString(IDS_REFRESH);
	Pos=m_cBusiness.AddString(str);
	m_cBusiness.SetItemData(Pos,0);
	rs.Close();
}

void CCustomer::FillSalesmanList()
{
	CString	str;
	long	Pos;
	CRSSalesman rs(g_strMainConnect);
	rs.m_strFilter="Activ = 1";
	rs.m_strSort="Name";
	rs.Open();

	m_cSales.ResetContent();

	while( !rs.IsEOF() )
	{
		rs.m_Name.TrimRight();

		Pos=m_cSales.AddString(rs.m_Name);
		m_cSales.SetItemData(Pos,rs.m_ID);

		rs.MoveNext();
	}
	
	str.LoadString(IDS_REFRESH);
	Pos=m_cSales.AddString(str);
	m_cSales.SetItemData(Pos,0);

	rs.Close();
}

void CCustomer::FillAgencyList()
{
	CString	str;
	long	Pos;
	CRSAgency rs(g_strMainConnect);
	rs.m_strFilter="Activ = 1";
	rs.m_strSort="Name";
	rs.Open();

	m_cAgency.ResetContent();

	while( !rs.IsEOF() )
	{
		rs.m_Name.TrimRight();

		Pos=m_cAgency.AddString(rs.m_Name);
		m_cAgency.SetItemData(Pos,rs.m_ID);

		rs.MoveNext();
	}
	
	str.LoadString(IDS_REFRESH);
	Pos=m_cAgency.AddString(str);
	m_cAgency.SetItemData(Pos,0);

	rs.Close();
}

BOOL CCustomer::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CString str;
	str.LoadString(IDS_REFRESH);

	m_cAgency.AddString(str);
	m_cAgency.SetItemData(0,0);
	
	m_cSales.AddString(str);
	m_cSales.SetItemData(0,0);

	m_cBusiness.AddString(str);
	m_cBusiness.SetItemData(0,0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCustomer::OnOK() 
{
	UpdateData();

	if( m_strName.GetLength()==0 )
		return;
	
	CDialog::OnOK();
}
