// RSViewTrafficSchedule.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSViewTrafficSchedule.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSViewTrafficSchedule

IMPLEMENT_DYNAMIC(CRSViewTrafficSchedule, CRecordset)

CRSViewTrafficSchedule::CRSViewTrafficSchedule(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSViewTrafficSchedule)
	m_ID = 0;
	m_Insertions = 0;
	m_Value = 0;
	m_Type = 0;
	m_Suspend = 0;
	m_DRM35 = _T("");
	m_StationID = 0;
	m_CustomerID = 0;
	m_RadioName = _T("");
	m_DSN = _T("");
	m_DB = _T("");
	m_CustomerName = _T("");
	m_TypeOfValue = 0;
	m_nFields = 15;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSViewTrafficSchedule::GetDefaultConnect()
{
	return strConnect;
}

CString CRSViewTrafficSchedule::GetDefaultSQL()
{
	return _T("[dbo].[ViewTrafficSchedule]");
}

void CRSViewTrafficSchedule::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSViewTrafficSchedule)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Date(pFX, _T("[StartingDate]"), m_StartingDate);
	RFX_Date(pFX, _T("[EndingDate]"), m_EndingDate);
	RFX_Long(pFX, _T("[Insertions]"), m_Insertions);
	RFX_Single(pFX, _T("[Value]"), m_Value);
	RFX_Long(pFX, _T("[Type]"), m_Type);
	RFX_Long(pFX, _T("[Suspend]"), m_Suspend);
	RFX_Text(pFX, _T("[DRM35]"), m_DRM35);
	RFX_Long(pFX, _T("[StationID]"), m_StationID);
	RFX_Long(pFX, _T("[CustomerID]"), m_CustomerID);
	RFX_Text(pFX, _T("[RadioName]"), m_RadioName);
	RFX_Text(pFX, _T("[DSN]"), m_DSN);
	RFX_Text(pFX, _T("[DB]"), m_DB);
	RFX_Text(pFX, _T("[CustomerName]"), m_CustomerName);
	RFX_Long(pFX, _T("[TypeOfValue]"), m_TypeOfValue);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSViewTrafficSchedule diagnostics

#ifdef _DEBUG
void CRSViewTrafficSchedule::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSViewTrafficSchedule::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
