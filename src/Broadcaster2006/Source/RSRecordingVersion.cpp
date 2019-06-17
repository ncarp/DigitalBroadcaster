// RSRecordingVersion.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSRecordingVersion.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSRecordingVersion

IMPLEMENT_DYNAMIC(CRSRecordingVersion, CRecordset)

CRSRecordingVersion::CRSRecordingVersion(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSRecordingVersion)
	m_ID = 0;
	m_RecordingID = 0;
	m_Name = _T("");
	m_FileName = _T("");
	m_PathID = 0;
	m_Remarks = _T("");
	m_Deleted = 0;
	m_nFields = 7;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSRecordingVersion::GetDefaultConnect()
{
	return strConnect;
}

CString CRSRecordingVersion::GetDefaultSQL()
{
	return _T("[dbo].[RecordingVersion]");
}

void CRSRecordingVersion::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSRecordingVersion)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Long(pFX, _T("[RecordingID]"), m_RecordingID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Text(pFX, _T("[FileName]"), m_FileName);
	RFX_Long(pFX, _T("[PathID]"), m_PathID);
	RFX_Text(pFX, _T("[Remarks]"), m_Remarks);
	RFX_Long(pFX, _T("[Deleted]"), m_Deleted);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSRecordingVersion diagnostics

#ifdef _DEBUG
void CRSRecordingVersion::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSRecordingVersion::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
