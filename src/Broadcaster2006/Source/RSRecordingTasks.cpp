// RSRecordingTasks.cpp : implementation file
//

#include "stdafx.h"
#include "..\OnAir\OnAir.h"
#include "..\include\RSRecordingTasks.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSRecordingTasks

IMPLEMENT_DYNAMIC(CRSRecordingTasks, CRecordset)

CRSRecordingTasks::CRSRecordingTasks(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSRecordingTasks)
	m_ID = 0;
	m_Name = _T("");
	m_TalentID = 0;
	m_Todo = _T("");
	m_Completed = 0;
	m_nFields = 6;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	m_strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSRecordingTasks::GetDefaultConnect()
{
	return m_strConnect;
}

CString CRSRecordingTasks::GetDefaultSQL()
{
	return _T("[dbo].[RecordingTask]");
}

void CRSRecordingTasks::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSRecordingTasks)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Long(pFX, _T("[TalentID]"), m_TalentID);
	RFX_Date(pFX, _T("[Deadline]"), m_Deadline);
	RFX_Text(pFX, _T("[Todo]"), m_Todo,10000);
	RFX_Long(pFX, _T("[Completed]"), m_Completed);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSRecordingTasks diagnostics

#ifdef _DEBUG
void CRSRecordingTasks::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSRecordingTasks::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
