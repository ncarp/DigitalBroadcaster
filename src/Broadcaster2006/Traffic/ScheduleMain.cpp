// ScheduleMain.cpp : implementation file
//

#include "stdafx.h"
#include "Traffic.h"
#include "ScheduleMain.h"
#include "TrafficExternals.h"
#include "..\include\RSCustomersList.h"
#include "..\include\RSRadioStations.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScheduleMain property page

IMPLEMENT_DYNCREATE(CScheduleMain, CPropertyPage)

CScheduleMain::CScheduleMain() : CPropertyPage(CScheduleMain::IDD)
, m_strPI(_T(""))
{
	//{{AFX_DATA_INIT(CScheduleMain)
	m_dEndingDate = COleDateTime::GetCurrentTime();
	m_dFinalHour = COleDateTime::GetCurrentTime();
	m_iNumber = 0;
	m_dStartingDate = COleDateTime::GetCurrentTime();
	m_fValue = 0.0f;
	m_dStartingHour = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
	m_lCustomerID=0;
	m_lStationID=0;
	m_bIsNew = TRUE;
}

CScheduleMain::~CScheduleMain()
{
}

void CScheduleMain::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScheduleMain)
	DDX_Control(pDX, IDC_STARTINGHOUR, m_cStartingHour);
	DDX_Control(pDX, IDC_STARTINGDATE, m_cStartingDate);
	DDX_Control(pDX, IDC_RADIOSTATION, m_cRadioStation);
	DDX_Control(pDX, IDC_NUMBER, m_cNumber);
	DDX_Control(pDX, IDC_FINALHOUR, m_cFinalHour);
	DDX_Control(pDX, IDC_ENDINGDATE, m_cEndingDate);
	DDX_Control(pDX, IDC_CUSTOMER, m_cCustomer);
	DDX_DateTimeCtrl(pDX, IDC_ENDINGDATE, m_dEndingDate);
	DDX_DateTimeCtrl(pDX, IDC_FINALHOUR, m_dFinalHour);
	DDX_Text(pDX, IDC_NUMBER, m_iNumber);
	DDX_DateTimeCtrl(pDX, IDC_STARTINGDATE, m_dStartingDate);
	DDX_Text(pDX, IDC_VALUE, m_fValue);
	DDX_DateTimeCtrl(pDX, IDC_STARTINGHOUR, m_dStartingHour);
	DDX_Text(pDX, IDC_PI, m_strPI);
	//}}AFX_DATA_MAP
	
	DDV_MaxChars(pDX, m_strPI, 20);
}


BEGIN_MESSAGE_MAP(CScheduleMain, CPropertyPage)
	//{{AFX_MSG_MAP(CScheduleMain)
	ON_CBN_KILLFOCUS(IDC_CUSTOMER, OnKillfocusCustomer)
	ON_NOTIFY(NM_KILLFOCUS, IDC_STARTINGDATE, OnKillfocusNotify)
	ON_NOTIFY(NM_SETFOCUS, IDC_ENDINGDATE, OnSetfocusNotify)
	ON_BN_CLICKED(IDC_BYNUMBER, OnBynumber)
	ON_BN_CLICKED(IDC_BYDATE, OnBydate)
	ON_CBN_KILLFOCUS(IDC_RADIOSTATION, OnKillfocusRadiostation)
	ON_BN_CLICKED(IDC_BYINSERT, OnByinsert)
	ON_NOTIFY(NM_KILLFOCUS, IDC_STARTINGHOUR, OnKillfocusNotify)
	ON_NOTIFY(NM_KILLFOCUS, IDC_FINALHOUR, OnKillfocusNotify)
	ON_NOTIFY(NM_KILLFOCUS, IDC_ENDINGDATE, OnKillfocusNotify)
	ON_EN_KILLFOCUS(IDC_NUMBER, CheckData)
	ON_EN_CHANGE(IDC_NUMBER, CheckData)
	ON_BN_CLICKED(IDC_BYCONTRACT, OnBycontract)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScheduleMain message handlers

