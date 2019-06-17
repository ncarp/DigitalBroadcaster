// RSViewRecordingTasksSmall.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSViewRecordingTasksSmall.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSViewRecordingTasksSmall

IMPLEMENT_DYNAMIC(CRSViewRecordingTasksSmall, CRecordset)

CRSViewRecordingTasksSmall::CRSViewRecordingTasksSmall(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSViewRecordingTasksSmall)
	m_ID = 0;
	m_Name = _T("");
	m_TalentID = 0;
	m_Completed = 0;
	m_UserName = _T("");
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSViewRecordingTasksSmall::GetDefaultConnect()
{
	return strConnect;
}

CString CRSViewRecordingTasksSmall::GetDefaultSQL()
{
	return _T("[dbo].[ViewRecordingTasksSmall]");
}

void CRSViewRecordingTasksSmall::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSViewRecordingTasksSmall)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Long(pFX, _T("[TalentID]"), m_TalentID);
	RFX_Long(pFX, _T("[Completed]"), m_Completed);
	RFX_Text(pFX, _T("[UserName]"), m_UserName);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSViewRecordingTasksSmall diagnostics

#ifdef _DEBUG
void CRSViewRecordingTasksSmall::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSViewRecordingTasksSmall::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
