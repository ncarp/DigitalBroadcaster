// RSTypeOfRM.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSTypeOfRM.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSTypeOfRM

IMPLEMENT_DYNAMIC(CRSTypeOfRM, CRecordset)

CRSTypeOfRM::CRSTypeOfRM(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSTypeOfRM)
	m_ID = 0;
	m_Name = _T("");
	m_Activ = 0;
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSTypeOfRM::GetDefaultConnect()
{
	return strConnect;
}

CString CRSTypeOfRM::GetDefaultSQL()
{
	return _T("[dbo].[TypeOfRM]");
}

void CRSTypeOfRM::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSTypeOfRM)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Long(pFX, _T("[Activ]"), m_Activ);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSTypeOfRM diagnostics

#ifdef _DEBUG
void CRSTypeOfRM::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSTypeOfRM::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
