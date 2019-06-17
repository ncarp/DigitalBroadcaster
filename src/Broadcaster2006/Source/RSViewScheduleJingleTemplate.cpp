// RSViewScheduleJingleTemplate.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSViewScheduleJingleTemplate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSViewScheduleJingleTemplate

IMPLEMENT_DYNAMIC(CRSViewScheduleJingleTemplate, CRecordset)

CRSViewScheduleJingleTemplate::CRSViewScheduleJingleTemplate(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSViewScheduleJingleTemplate)
	m_ID = 0;
	m_Name = _T("");
	m_TypeID = 0;
	m_MinRythm = 0;
	m_MaxRythm = 0;
	m_MinLen = 0;
	m_MaxLen = 0;
	m_TypeName = _T("");
	m_nFields = 8;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSViewScheduleJingleTemplate::GetDefaultConnect()
{
	return strConnect;
}

CString CRSViewScheduleJingleTemplate::GetDefaultSQL()
{
	return _T("[dbo].[ViewSchedulingJingleTemplate]");
}

void CRSViewScheduleJingleTemplate::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSViewScheduleJingleTemplate)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Long(pFX, _T("[TypeID]"), m_TypeID);
	RFX_Long(pFX, _T("[MinRythm]"), m_MinRythm);
	RFX_Long(pFX, _T("[MaxRythm]"), m_MaxRythm);
	RFX_Long(pFX, _T("[MinLen]"), m_MinLen);
	RFX_Long(pFX, _T("[MaxLen]"), m_MaxLen);
	RFX_Text(pFX, _T("[TypeName]"), m_TypeName);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSViewScheduleJingleTemplate diagnostics

#ifdef _DEBUG
void CRSViewScheduleJingleTemplate::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSViewScheduleJingleTemplate::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
