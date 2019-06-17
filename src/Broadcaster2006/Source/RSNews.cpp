// RSNews.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSNews.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSNews

IMPLEMENT_DYNAMIC(CRSNews, CRecordset)

CRSNews::CRSNews(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSNews)
	m_ID = 0;
	m_Name = _T("");
	m_TypeID = 0;
	m_Activ = 0;
	m_NewsText = _T("");
	m_KeyWords = _T("");
	m_nFields = 7;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSNews::GetDefaultConnect()
{
	return strConnect;
}

CString CRSNews::GetDefaultSQL()
{
	return _T("[dbo].[News]");
}

void CRSNews::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSNews)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Long(pFX, _T("[TypeID]"), m_TypeID);
	RFX_Date(pFX, _T("[Date]"), m_Date);
	RFX_Long(pFX, _T("[Activ]"), m_Activ);
	RFX_Text(pFX, _T("[NewsText]"), m_NewsText, 10000);
	RFX_Text(pFX, _T("[KeyWords]"), m_KeyWords);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSNews diagnostics

#ifdef _DEBUG
void CRSNews::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSNews::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
