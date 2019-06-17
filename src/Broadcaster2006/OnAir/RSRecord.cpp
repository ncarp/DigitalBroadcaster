// RSRecord.cpp : implementation file
//

#include "stdafx.h"

#include "RSRecord.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSRecord

IMPLEMENT_DYNAMIC(CRSRecord, CRecordset)

CRSRecord::CRSRecord(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSRecord)
	m_ID = 0;
	m_Title = _T("");
	m_ArtistID = 0;
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSRecord::GetDefaultConnect()
{
	return strConnect;
}

CString CRSRecord::GetDefaultSQL()
{
	return _T("[dbo].[Records]");
}

void CRSRecord::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSRecord)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Title]"), m_Title);
	RFX_Long(pFX, _T("[ArtistID]"), m_ArtistID);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSRecord diagnostics

#ifdef _DEBUG
void CRSRecord::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSRecord::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
