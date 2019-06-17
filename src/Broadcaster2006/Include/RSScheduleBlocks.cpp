// RSScheduleBlocks.cpp : implementation file
//

#include "stdafx.h"
#include "RSScheduleBlocks.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSScheduleBlocks

IMPLEMENT_DYNAMIC(CRSScheduleBlocks, CRecordset)

CRSScheduleBlocks::CRSScheduleBlocks(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSScheduleBlocks)
	m_BlockID = 0;
	m_Sun = 0;
	m_Mon = 0;
	m_Tue = 0;
	m_Wed = 0;
	m_Thu = 0;
	m_Fri = 0;
	m_Sat = 0;
	m_Position = 0;
	m_Value = 0.0f;
	m_ScheduleID = 0;
	m_StationID = 0;
	m_nFields = 14;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSScheduleBlocks::GetDefaultConnect()
{
	return strConnect;
}

CString CRSScheduleBlocks::GetDefaultSQL()
{
	return _T("[dbo].[TrafficScheduleBlocks]");
}

void CRSScheduleBlocks::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSScheduleBlocks)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[BlockID]"), m_BlockID);
	RFX_Long(pFX, _T("[Sun]"), m_Sun);
	RFX_Long(pFX, _T("[Mon]"), m_Mon);
	RFX_Long(pFX, _T("[Tue]"), m_Tue);
	RFX_Long(pFX, _T("[Wed]"), m_Wed);
	RFX_Long(pFX, _T("[Thu]"), m_Thu);
	RFX_Long(pFX, _T("[Fri]"), m_Fri);
	RFX_Long(pFX, _T("[Sat]"), m_Sat);
	RFX_Long(pFX, _T("[Position]"), m_Position);
	RFX_Single(pFX, _T("[Value]"), m_Value);
	RFX_Long(pFX, _T("[ScheduleID]"), m_ScheduleID);
	RFX_Long(pFX, _T("[StationID]"), m_StationID);
	RFX_Date(pFX, _T("[StartingDate]"), m_StartingDate);
	RFX_Date(pFX, _T("[EndingDate]"), m_EndingDate);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSScheduleBlocks diagnostics

#ifdef _DEBUG
void CRSScheduleBlocks::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSScheduleBlocks::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
