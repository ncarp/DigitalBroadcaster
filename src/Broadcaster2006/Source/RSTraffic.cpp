// RSTraffic.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSTraffic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSTraffic

IMPLEMENT_DYNAMIC(CRSTraffic, CRecordset)

CRSTraffic::CRSTraffic(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSTraffic)
	m_ID = 0;
	m_BlockID = 0;
	m_ScheduleID = 0;
	m_Value = 0.0f;
	m_Aired = 0;
	m_TalentID = 0;
	m_Suspend = 0;
	m_Position = 0;
	m_SpotID = 0;
	m_nFields = 11;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSTraffic::GetDefaultConnect()
{
	return strConnect;
}

CString CRSTraffic::GetDefaultSQL()
{
	return _T("[dbo].[Traffic]");
}

void CRSTraffic::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSTraffic)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Long(pFX, _T("[BlockID]"), m_BlockID);
	RFX_Date(pFX, _T("[BlockDate]"), m_BlockDate);
	RFX_Long(pFX, _T("[ScheduleID]"), m_ScheduleID);
	RFX_Single(pFX, _T("[Value]"), m_Value);
	RFX_Long(pFX, _T("[Aired]"), m_Aired);
	RFX_Date(pFX, _T("[AiringDate]"), m_AiringDate);
	RFX_Long(pFX, _T("[TalentID]"), m_TalentID);
	RFX_Long(pFX, _T("[Suspend]"), m_Suspend);
	RFX_Long(pFX, _T("[Position]"), m_Position);
	RFX_Long(pFX, _T("[SpotID]"), m_SpotID);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSTraffic diagnostics

#ifdef _DEBUG
void CRSTraffic::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSTraffic::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
