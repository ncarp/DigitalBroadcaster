// RSTypeOfJingle.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSTypeOfJingle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSTypeOfJingle

IMPLEMENT_DYNAMIC(CRSTypeOfJingle, CRecordset)

CRSTypeOfJingle::CRSTypeOfJingle(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSTypeOfJingle)
	m_ID = 0;
	m_Name = _T("");
	m_Activ = 0;
	m_DRM35 = _T("");
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSTypeOfJingle::GetDefaultConnect()
{
	return strConnect;
}

CString CRSTypeOfJingle::GetDefaultSQL()
{
	return _T("[dbo].[TypeOfJingle]");
}

void CRSTypeOfJingle::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSTypeOfJingle)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Long(pFX, _T("[Activ]"), m_Activ);
	RFX_Text(pFX, _T("[DRM35]"), m_DRM35);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSTypeOfJingle diagnostics

#ifdef _DEBUG
void CRSTypeOfJingle::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSTypeOfJingle::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
