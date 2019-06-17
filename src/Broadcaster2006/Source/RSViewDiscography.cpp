// RSViewDiscography.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSViewDiscography.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSViewDiscography

IMPLEMENT_DYNAMIC(CRSViewDiscography, CRecordset)

CRSViewDiscography::CRSViewDiscography(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSViewDiscography)
	m_ID = 0;
	m_ArtistID = 0;
	m_Title = _T("");
	m_Artist = _T("");
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSViewDiscography::GetDefaultConnect()
{
	return strConnect;
}

CString CRSViewDiscography::GetDefaultSQL()
{
	return _T("[dbo].[ViewDiscography]");
}

void CRSViewDiscography::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSViewDiscography)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Long(pFX, _T("[ArtistID]"), m_ArtistID);
	RFX_Text(pFX, _T("[Title]"), m_Title);
	RFX_Text(pFX, _T("[Artist]"), m_Artist);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSViewDiscography diagnostics

#ifdef _DEBUG
void CRSViewDiscography::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSViewDiscography::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
