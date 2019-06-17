// RSPlayListsDefinition.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSPlayListsDefinition.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSPlayListsDefinition

IMPLEMENT_DYNAMIC(CRSPlayListsDefinition, CRecordset)

CRSPlayListsDefinition::CRSPlayListsDefinition(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSPlayListsDefinition)
	m_ID = 0;
	m_Name = _T("");
	m_Activ = 0;
	m_DRM35 = _T("");
	m_OnAir = 0;
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	m_strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSPlayListsDefinition::GetDefaultConnect()
{
	return m_strConnect;
}

CString CRSPlayListsDefinition::GetDefaultSQL()
{
	return _T("[dbo].[PlayLists-Def]");
}

void CRSPlayListsDefinition::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSPlayListsDefinition)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Long(pFX, _T("[Activ]"), m_Activ);
	RFX_Text(pFX, _T("[DRM35]"), m_DRM35);
	RFX_Long(pFX, _T("[OnAir]"), m_OnAir);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSPlayListsDefinition diagnostics

#ifdef _DEBUG
void CRSPlayListsDefinition::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSPlayListsDefinition::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
