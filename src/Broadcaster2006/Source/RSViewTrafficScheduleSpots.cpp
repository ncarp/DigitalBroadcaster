// RSViewTrafficScheduleSpots.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSViewTrafficScheduleSpots.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSViewTrafficScheduleSpots

IMPLEMENT_DYNAMIC(CRSViewTrafficScheduleSpots, CRecordset)

CRSViewTrafficScheduleSpots::CRSViewTrafficScheduleSpots(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSViewTrafficScheduleSpots)
	m_ScheduleID = 0;
	m_Position = 0;
	m_SpotID = 0;
	m_Sun = 0;
	m_Mon = 0;
	m_Tue = 0;
	m_Wed = 0;
	m_Thu = 0;
	m_Fri = 0;
	m_Sat = 0;
	m_Name = _T("");
	m_nFields = 13;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	m_strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSViewTrafficScheduleSpots::GetDefaultConnect()
{
	return m_strConnect;
}

CString CRSViewTrafficScheduleSpots::GetDefaultSQL()
{
	return _T("[dbo].[ViewTrafficScheduleSpots]");
}

void CRSViewTrafficScheduleSpots::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSViewTrafficScheduleSpots)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ScheduleID]"), m_ScheduleID);
	RFX_Long(pFX, _T("[Position]"), m_Position);
	RFX_Long(pFX, _T("[SpotID]"), m_SpotID);
	RFX_Date(pFX, _T("[StartingDate]"), m_StartingDate);
	RFX_Date(pFX, _T("[EndingDate]"), m_EndingDate);
	RFX_Long(pFX, _T("[Sun]"), m_Sun);
	RFX_Long(pFX, _T("[Mon]"), m_Mon);
	RFX_Long(pFX, _T("[Tue]"), m_Tue);
	RFX_Long(pFX, _T("[Wed]"), m_Wed);
	RFX_Long(pFX, _T("[Thu]"), m_Thu);
	RFX_Long(pFX, _T("[Fri]"), m_Fri);
	RFX_Long(pFX, _T("[Sat]"), m_Sat);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSViewTrafficScheduleSpots diagnostics

#ifdef _DEBUG
void CRSViewTrafficScheduleSpots::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSViewTrafficScheduleSpots::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
