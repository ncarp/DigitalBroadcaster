// RSScheduleHeadline.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSScheduleHeadline.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSScheduleHeadline

IMPLEMENT_DYNAMIC(CRSScheduleHeadline, CRecordset)

CRSScheduleHeadline::CRSScheduleHeadline(CString str, CDatabase *pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRSScheduleHeadline)
	m_ID = 0;
	m_Priority = 0;
	m_Name = _T("");
	m_TemplateID = 0;
	m_nFields = 6;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSScheduleHeadline::GetDefaultConnect()
{
	return strConnect;
}

CString CRSScheduleHeadline::GetDefaultSQL()
{
	return _T("[dbo].[SchedulingHeadlines]");
}

void CRSScheduleHeadline::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSScheduleHeadline)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Date(pFX, _T("[Date]"), m_Date);
	RFX_Date(pFX, _T("[EndingDate]"), m_EndingDate);
	RFX_Long(pFX, _T("[Priority]"), m_Priority);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Long(pFX, _T("[TemplateID]"), m_TemplateID);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSScheduleHeadline diagnostics

#ifdef _DEBUG
void CRSScheduleHeadline::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSScheduleHeadline::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
