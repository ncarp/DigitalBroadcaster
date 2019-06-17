// RSBusiness.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSBusiness.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSBusiness

IMPLEMENT_DYNAMIC(CRSBusiness, CRecordset)

CRSBusiness::CRSBusiness(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSBusiness)
	m_ID = 0;
	m_Name = _T("");
	m_Activ = 0;
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSBusiness::GetDefaultConnect()
{
	return strConnect;
}

CString CRSBusiness::GetDefaultSQL()
{
	return _T("[dbo].[TypeOfBusiness]");
}

void CRSBusiness::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSBusiness)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Long(pFX, _T("[Activ]"), m_Activ);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSBusiness diagnostics

#ifdef _DEBUG
void CRSBusiness::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSBusiness::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
