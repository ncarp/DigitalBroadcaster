// RSViewRecordings.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSViewRecordings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSViewRecordings

IMPLEMENT_DYNAMIC(CRSViewRecordings, CRecordset)

CRSViewRecordings::CRSViewRecordings(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSViewRecordings)
	m_ID = 0;
	m_Name = _T("");
	m_TalentID = 0;
	m_Todo = _T("");
	m_Completed = 0;
	m_VersionID = 0;
	m_FileName = _T("");
	m_PathID = 0;
	m_Remarks = _T("");
	m_Deleted = 0;
	m_Path = _T("");
	m_VersionName = _T("");
	m_nFields = 13;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	m_strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSViewRecordings::GetDefaultConnect()
{
	return m_strConnect;
}

CString CRSViewRecordings::GetDefaultSQL()
{
	return _T("[dbo].[ViewRecordings]");
}

void CRSViewRecordings::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSViewRecordings)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Long(pFX, _T("[TalentID]"), m_TalentID);
	RFX_Date(pFX, _T("[Deadline]"), m_Deadline);
	RFX_Text(pFX, _T("[Todo]"), m_Todo,10000);
	RFX_Long(pFX, _T("[Completed]"), m_Completed);
	RFX_Long(pFX, _T("[VersionID]"), m_VersionID);
	RFX_Text(pFX, _T("[FileName]"), m_FileName);
	RFX_Long(pFX, _T("[PathID]"), m_PathID);
	RFX_Text(pFX, _T("[Remarks]"), m_Remarks,10000);
	RFX_Long(pFX, _T("[Deleted]"), m_Deleted);
	RFX_Text(pFX, _T("[Path]"), m_Path);
	RFX_Text(pFX, _T("[VersionName]"), m_VersionName);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSViewRecordings diagnostics

#ifdef _DEBUG
void CRSViewRecordings::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSViewRecordings::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
