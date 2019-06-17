// RSViewRecordingTasks.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSViewRecordingTasks.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSViewRecordingTasks

IMPLEMENT_DYNAMIC(CRSViewRecordingTasks, CRecordset)

CRSViewRecordingTasks::CRSViewRecordingTasks(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSViewRecordingTasks)
	m_ID = 0;
	m_Name = _T("");
	m_TalentID = 0;
	m_Todo = _T("");
	m_Completed = 0;
	m_UserName = _T("");
	m_nFields = 7;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSViewRecordingTasks::GetDefaultConnect()
{
	return strConnect;
}

CString CRSViewRecordingTasks::GetDefaultSQL()
{
	return _T("[dbo].[ViewRecordingTasks]");
}

void CRSViewRecordingTasks::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSViewRecordingTasks)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Long(pFX, _T("[TalentID]"), m_TalentID);
	RFX_Date(pFX, _T("[Deadline]"), m_Deadline);
	RFX_Text(pFX, _T("[Todo]"), m_Todo, 10000);
	RFX_Long(pFX, _T("[Completed]"), m_Completed);
	RFX_Text(pFX, _T("[UserName]"), m_UserName);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSViewRecordingTasks diagnostics

#ifdef _DEBUG
void CRSViewRecordingTasks::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSViewRecordingTasks::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
