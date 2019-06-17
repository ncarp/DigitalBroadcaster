// rssystemusers.cpp : implementation file
//

#include "stdafx.h"
#include "..\..\common\include\rssystemusers.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSSystemUsers

IMPLEMENT_DYNAMIC(CRSSystemUsers, CRecordset)

CRSSystemUsers::CRSSystemUsers(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSSystemUsers)
	m_Id = 0;
	m_Name = _T("");
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	m_strConnect = str;
}


CString CRSSystemUsers::GetDefaultConnect()
{
	return _T("ODBC;DSN=")+m_strConnect;
}

CString CRSSystemUsers::GetDefaultSQL()
{
	return _T("[dbo].[SystemUsers]");
}

void CRSSystemUsers::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSSystemUsers)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[Id]"), m_Id);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Binary(pFX, _T("[Permission]"), m_Permission);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSSystemUsers diagnostics

#ifdef _DEBUG
void CRSSystemUsers::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSSystemUsers::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
