// RSSalesman.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSSalesman.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSSalesman

IMPLEMENT_DYNAMIC(CRSSalesman, CRecordset)

CRSSalesman::CRSSalesman(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSSalesman)
	m_ID = 0;
	m_Name = _T("");
	m_Adress = _T("");
	m_ZIP = _T("");
	m_NC = _T("");
	m_Phone = _T("");
	m_Fax = _T("");
	m_eMail = _T("");
	m_Comission = 0.0;
	m_Remarks = _T("");
	m_Activ = 0;
	m_DRM35 = _T("");
	m_nFields = 12;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSSalesman::GetDefaultConnect()
{
	return strConnect;
}

CString CRSSalesman::GetDefaultSQL()
{
	return _T("[dbo].[Salesperson]");
}

void CRSSalesman::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSSalesman)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Text(pFX, _T("[Adress]"), m_Adress);
	RFX_Text(pFX, _T("[ZIP]"), m_ZIP);
	RFX_Text(pFX, _T("[NC]"), m_NC);
	RFX_Text(pFX, _T("[Phone]"), m_Phone);
	RFX_Text(pFX, _T("[Fax]"), m_Fax);
	RFX_Text(pFX, _T("[eMail]"), m_eMail);
	RFX_Double(pFX, _T("[Comission]"), m_Comission);
	RFX_Text(pFX, _T("[Remarks]"), m_Remarks);
	RFX_Long(pFX, _T("[Activ]"), m_Activ);
	RFX_Text(pFX, _T("[DRM35]"), m_DRM35);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSSalesman diagnostics

#ifdef _DEBUG
void CRSSalesman::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSSalesman::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
