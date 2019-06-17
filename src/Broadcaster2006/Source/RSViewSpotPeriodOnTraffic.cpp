// RSViewSpotPeriodOnTraffic.cpp : implementation file
//

#include "stdafx.h"
#include "..\Traffic\Traffic.h"
#include "..\include\RSViewSpotPeriodOnTraffic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSViewSpotPeriodOnTraffic

IMPLEMENT_DYNAMIC(CRSViewSpotPeriodOnTraffic, CRecordset)

CRSViewSpotPeriodOnTraffic::CRSViewSpotPeriodOnTraffic(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSViewSpotPeriodOnTraffic)
	m_SpotID = 0;
	m_SpotName = "";
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	m_strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSViewSpotPeriodOnTraffic::GetDefaultConnect()
{
	return m_strConnect;
}

CString CRSViewSpotPeriodOnTraffic::GetDefaultSQL()
{
	return _T("[dbo].[ViewSpotPeriodOnTraffic]");
}

void CRSViewSpotPeriodOnTraffic::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSViewSpotPeriodOnTraffic)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[SpotID]"), m_SpotID);
	RFX_Date(pFX, _T("[MaxDate]"), m_MaxDate);
	RFX_Date(pFX, _T("[MinDate]"), m_MinDate);
	RFX_Text(pFX, _T("[SpotName]"),m_SpotName);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSViewSpotPeriodOnTraffic diagnostics

#ifdef _DEBUG
void CRSViewSpotPeriodOnTraffic::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSViewSpotPeriodOnTraffic::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
