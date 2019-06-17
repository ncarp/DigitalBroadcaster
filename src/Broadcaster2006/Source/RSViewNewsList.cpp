// RSViewNewsList.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSViewNewsList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSViewNewsList

IMPLEMENT_DYNAMIC(CRSViewNewsList, CRecordset)

CRSViewNewsList::CRSViewNewsList(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSViewNewsList)
	m_ID = 0;
	m_Name = _T("");
	m_TypeID = _T("");
	m_Type = _T("");
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSViewNewsList::GetDefaultConnect()
{
	return strConnect;
}

CString CRSViewNewsList::GetDefaultSQL()
{
	return _T("[dbo].[ViewNewsList]");
}

void CRSViewNewsList::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSViewNewsList)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Text(pFX, _T("[TypeID]"), m_TypeID);
	RFX_Text(pFX, _T("[Type]"), m_Type);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSViewNewsList diagnostics

#ifdef _DEBUG
void CRSViewNewsList::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSViewNewsList::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
