// RSScheduleSpots.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSScheduleSpots.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSScheduleSpots

IMPLEMENT_DYNAMIC(CRSScheduleSpots, CRecordset)

CRSScheduleSpots::CRSScheduleSpots(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSScheduleSpots)
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
	m_nFields = 12;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSScheduleSpots::GetDefaultConnect()
{
	return strConnect;
}

CString CRSScheduleSpots::GetDefaultSQL()
{
	return _T("[dbo].[TrafficScheduleSpots]");
}

void CRSScheduleSpots::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSScheduleSpots)
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
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSScheduleSpots diagnostics

#ifdef _DEBUG
void CRSScheduleSpots::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSScheduleSpots::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
