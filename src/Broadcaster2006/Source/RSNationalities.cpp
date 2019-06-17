// RSNationalities.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSNationalities.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSNationalities

IMPLEMENT_DYNAMIC(CRSNationalities, CRecordset)

CRSNationalities::CRSNationalities(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSNationalities)
	m_ID = 0;
	m_Nationality = _T("");
	m_ZoneID = 0;
	m_Activ = 0;
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSNationalities::GetDefaultConnect()
{
	return strConnect;
}

CString CRSNationalities::GetDefaultSQL()
{
	return _T("[dbo].[Nationalities]");
}

void CRSNationalities::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSNationalities)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Nationality]"), m_Nationality);
	RFX_Long(pFX, _T("[ZoneID]"), m_ZoneID);
	RFX_Long(pFX, _T("[Activ]"), m_Activ);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSNationalities diagnostics

#ifdef _DEBUG
void CRSNationalities::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSNationalities::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
