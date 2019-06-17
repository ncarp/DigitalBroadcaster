// RSCartwallDefinition.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSCartwallDefinition.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSCartwallDefinition

IMPLEMENT_DYNAMIC(CRSCartwallDefinition, CRecordset)

CRSCartwallDefinition::CRSCartwallDefinition(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSCartwallDefinition)
	m_ID = 0;
	m_Name = _T("");
	m_UserID = 0;
	m_Info = 0;
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSCartwallDefinition::GetDefaultConnect()
{
	return strConnect;
}

CString CRSCartwallDefinition::GetDefaultSQL()
{
	return _T("[dbo].[CartwallDefinition]");
}

void CRSCartwallDefinition::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSCartwallDefinition)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Long(pFX, _T("[UserID]"), m_UserID);
	RFX_Long(pFX, _T("[Info]"), m_Info);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSCartwallDefinition diagnostics

#ifdef _DEBUG
void CRSCartwallDefinition::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSCartwallDefinition::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
