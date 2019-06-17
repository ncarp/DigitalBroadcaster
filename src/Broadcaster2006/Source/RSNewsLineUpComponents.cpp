// RSNewsLineUpComponents.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSNewsLineUpComponents.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSNewsLineUpComponents

IMPLEMENT_DYNAMIC(CRSNewsLineUpComponents, CRecordset)

CRSNewsLineUpComponents::CRSNewsLineUpComponents(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSNewsLineUpComponents)
	m_LineUpID = 0;
	m_Position = 0;
	m_NewsID = 0;
	m_Prev = 0;
	m_Next = 0;
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSNewsLineUpComponents::GetDefaultConnect()
{
	return strConnect;
}

CString CRSNewsLineUpComponents::GetDefaultSQL()
{
	return _T("[dbo].[NewsLineUpComponents]");
}

void CRSNewsLineUpComponents::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSNewsLineUpComponents)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[LineUpID]"), m_LineUpID);
	RFX_Long(pFX, _T("[Position]"), m_Position);
	RFX_Long(pFX, _T("[NewsID]"), m_NewsID);
	RFX_Long(pFX, _T("[Prev]"), m_Prev);
	RFX_Long(pFX, _T("[Next]"), m_Next);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSNewsLineUpComponents diagnostics

#ifdef _DEBUG
void CRSNewsLineUpComponents::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSNewsLineUpComponents::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
