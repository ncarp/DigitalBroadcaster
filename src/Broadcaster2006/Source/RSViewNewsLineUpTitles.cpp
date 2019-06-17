// RSViewNewsLineUpTitles.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSViewNewsLineUpTitles.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSViewNewsLineUpTitles

IMPLEMENT_DYNAMIC(CRSViewNewsLineUpTitles, CRecordset)

CRSViewNewsLineUpTitles::CRSViewNewsLineUpTitles(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSViewNewsLineUpTitles)
	m_LineUpID = 0;
	m_Position = 0;
	m_News = _T("");
	m_NewsID = 0;
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSViewNewsLineUpTitles::GetDefaultConnect()
{
	return strConnect;
}

CString CRSViewNewsLineUpTitles::GetDefaultSQL()
{
	return _T("[dbo].[ViewNewsLineUpTitles]");
}

void CRSViewNewsLineUpTitles::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSViewNewsLineUpTitles)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[LineUpID]"), m_LineUpID);
	RFX_Long(pFX, _T("[Position]"), m_Position);
	RFX_Text(pFX, _T("[News]"), m_News);
	RFX_Long(pFX, _T("[NewsID]"), m_NewsID);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSViewNewsLineUpTitles diagnostics

#ifdef _DEBUG
void CRSViewNewsLineUpTitles::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSViewNewsLineUpTitles::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
