// RSViewSpotFiles.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSViewSpotFiles.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSViewSpotFiles

IMPLEMENT_DYNAMIC(CRSViewSpotFiles, CRecordset)

CRSViewSpotFiles::CRSViewSpotFiles(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSViewSpotFiles)
	m_ID = 0;
	m_FileName = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	m_strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSViewSpotFiles::GetDefaultConnect()
{
	return _T("ODBC;DSN=DigitalRM");
}

CString CRSViewSpotFiles::GetDefaultSQL()
{
	return _T("[dbo].[ViewSpotFiles]");
}

void CRSViewSpotFiles::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSViewSpotFiles)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[FileName]"), m_FileName);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSViewSpotFiles diagnostics

#ifdef _DEBUG
void CRSViewSpotFiles::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSViewSpotFiles::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
