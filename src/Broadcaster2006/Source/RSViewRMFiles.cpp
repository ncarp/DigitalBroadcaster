// RSViewRMFiles.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSViewRMFiles.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSViewRMFiles

IMPLEMENT_DYNAMIC(CRSViewRMFiles, CRecordset)

CRSViewRMFiles::CRSViewRMFiles(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSViewRMFiles)
	m_ID = 0;
	m_FileName = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSViewRMFiles::GetDefaultConnect()
{
	return strConnect;
}

CString CRSViewRMFiles::GetDefaultSQL()
{
	return _T("[dbo].[ViewRMFiles]");
}

void CRSViewRMFiles::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSViewRMFiles)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[FileName]"), m_FileName);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSViewRMFiles diagnostics

#ifdef _DEBUG
void CRSViewRMFiles::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSViewRMFiles::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
