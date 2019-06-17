// RSViewJinglesList.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSViewJinglesList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSViewJinglesList

IMPLEMENT_DYNAMIC(CRSViewJinglesList, CRecordset)

CRSViewJinglesList::CRSViewJinglesList(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSViewJinglesList)
	m_ID = 0;
	m_TypeID = 0;
	m_Name = _T("");
	m_Type = _T("");
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSViewJinglesList::GetDefaultConnect()
{
	return strConnect;
}

CString CRSViewJinglesList::GetDefaultSQL()
{
	return _T("[dbo].[ViewJinglesList]");
}

void CRSViewJinglesList::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSViewJinglesList)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Long(pFX, _T("[TypeID]"), m_TypeID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Text(pFX, _T("[Type]"), m_Type);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSViewJinglesList diagnostics

#ifdef _DEBUG
void CRSViewJinglesList::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSViewJinglesList::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
