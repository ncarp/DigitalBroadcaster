// RSViewJinglesOnAir.cpp : implementation file
//

#include "stdafx.h"

#include "RSViewJinglesOnAir.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSViewJinglesOnAir

IMPLEMENT_DYNAMIC(CRSViewJinglesOnAir, CRecordset)

CRSViewJinglesOnAir::CRSViewJinglesOnAir(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSViewJinglesOnAir)
	m_JingleID = 0;
	m_Name = _T("");
	m_Rythm = 0;
	m_JingleType = _T("");
	m_Length = 0;
	m_Intro = 0;
	m_nFields = 8;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	m_strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSViewJinglesOnAir::GetDefaultConnect()
{
	return (m_strConnect);
}

CString CRSViewJinglesOnAir::GetDefaultSQL()
{
	return _T("[dbo].[ViewJingles_OnAir]");
}

void CRSViewJinglesOnAir::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSViewJinglesOnAir)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[JingleID]"), m_JingleID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Long(pFX, _T("[Rythm]"), m_Rythm);
	RFX_Text(pFX, _T("[JingleType]"), m_JingleType);
	RFX_Long(pFX, _T("[Length]"), m_Length);
	RFX_Long(pFX, _T("[Intro]"), m_Intro);
	RFX_Date(pFX, _T("[StartingDate]"), m_StartingTime);
	RFX_Date(pFX, _T("[EndingDate]"), m_EndingTime);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSViewJinglesOnAir diagnostics

#ifdef _DEBUG
void CRSViewJinglesOnAir::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSViewJinglesOnAir::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
