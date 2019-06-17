// RSViewWorkingSchedule.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSViewWorkingSchedule.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSViewWorkingSchedule

IMPLEMENT_DYNAMIC(CRSViewWorkingSchedule, CRecordset)

CRSViewWorkingSchedule::CRSViewWorkingSchedule(CString str,CDatabase *pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRSViewWorkingSchedule)
	m_ID = 0;
	m_ItemType = 0;
	m_ItemID = 0;
	m_ScheduleID = 0;
	m_Priority = 0;
	m_TemplateID = 0;
	m_strSQL = _T("");
	m_ItemOrder = 0;
	m_ItemParentID = 0;
	m_ArtistQuarantine = 0;
	m_Name = _T("");
	m_RandomFactor = 0;
	m_SongQuarantine = 0;
	m_LastPos = 0;
	m_nFields = 14;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSViewWorkingSchedule::GetDefaultConnect()
{
	return strConnect;
}

CString CRSViewWorkingSchedule::GetDefaultSQL()
{
	return _T("[dbo].[ViewWorkingSchedule]");
}

void CRSViewWorkingSchedule::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSViewWorkingSchedule)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Long(pFX, _T("[ItemType]"), m_ItemType);
	RFX_Long(pFX, _T("[ItemID]"), m_ItemID);
	RFX_Long(pFX, _T("[ScheduleID]"), m_ScheduleID);
	RFX_Long(pFX, _T("[Priority]"), m_Priority);
	RFX_Long(pFX, _T("[TemplateID]"), m_TemplateID);
	RFX_Text(pFX, _T("[strSQL]"), m_strSQL);
	RFX_Long(pFX, _T("[ItemOrder]"), m_ItemOrder);
	RFX_Long(pFX, _T("[ItemParentID]"), m_ItemParentID);
	RFX_Long(pFX, _T("[ArtistQuarantine]"), m_ArtistQuarantine);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Long(pFX, _T("[RandomFactor]"), m_RandomFactor);
	RFX_Long(pFX, _T("[SongQuarantine]"), m_SongQuarantine);
	RFX_Long(pFX, _T("[LastPos]"), m_LastPos);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSViewWorkingSchedule diagnostics

#ifdef _DEBUG
void CRSViewWorkingSchedule::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSViewWorkingSchedule::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
