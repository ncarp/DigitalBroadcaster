// RSRecordLabel.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSRecordLabel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSRecordLabel

IMPLEMENT_DYNAMIC(CRSRecordLabel, CRecordset)

CRSRecordLabel::CRSRecordLabel(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSRecordLabel)
	m_ID = 0;
	m_Name = _T("");
	m_Adress = _T("");
	m_Activ = 0;
	m_ParentCompany = 0;
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSRecordLabel::GetDefaultConnect()
{
	return strConnect;
}

CString CRSRecordLabel::GetDefaultSQL()
{
	return _T("[dbo].[RecordLabel]");
}

void CRSRecordLabel::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSRecordLabel)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Text(pFX, _T("[Adress]"), m_Adress);
	RFX_Long(pFX, _T("[Activ]"), m_Activ);
	RFX_Long(pFX, _T("[ParentCompany]"), m_ParentCompany);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSRecordLabel diagnostics

#ifdef _DEBUG
void CRSRecordLabel::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSRecordLabel::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
