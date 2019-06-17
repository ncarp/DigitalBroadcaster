// RSViewSchedule.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSViewSchedule.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSViewSchedule

IMPLEMENT_DYNAMIC(CRSViewSchedule, CRecordset)

CRSViewSchedule::CRSViewSchedule(CString str,CDatabase *pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRSViewSchedule)
	m_ItemOrder = 0;
	m_ItemType = 0;
	m_ItemID = 0;
	m_ScheduleID = 0;
	m_Type = _T("");
	m_Name = _T("");
	m_TemplateID = 0;
	m_TemplateName = _T("");
	m_Intro = 0;
	m_Mix = 0;
	m_Start = 0;
	m_TypeID = 0;
	m_Priority = 0;
	m_Rythm = 0;
	m_nFields = 15;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSViewSchedule::GetDefaultConnect()
{
	return strConnect;
}

CString CRSViewSchedule::GetDefaultSQL()
{
	return _T("[dbo].[ViewSchedule]");
}

void CRSViewSchedule::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSViewSchedule)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Date(pFX, _T("[Date]"), m_Date);
	RFX_Long(pFX, _T("[ItemOrder]"), m_ItemOrder);
	RFX_Long(pFX, _T("[ItemType]"), m_ItemType);
	RFX_Long(pFX, _T("[ItemID]"), m_ItemID);
	RFX_Long(pFX, _T("[ScheduleID]"), m_ScheduleID);
	RFX_Text(pFX, _T("[Type]"), m_Type);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Long(pFX, _T("[TemplateID]"), m_TemplateID);
	RFX_Text(pFX, _T("[TemplateName]"), m_TemplateName);
	RFX_Long(pFX, _T("[Intro]"), m_Intro);
	RFX_Long(pFX, _T("[Mix]"), m_Mix);
	RFX_Long(pFX, _T("[Start]"), m_Start);
	RFX_Long(pFX, _T("[TypeID]"), m_TypeID);
	RFX_Long(pFX, _T("[Priority]"), m_Priority);
	RFX_Long(pFX, _T("[Rythm]"), m_Rythm);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSViewSchedule diagnostics

#ifdef _DEBUG
void CRSViewSchedule::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSViewSchedule::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
