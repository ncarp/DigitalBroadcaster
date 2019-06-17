// RSViewSponsors.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSViewSponsors.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSViewSponsors

IMPLEMENT_DYNAMIC(CRSViewSponsors, CRecordset)

CRSViewSponsors::CRSViewSponsors(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSViewSponsors)
	m_SpotID = 0;
	m_SpotName = _T("");
	m_CustomerName = _T("");
	m_ID = 0;
	m_CustomerID = 0;
	m_nFields = 7;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSViewSponsors::GetDefaultConnect()
{
	return strConnect;
}

CString CRSViewSponsors::GetDefaultSQL()
{
	return _T("[dbo].[ViewSponsors]");
}

void CRSViewSponsors::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSViewSponsors)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[SpotID]"), m_SpotID);
	RFX_Date(pFX, _T("[StartingDate]"), m_StartingDate);
	RFX_Date(pFX, _T("[EndingDate]"), m_EndingDate);
	RFX_Text(pFX, _T("[SpotName]"), m_SpotName);
	RFX_Text(pFX, _T("[CustomerName]"), m_CustomerName);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Long(pFX, _T("[CustomerID]"), m_CustomerID);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSViewSponsors diagnostics

#ifdef _DEBUG
void CRSViewSponsors::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSViewSponsors::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
