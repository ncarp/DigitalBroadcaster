// RSViewRMsOnAir.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSViewRMsOnAir.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSViewRMsOnAir

IMPLEMENT_DYNAMIC(CRSViewRMsOnAir, CRecordset)

CRSViewRMsOnAir::CRSViewRMsOnAir(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSViewRMsOnAir)
	m_ID = 0;
	m_RMID = 0;
	m_Name = _T("");
	m_Type = _T("");
	m_Length = 0;
	m_TypeID = 0;
	m_nFields = 8;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSViewRMsOnAir::GetDefaultConnect()
{
	return strConnect;
}

CString CRSViewRMsOnAir::GetDefaultSQL()
{
	return _T("[dbo].[ViewRMs_OnAir]");
}

void CRSViewRMsOnAir::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSViewRMsOnAir)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Date(pFX, _T("[EndingDate]"), m_EndingDate);
	RFX_Date(pFX, _T("[StartingDate]"), m_StartingDate);
	RFX_Long(pFX, _T("[RMID]"), m_RMID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Text(pFX, _T("[Type]"), m_Type);
	RFX_Long(pFX, _T("[Length]"), m_Length);
	RFX_Long(pFX, _T("[TypeID]"), m_TypeID);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSViewRMsOnAir diagnostics

#ifdef _DEBUG
void CRSViewRMsOnAir::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSViewRMsOnAir::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
