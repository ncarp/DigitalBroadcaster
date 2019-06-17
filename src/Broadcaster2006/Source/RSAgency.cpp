// RSAgency.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSAgency.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSAgency

IMPLEMENT_DYNAMIC(CRSAgency, CRecordset)

CRSAgency::CRSAgency(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSAgency)
	m_ID = 0;
	m_Name = _T("");
	m_Adress = _T("");
	m_ZIP = _T("");
	m_Telephone = _T("");
	m_Fax = _T("");
	m_eMail = _T("");
	m_WWW = _T("");
	m_Contact = _T("");
	m_FID = _T("");
	m_Salesperson = 0;
	m_OBS = _T("");
	m_Activ = 0;
	m_nFields = 13;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSAgency::GetDefaultConnect()
{
	return strConnect;
}

CString CRSAgency::GetDefaultSQL()
{
	return _T("[dbo].[Agency]");
}

void CRSAgency::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSAgency)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Text(pFX, _T("[Adress]"), m_Adress);
	RFX_Text(pFX, _T("[ZIP]"), m_ZIP);
	RFX_Text(pFX, _T("[Telephone]"), m_Telephone);
	RFX_Text(pFX, _T("[Fax]"), m_Fax);
	RFX_Text(pFX, _T("[eMail]"), m_eMail);
	RFX_Text(pFX, _T("[WWW]"), m_WWW);
	RFX_Text(pFX, _T("[Contact]"), m_Contact);
	RFX_Text(pFX, _T("[FID]"), m_FID);
	RFX_Long(pFX, _T("[Salesperson]"), m_Salesperson);
	RFX_Text(pFX, _T("[OBS]"), m_OBS);
	RFX_Long(pFX, _T("[Activ]"), m_Activ);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSAgency diagnostics

#ifdef _DEBUG
void CRSAgency::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSAgency::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
