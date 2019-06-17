// RSInstrumentals.cpp : implementation file
//

#include "stdafx.h"
#include "..\..\common\include\RSInstrumentals.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSInstrumentals

IMPLEMENT_DYNAMIC(CRSInstrumentals, CRecordset)

CRSInstrumentals::CRSInstrumentals(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSInstrumentals)
	m_ID = 0;
	m_TypeID = 0;
	m_ElementID = 0;
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	m_strConnect = str;
}


CString CRSInstrumentals::GetDefaultConnect()
{
	return _T("ODBC;DSN=")+m_strConnect;
}

CString CRSInstrumentals::GetDefaultSQL()
{
	return _T("[dbo].[Instrumentals]");
}

void CRSInstrumentals::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSInstrumentals)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Long(pFX, _T("[TypeID]"), m_TypeID);
	RFX_Long(pFX, _T("[ElementID]"), m_ElementID);
	RFX_Date(pFX, _T("[LastDate]"), m_LastDate);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSInstrumentals diagnostics

#ifdef _DEBUG
void CRSInstrumentals::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSInstrumentals::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
