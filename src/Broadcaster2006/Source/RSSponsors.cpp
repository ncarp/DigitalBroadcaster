// RSSponsors.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSSponsors.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSSponsors

IMPLEMENT_DYNAMIC(CRSSponsors, CRecordset)

CRSSponsors::CRSSponsors(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSSponsors)
	m_SpotID = 0;
	m_ID = 0;
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSSponsors::GetDefaultConnect()
{
	return strConnect;
}

CString CRSSponsors::GetDefaultSQL()
{
	return _T("[dbo].[Sponsors]");
}

void CRSSponsors::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSSponsors)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[SpotID]"), m_SpotID);
	RFX_Date(pFX, _T("[StartingDate]"), m_StartingDate);
	RFX_Date(pFX, _T("[EndingDate]"), m_EndingDate);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSSponsors diagnostics

#ifdef _DEBUG
void CRSSponsors::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSSponsors::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
