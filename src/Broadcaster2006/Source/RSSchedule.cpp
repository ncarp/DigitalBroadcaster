// RSSchedule.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSSchedule.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSSchedule

IMPLEMENT_DYNAMIC(CRSSchedule, CRecordset)

CRSSchedule::CRSSchedule(CString str,CDatabase *pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRSSchedule)
	m_ID = 0;
	m_ItemOrder = 0;
	m_ItemType = 0;
	m_ItemID = 0;
	m_ScheduleID = 0;
	m_Start = 0;
	m_End = 0;
	m_Priority = 0;
	m_Aired = 0;
	m_TemplateID = 0;
	m_ItemParentID = 0;
	m_Mix = 0;
	m_nFields = 13;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSSchedule::GetDefaultConnect()
{
	return strConnect;
}

CString CRSSchedule::GetDefaultSQL()
{
	return _T("[dbo].[Scheduling]");
}

void CRSSchedule::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSSchedule)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Date(pFX, _T("[Date]"), m_Date);
	RFX_Long(pFX, _T("[ItemOrder]"), m_ItemOrder);
	RFX_Long(pFX, _T("[ItemType]"), m_ItemType);
	RFX_Long(pFX, _T("[ItemID]"), m_ItemID);
	RFX_Long(pFX, _T("[ScheduleID]"), m_ScheduleID);
	RFX_Long(pFX, _T("[Start]"), m_Start);
	RFX_Long(pFX, _T("[End]"), m_End);
	RFX_Long(pFX, _T("[Priority]"), m_Priority);
	RFX_Long(pFX, _T("[Aired]"), m_Aired);
	RFX_Long(pFX, _T("[TemplateID]"), m_TemplateID);
	RFX_Long(pFX, _T("[ItemParentID]"), m_ItemParentID);
	RFX_Long(pFX, _T("[Mix]"), m_Mix);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSSchedule diagnostics

#ifdef _DEBUG
void CRSSchedule::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSSchedule::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
