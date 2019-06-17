// RSViewOnAirSponsors.cpp : implementation file
//

#include "stdafx.h"
#include "RSViewOnAirSponsors.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSViewOnAirSponsors

IMPLEMENT_DYNAMIC(CRSViewOnAirSponsors, CRecordset)

CRSViewOnAirSponsors::CRSViewOnAirSponsors(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSViewOnAirSponsors)
	m_SpotID = 0;
	m_SpotName = _T("");
	m_CustomerName = _T("");
	m_Length = 0;
	m_nFields = 6;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	m_strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSViewOnAirSponsors::GetDefaultConnect()
{
	return m_strConnect;
}

CString CRSViewOnAirSponsors::GetDefaultSQL()
{
	return _T("[dbo].[ViewOnAirSponsors]");
}

void CRSViewOnAirSponsors::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSViewOnAirSponsors)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[SpotID]"), m_SpotID);
	RFX_Date(pFX, _T("[StartingDate]"), m_StartingDate);
	RFX_Date(pFX, _T("[EndingDate]"), m_EndingDate);
	RFX_Text(pFX, _T("[SpotName]"), m_SpotName);
	RFX_Text(pFX, _T("[CustomerName]"), m_CustomerName);
	RFX_Long(pFX, _T("[Length]"), m_Length);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSViewOnAirSponsors diagnostics

#ifdef _DEBUG
void CRSViewOnAirSponsors::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSViewOnAirSponsors::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
