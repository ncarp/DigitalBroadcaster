// RSCategories.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSCategories.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSCategories

IMPLEMENT_DYNAMIC(CRSCategories, CRecordset)

CRSCategories::CRSCategories(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSCategories)
	m_ID = 0;
	m_Name = _T("");
	m_Activ = 0;
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	m_strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSCategories::GetDefaultConnect()
{
	return m_strConnect;
}

CString CRSCategories::GetDefaultSQL()
{
	return _T("[dbo].[Categories]");
}

void CRSCategories::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSCategories)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Long(pFX, _T("[Activ]"), m_Activ);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSCategories diagnostics

#ifdef _DEBUG
void CRSCategories::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSCategories::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
