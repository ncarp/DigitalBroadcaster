// RSViewMusicFiles.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSViewMusicFiles.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSViewMusicFiles

IMPLEMENT_DYNAMIC(CRSViewMusicFiles, CRecordset)

CRSViewMusicFiles::CRSViewMusicFiles(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSViewMusicFiles)
	m_FileName = _T("");
	m_Activ = 0;
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	m_strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSViewMusicFiles::GetDefaultConnect()
{
	return m_strConnect;
}

CString CRSViewMusicFiles::GetDefaultSQL()
{
	return _T("[dbo].[ViewEditedMusicFiles]");
}

void CRSViewMusicFiles::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSViewMusicFiles)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[FileName]"), m_FileName);
	RFX_Long(pFX, _T("[Activ]"), m_Activ);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSViewMusicFiles diagnostics

#ifdef _DEBUG
void CRSViewMusicFiles::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSViewMusicFiles::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
