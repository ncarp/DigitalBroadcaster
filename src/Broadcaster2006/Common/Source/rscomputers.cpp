// rscomputers.cpp : implementation file
//

#include "stdafx.h"
#include "..\..\common\include\rscomputers.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSComputers

IMPLEMENT_DYNAMIC(CRSComputers, CRecordset)

CRSComputers::CRSComputers(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSComputers)
	m_ID = 0;
	m_Name = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	m_strConnect = str;
}


CString CRSComputers::GetDefaultConnect()
{
	return _T("ODBC;DSN=")+m_strConnect;
}

CString CRSComputers::GetDefaultSQL()
{
	return _T("[dbo].[Computers]");
}

void CRSComputers::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSComputers)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSComputers diagnostics

#ifdef _DEBUG
void CRSComputers::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSComputers::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
