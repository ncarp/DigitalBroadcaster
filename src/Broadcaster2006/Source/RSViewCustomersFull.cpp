// RSViewCustomersFull.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSViewCustomersFull.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSViewCustomersFull

IMPLEMENT_DYNAMIC(CRSViewCustomersFull, CRecordset)

CRSViewCustomersFull::CRSViewCustomersFull(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSViewCustomersFull)
	m_ID = 0;
	m_Name = _T("");
	m_Adress = _T("");
	m_ZIP = _T("");
	m_Phone = _T("");
	m_Fax = _T("");
	m_eMail = _T("");
	m_www = _T("");
	m_Contact = _T("");
	m_nc = _T("");
	m_AgencyID = 0;
	m_BusinessTypeID = 0;
	m_SalespersonID = 0;
	m_Obs = _T("");
	m_Activ = 0;
	m_Cli35 = _T("");
	m_Agency = _T("");
	m_Business = _T("");
	m_Salesperson = _T("");
	m_NC2 = _T("");
	m_Name2 = _T("");
	m_Number = _T("");
	m_CelPhone = _T("");
	m_nFields = 23;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	m_strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSViewCustomersFull::GetDefaultConnect()
{
	return m_strConnect;
}

CString CRSViewCustomersFull::GetDefaultSQL()
{
	return _T("[dbo].[ViewCustomersFull]");
}

void CRSViewCustomersFull::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSViewCustomersFull)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Text(pFX, _T("[Adress]"), m_Adress);
	RFX_Text(pFX, _T("[ZIP]"), m_ZIP);
	RFX_Text(pFX, _T("[Phone]"), m_Phone);
	RFX_Text(pFX, _T("[Fax]"), m_Fax);
	RFX_Text(pFX, _T("[eMail]"), m_eMail);
	RFX_Text(pFX, _T("[www]"), m_www);
	RFX_Text(pFX, _T("[Contact]"), m_Contact);
	RFX_Text(pFX, _T("[nc]"), m_nc);
	RFX_Long(pFX, _T("[AgencyID]"), m_AgencyID);
	RFX_Long(pFX, _T("[BusinessTypeID]"), m_BusinessTypeID);
	RFX_Long(pFX, _T("[SalespersonID]"), m_SalespersonID);
	RFX_Text(pFX, _T("[Obs]"), m_Obs);
	RFX_Long(pFX, _T("[Activ]"), m_Activ);
	RFX_Text(pFX, _T("[Cli35]"), m_Cli35);
	RFX_Text(pFX, _T("[Agency]"), m_Agency);
	RFX_Text(pFX, _T("[Business]"), m_Business);
	RFX_Text(pFX, _T("[Salesperson]"), m_Salesperson);
	RFX_Text(pFX, _T("[NC2]"), m_NC2);
	RFX_Text(pFX, _T("[Name2]"), m_Name2);
	RFX_Text(pFX, _T("[Number]"), m_Number );
	RFX_Text(pFX, _T("[CelPhone]"),m_CelPhone );
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSViewCustomersFull diagnostics

#ifdef _DEBUG
void CRSViewCustomersFull::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSViewCustomersFull::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
