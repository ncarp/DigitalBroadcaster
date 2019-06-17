// RSViewBumpedTraffic.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSViewBumpedTraffic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSViewBumpedTraffic

IMPLEMENT_DYNAMIC(CRSViewBumpedTraffic, CRecordset)

CRSViewBumpedTraffic::CRSViewBumpedTraffic(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSViewBumpedTraffic)
	m_SpotID = 0;
	m_CustomerName = _T("");
	m_Name = _T("");
	m_Length = 0;
	m_ID = 0;
	m_Time = 0;
	m_nFields = 7;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSViewBumpedTraffic::GetDefaultConnect()
{
	return strConnect;
}

CString CRSViewBumpedTraffic::GetDefaultSQL()
{
	return _T("[dbo].[ViewBumpedTraffic]");
}

void CRSViewBumpedTraffic::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSViewBumpedTraffic)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[SpotID]"), m_SpotID);
	RFX_Text(pFX, _T("[CustomerName]"), m_CustomerName);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Long(pFX, _T("[Length]"), m_Length);
	RFX_Date(pFX, _T("[BlockDate]"), m_BlockDate);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Long(pFX, _T("[Time]"), m_Time);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSViewBumpedTraffic diagnostics

#ifdef _DEBUG
void CRSViewBumpedTraffic::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSViewBumpedTraffic::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
