// RSViewJingleFiles.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSViewJingleFiles.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSViewJingleFiles

IMPLEMENT_DYNAMIC(CRSViewJingleFiles, CRecordset)

CRSViewJingleFiles::CRSViewJingleFiles(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSViewJingleFiles)
	m_ID = 0;
	m_FileName = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSViewJingleFiles::GetDefaultConnect()
{
	return strConnect;
}

CString CRSViewJingleFiles::GetDefaultSQL()
{
	return _T("[dbo].[ViewJingleFiles]");
}

void CRSViewJingleFiles::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSViewJingleFiles)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[FileName]"), m_FileName);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSViewJingleFiles diagnostics

#ifdef _DEBUG
void CRSViewJingleFiles::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSViewJingleFiles::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
