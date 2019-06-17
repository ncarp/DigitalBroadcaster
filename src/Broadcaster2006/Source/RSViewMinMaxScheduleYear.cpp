// RSViewMinMaxScheduleYear.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSViewMinMaxScheduleYear.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSViewMinMaxScheduleYear

IMPLEMENT_DYNAMIC(CRSViewMinMaxScheduleYear, CRecordset)

CRSViewMinMaxScheduleYear::CRSViewMinMaxScheduleYear(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSViewMinMaxScheduleYear)
	m_Min = 0;
	m_Max = 0;
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSViewMinMaxScheduleYear::GetDefaultConnect()
{
	return strConnect;
}

CString CRSViewMinMaxScheduleYear::GetDefaultSQL()
{
	return _T("[dbo].[ViewMaxMinYearOnSchedule]");
}

void CRSViewMinMaxScheduleYear::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSViewMinMaxScheduleYear)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[Min]"), m_Min);
	RFX_Long(pFX, _T("[Max]"), m_Max);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSViewMinMaxScheduleYear diagnostics

#ifdef _DEBUG
void CRSViewMinMaxScheduleYear::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSViewMinMaxScheduleYear::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
