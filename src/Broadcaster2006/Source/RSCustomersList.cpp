// RSCustomersList.cpp : implementation file
//

#include "stdafx.h"
#include "..\Traffic\Traffic.h"
#include "..\include\RSCustomersList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSCustomersList

IMPLEMENT_DYNAMIC(CRSCustomersList, CRecordset)

CRSCustomersList::CRSCustomersList(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSCustomersList)
	m_ID = 0;
	m_Name = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	m_strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSCustomersList::GetDefaultConnect()
{
	return m_strConnect;
}

CString CRSCustomersList::GetDefaultSQL()
{
	return _T("[dbo].[ViewCustomersNameAndID]");
}

void CRSCustomersList::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSCustomersList)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSCustomersList diagnostics

#ifdef _DEBUG
void CRSCustomersList::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSCustomersList::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
