// RSViewInstrumentals.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\rsviewinstrumentals.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSViewInstrumentals

IMPLEMENT_DYNAMIC(CRSViewInstrumentals, CRecordset)

CRSViewInstrumentals::CRSViewInstrumentals(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSViewInstrumentals)
	m_ID = 0;
	m_TypeID = 0;
	m_ElementID = 0;
	m_Title = _T("");
	m_Artist = _T("");
	m_Length = 0;
	m_nFields = 7;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	m_strConnect = str;
}


CString CRSViewInstrumentals::GetDefaultConnect()
{
	return _T("ODBC;DSN=")+m_strConnect;
}

CString CRSViewInstrumentals::GetDefaultSQL()
{
	return _T("[dbo].[ViewInstrumentals]");
}

void CRSViewInstrumentals::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSViewInstrumentals)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Long(pFX, _T("[TypeID]"), m_TypeID);
	RFX_Long(pFX, _T("[ElementID]"), m_ElementID);
	RFX_Date(pFX, _T("[LastDate]"), m_LastDate);
	RFX_Text(pFX, _T("[Title]"), m_Title);
	RFX_Text(pFX, _T("[Artist]"), m_Artist);
	RFX_Long(pFX, _T("[Length]"), m_Length);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSViewInstrumentals diagnostics

#ifdef _DEBUG
void CRSViewInstrumentals::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSViewInstrumentals::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