BOOL CScheduleMain::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	CRSCustomersList	rsCustomer(g_strMainConnect);
	CRSRadioStations	rsStation(g_strMainConnect);
	long	lPos;

	rsCustomer.m_strFilter="ID IN (Select CustomerID FROM Spots WHERE Activ=1)";
	rsCustomer.m_strSort="Name";
	rsCustomer.Open();

	rsStation.m_strSort="Name";
	rsStation.Open();

	while( !rsCustomer.IsEOF() )
	{
		rsCustomer.m_Name.TrimRight();
		lPos=m_cCustomer.AddString(rsCustomer.m_Name);
		m_cCustomer.SetItemData(lPos,rsCustomer.m_ID);
		rsCustomer.MoveNext();
	}
	lPos=m_cCustomer.FindStringExact(-1,m_strCustomer);
	m_cCustomer.SetCurSel(lPos);

	rsCustomer.Close();

	while( !rsStation.IsEOF() )
	{
		rsStation.m_Name.TrimRight();
		lPos=m_cRadioStation.AddString(rsStation.m_Name);
		m_cRadioStation.SetItemData(lPos,rsStation.m_ID);
		rsStation.MoveNext();
	}

	if( m_cRadioStation.GetCount()==1 )
	{
		m_cRadioStation.SetCurSel(0);
		m_cRadioStation.EnableWindow(FALSE);
		m_lStationID=m_cRadioStation.GetItemData(0);
	}
	else
	{
		lPos=m_cRadioStation.FindStringExact(-1,m_strStation);
		m_cRadioStation.SetCurSel(lPos);
	}

	rsStation.Close();

	if( !m_bIsNew )
	{
		m_cCustomer.EnableWindow(FALSE);
		m_cRadioStation.EnableWindow(FALSE);
		m_cEndingDate.EnableWindow(!m_bByNumber);
		m_cFinalHour.EnableWindow(!m_bByNumber);
		m_cNumber.EnableWindow(m_bByNumber);

		SendDlgItemMessage(IDC_BYDATE,BM_SETCHECK,!m_bByNumber);
		SendDlgItemMessage(IDC_BYNUMBER,BM_SETCHECK,m_bByNumber);

		SendDlgItemMessage(IDC_BYINSERT,BM_SETCHECK,!m_bTotalValue);
		SendDlgItemMessage(IDC_BYCONTRACT,BM_SETCHECK,m_bTotalValue);
	}
	else
	{
		m_lCustomerID=0;
		m_bByNumber=FALSE;
		m_cNumber.EnableWindow(FALSE);

		SendDlgItemMessage(IDC_BYDATE,BM_SETCHECK,BST_CHECKED);
		SendDlgItemMessage(IDC_BYINSERT,BM_SETCHECK,BST_CHECKED);
	}
	
	CheckData();

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CScheduleMain::CheckData()
{
	BOOL bOK=TRUE;

	UpdateData();

	if( m_lStationID==0 )
		bOK=FALSE;

	if( m_lCustomerID==0 )
		bOK=FALSE;

	if( m_bByNumber )
	{
		if( m_iNumber<1 )
			bOK=FALSE;
	}
	else
	{
		if( m_dEndingDate<m_dStartingDate)
			bOK=FALSE;
	}

	CPropertySheet *Parent=(CPropertySheet *)GetParent();
	if( bOK )
		Parent->SetWizardButtons(PSWIZB_NEXT);
	else
		Parent->SetWizardButtons(0);
}

void CScheduleMain::OnKillfocusCustomer() 
{
	long lPos=m_cCustomer.GetCurSel();

	if( lPos==CB_ERR )
		m_lCustomerID=0;
	else
	{
		m_lCustomerID=m_cCustomer.GetItemData(lPos);
		m_cCustomer.GetLBText(lPos,m_strCustomer);
	}

	CheckData();
}

void CScheduleMain::OnKillfocusRadiostation() 
{
	long lPos=m_cRadioStation.GetCurSel();

	if( lPos==CB_ERR )
		m_lStationID=0;
	else
		m_lStationID=m_cRadioStation.GetItemData(lPos);

	CheckData();
}

void CScheduleMain::OnKillfocusNotify(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CheckData();

	*pResult = 0;
}

void CScheduleMain::OnSetfocusNotify(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void CScheduleMain::OnBynumber() 
{
	m_cEndingDate.EnableWindow(FALSE);
	m_cFinalHour.EnableWindow(FALSE);
	m_cNumber.EnableWindow(TRUE);
	m_bByNumber=TRUE;

	CheckData();
}

void CScheduleMain::OnBydate() 
{
	m_cEndingDate.EnableWindow(TRUE);
	m_cFinalHour.EnableWindow(TRUE);
	m_cNumber.EnableWindow(FALSE);
	m_bByNumber=FALSE;

	CheckData();
}

BOOL CScheduleMain::OnSetActive() 
{
	CPropertySheet *pParent=(CPropertySheet *)GetParent();
	
	pParent->SetWizardButtons(PSWIZB_NEXT);

	return CPropertyPage::OnSetActive();
}

void CScheduleMain::OnByinsert() 
{
	m_bTotalValue = FALSE;	
}

void CScheduleMain::OnBycontract() 
{
	m_bTotalValue = TRUE;	
}
