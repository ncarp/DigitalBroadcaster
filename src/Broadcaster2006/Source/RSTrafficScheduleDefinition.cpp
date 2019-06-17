// RSTrafficScheduleDefinition.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSTrafficScheduleDefinition.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSTrafficScheduleDefinition

IMPLEMENT_DYNAMIC(CRSTrafficScheduleDefinition, CRecordset)

CRSTrafficScheduleDefinition::CRSTrafficScheduleDefinition(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSTrafficScheduleDefinition)
	m_ID = 0;
	m_Insertions = 0;
	m_Value = _T("");
	m_Type = 0;
	m_Suspend = 0;
	m_DRM35 = _T("");
	m_StationID = 0;
	m_CustomerID = 0;
	m_TypeOfValue = 0;
	m_nFields = 11;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	m_strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSTrafficScheduleDefinition::GetDefaultConnect()
{
	return m_strConnect;
}

CString CRSTrafficScheduleDefinition::GetDefaultSQL()
{
	return _T("[dbo].[TrafficScheduleDefinition]");
}

void CRSTrafficScheduleDefinition::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSTrafficScheduleDefinition)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Date(pFX, _T("[StartingDate]"), m_StartingDate);
	RFX_Date(pFX, _T("[EndingDate]"), m_EndingDate);
	RFX_Long(pFX, _T("[Insertions]"), m_Insertions);
	RFX_Text(pFX, _T("[Value]"), m_Value);
	RFX_Long(pFX, _T("[Type]"), m_Type);
	RFX_Long(pFX, _T("[Suspend]"), m_Suspend);
	RFX_Text(pFX, _T("[DRM35]"), m_DRM35);
	RFX_Long(pFX, _T("[StationID]"), m_StationID);
	RFX_Long(pFX, _T("[CustomerID]"), m_CustomerID);
	RFX_Long(pFX, _T("[TypeOfValue]"), m_TypeOfValue);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSTrafficScheduleDefinition diagnostics

#ifdef _DEBUG
void CRSTrafficScheduleDefinition::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSTrafficScheduleDefinition::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
