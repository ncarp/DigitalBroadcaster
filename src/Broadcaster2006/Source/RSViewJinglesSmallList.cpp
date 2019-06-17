// RSViewJinglesSmallList.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSViewJinglesSmallList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSViewJinglesSmallList

IMPLEMENT_DYNAMIC(CRSViewJinglesSmallList, CRecordset)

CRSViewJinglesSmallList::CRSViewJinglesSmallList(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSViewJinglesSmallList)
	m_ID = 0;
	m_Jingle = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	m_strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSViewJinglesSmallList::GetDefaultConnect()
{
	return m_strConnect;
}

CString CRSViewJinglesSmallList::GetDefaultSQL()
{
	return _T("[dbo].[ViewJinglesSmallList]");
}

void CRSViewJinglesSmallList::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSViewJinglesSmallList)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Jingle]"), m_Jingle);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSViewJinglesSmallList diagnostics

#ifdef _DEBUG
void CRSViewJinglesSmallList::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSViewJinglesSmallList::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
