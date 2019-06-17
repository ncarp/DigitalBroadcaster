// RSRadioStations.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSRadioStations.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSRadioStations

IMPLEMENT_DYNAMIC(CRSRadioStations, CRecordset)

CRSRadioStations::CRSRadioStations(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSRadioStations)
	m_ID = 0;
	m_Name = _T("");
	m_Adress = _T("");
	m_LogoURL = _T("");
	m_DSN = _T("");
	m_DB = _T("");
	m_nFields = 6;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	m_strConnect.Format("ODBC;DSN=%s",str);
}

CString CRSRadioStations::GetDefaultConnect()
{
	return m_strConnect;
}

CString CRSRadioStations::GetDefaultSQL()
{
	return _T("[dbo].[RadioStations]");
}

void CRSRadioStations::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSRadioStations)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Text(pFX, _T("[Adress]"), m_Adress);
	RFX_Text(pFX, _T("[LogoURL]"), m_LogoURL);
	RFX_Text(pFX, _T("[DSN]"), m_DSN);
	RFX_Text(pFX, _T("[DB]"), m_DB);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSRadioStations diagnostics

#ifdef _DEBUG
void CRSRadioStations::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSRadioStations::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
