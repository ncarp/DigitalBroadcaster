// RSViewNewsOnAir.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSViewNewsOnAir.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSViewNewsOnAir

IMPLEMENT_DYNAMIC(CRSViewNewsOnAir, CRecordset)

CRSViewNewsOnAir::CRSViewNewsOnAir(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSViewNewsOnAir)
	m_ID = 0;
	m_NewsID = 0;
	m_Name = _T("");
	m_TypeID = 0;
	m_Type = _T("");
	m_nFields = 7;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSViewNewsOnAir::GetDefaultConnect()
{
	return strConnect;
}

CString CRSViewNewsOnAir::GetDefaultSQL()
{
	return _T("[dbo].[ViewNews_OnAir]");
}

void CRSViewNewsOnAir::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSViewNewsOnAir)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Long(pFX, _T("[NewsID]"), m_NewsID);
	RFX_Date(pFX, _T("[StartingDate]"), m_StartingDate);
	RFX_Date(pFX, _T("[EndingDate]"), m_EndingDate);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Long(pFX, _T("[TypeID]"), m_TypeID);
	RFX_Text(pFX, _T("[Type]"), m_Type);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSViewNewsOnAir diagnostics

#ifdef _DEBUG
void CRSViewNewsOnAir::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSViewNewsOnAir::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
