// RSBlocksDefinition.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSBlocksDefinition.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSBlocksDefinition

IMPLEMENT_DYNAMIC(CRSBlocksDefinition, CRecordset)

CRSBlocksDefinition::CRSBlocksDefinition(CString str,CDatabase *pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRSBlocksDefinition)
	m_ID = 0;
	m_Name = _T("");
	m_Sun = 0;
	m_Mon = 0;
	m_Tue = 0;
	m_Wed = 0;
	m_Thu = 0;
	m_Fry = 0;
	m_Sat = 0;
	m_Time = 0;
	m_InsertionType = 0;
	m_Sponsor = 0;
	m_Activ = 0;
	m_DRM = _T("");
	m_nFields = 14;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSBlocksDefinition::GetDefaultConnect()
{
	return strConnect;
}

CString CRSBlocksDefinition::GetDefaultSQL()
{
	return _T("[dbo].[BlocksDefinition]");
}

void CRSBlocksDefinition::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSBlocksDefinition)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Long(pFX, _T("[Sun]"), m_Sun);
	RFX_Long(pFX, _T("[Mon]"), m_Mon);
	RFX_Long(pFX, _T("[Tue]"), m_Tue);
	RFX_Long(pFX, _T("[Wed]"), m_Wed);
	RFX_Long(pFX, _T("[Thu]"), m_Thu);
	RFX_Long(pFX, _T("[Fri]"), m_Fry);
	RFX_Long(pFX, _T("[Sat]"), m_Sat);
	RFX_Long(pFX, _T("[Time]"), m_Time);
	RFX_Long(pFX, _T("[InsertionType]"), m_InsertionType);
	RFX_Long(pFX, _T("[Sponsor]"), m_Sponsor);
	RFX_Long(pFX, _T("[Activ]"), m_Activ);
	RFX_Text(pFX, _T("[DRM]"), m_DRM);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSBlocksDefinition diagnostics

#ifdef _DEBUG
void CRSBlocksDefinition::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSBlocksDefinition::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
