// RSExpressions.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSExpressions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSExpressions

IMPLEMENT_DYNAMIC(CRSExpressions, CRecordset)

CRSExpressions::CRSExpressions(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSExpressions)
	m_ID = 0;
	m_Name = _T("");
	m_Activ = 0;
	m_DRM35 = _T("");
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	m_strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSExpressions::GetDefaultConnect()
{
	return m_strConnect;
}

CString CRSExpressions::GetDefaultSQL()
{
	return _T("[dbo].[Languages]");
}

void CRSExpressions::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSExpressions)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Long(pFX, _T("[Activ]"), m_Activ);
	RFX_Text(pFX, _T("[DRM35]"), m_DRM35);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSExpressions diagnostics

#ifdef _DEBUG
void CRSExpressions::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSExpressions::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
