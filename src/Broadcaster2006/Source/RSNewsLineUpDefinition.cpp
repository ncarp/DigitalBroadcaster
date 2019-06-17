// RSNewsLineUpDefinition.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSNewsLineUpDefinition.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSNewsLineUpDefinition

IMPLEMENT_DYNAMIC(CRSNewsLineUpDefinition, CRecordset)

CRSNewsLineUpDefinition::CRSNewsLineUpDefinition(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSNewsLineUpDefinition)
	m_ID = 0;
	m_Name = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSNewsLineUpDefinition::GetDefaultConnect()
{
	return strConnect;
}

CString CRSNewsLineUpDefinition::GetDefaultSQL()
{
	return _T("[dbo].[NewsLineUpDefinition]");
}

void CRSNewsLineUpDefinition::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSNewsLineUpDefinition)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSNewsLineUpDefinition diagnostics

#ifdef _DEBUG
void CRSNewsLineUpDefinition::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSNewsLineUpDefinition::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
