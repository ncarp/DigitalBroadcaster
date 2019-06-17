// RSJinglesOnAir.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSJinglesOnAir.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSJinglesOnAir

IMPLEMENT_DYNAMIC(CRSJinglesOnAir, CRecordset)

CRSJinglesOnAir::CRSJinglesOnAir(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSJinglesOnAir)
	m_JingleID = 0;
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSJinglesOnAir::GetDefaultConnect()
{
	return strConnect;
}

CString CRSJinglesOnAir::GetDefaultSQL()
{
	return _T("[dbo].[JinglesOnAir]");
}

void CRSJinglesOnAir::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSJinglesOnAir)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[JingleID]"), m_JingleID);
	RFX_Date(pFX, _T("[StartingDate]"), m_StartingDate);
	RFX_Date(pFX, _T("[EndingDate]"), m_EndingDate);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSJinglesOnAir diagnostics

#ifdef _DEBUG
void CRSJinglesOnAir::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSJinglesOnAir::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
