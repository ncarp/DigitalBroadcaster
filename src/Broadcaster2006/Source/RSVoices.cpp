// RSVoices.cpp : implementation file
//

#include "stdafx.h"
#include "..\Traffic\Traffic.h"
#include "..\include\RSVoices.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSVoices

IMPLEMENT_DYNAMIC(CRSVoices, CRecordset)

CRSVoices::CRSVoices(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSVoices)
	m_ID = 0;
	m_Name = _T("");
	m_Activ = 0;
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSVoices::GetDefaultConnect()
{
	return strConnect;
}

CString CRSVoices::GetDefaultSQL()
{
	return _T("[dbo].[Voices]");
}

void CRSVoices::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSVoices)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Long(pFX, _T("[Activ]"), m_Activ);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSVoices diagnostics

#ifdef _DEBUG
void CRSVoices::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSVoices::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
