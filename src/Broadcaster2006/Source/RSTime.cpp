// RSTime.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSTime.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSTime

IMPLEMENT_DYNAMIC(CRSTime, CRecordset)

CRSTime::CRSTime(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSTime)
	m_ID = 0;
	m_Name = _T("");
	m_PathID = 0;
	m_FolderName = _T("");
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSTime::GetDefaultConnect()
{
	return strConnect;
}

CString CRSTime::GetDefaultSQL()
{
	return _T("[dbo].[Time]");
}

void CRSTime::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSTime)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Long(pFX, _T("[PathID]"), m_PathID);
	RFX_Text(pFX, _T("[FolderName]"), m_FolderName);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSTime diagnostics

#ifdef _DEBUG
void CRSTime::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSTime::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
