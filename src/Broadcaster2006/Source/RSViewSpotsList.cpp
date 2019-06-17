// RSViewSpotsList.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSViewSpotsList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSViewSpotsList

IMPLEMENT_DYNAMIC(CRSViewSpotsList, CRecordset)

CRSViewSpotsList::CRSViewSpotsList(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSViewSpotsList)
	m_ID = 0;
	m_Name = _T("");
	m_CustomerID = 0;
	m_AgencyID = 0;
	m_CustomerName = _T("");
	m_AgencyName = _T("");
	m_SalespersonID = 0;
	m_SalespersonName = _T("");
	m_nFields = 8;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	m_strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSViewSpotsList::GetDefaultConnect()
{
	return m_strConnect;
}

CString CRSViewSpotsList::GetDefaultSQL()
{
	return _T("[dbo].[ViewSpotsList]");
}

void CRSViewSpotsList::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSViewSpotsList)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Long(pFX, _T("[CustomerID]"), m_CustomerID);
	RFX_Long(pFX, _T("[AgencyID]"), m_AgencyID);
	RFX_Text(pFX, _T("[CustomerName]"), m_CustomerName);
	RFX_Text(pFX, _T("[AgencyName]"), m_AgencyName);
	RFX_Long(pFX, _T("[SalespersonID]"), m_SalespersonID);
	RFX_Text(pFX, _T("[SalespersonName]"), m_SalespersonName);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSViewSpotsList diagnostics

#ifdef _DEBUG
void CRSViewSpotsList::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSViewSpotsList::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
