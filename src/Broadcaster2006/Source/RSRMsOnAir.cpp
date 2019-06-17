// RSRMsOnAir.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSRMsOnAir.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSRMsOnAir

IMPLEMENT_DYNAMIC(CRSRMsOnAir, CRecordset)

CRSRMsOnAir::CRSRMsOnAir(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSRMsOnAir)
	m_RMID = 0;
	m_ID = 0;
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSRMsOnAir::GetDefaultConnect()
{
	return strConnect;
}

CString CRSRMsOnAir::GetDefaultSQL()
{
	return _T("[dbo].[RmsOnAir]");
}

void CRSRMsOnAir::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSRMsOnAir)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[RMID]"), m_RMID);
	RFX_Date(pFX, _T("[StartingDate]"), m_StartingDate);
	RFX_Date(pFX, _T("[EndingDate]"), m_EndingDate);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSRMsOnAir diagnostics

#ifdef _DEBUG
void CRSRMsOnAir::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSRMsOnAir::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
