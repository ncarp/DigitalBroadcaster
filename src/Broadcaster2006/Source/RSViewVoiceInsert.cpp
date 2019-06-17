// RSViewVoiceInsert.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSViewVoiceInsert.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSViewVoiceInsert

IMPLEMENT_DYNAMIC(CRSViewVoiceInsert, CRecordset)

CRSViewVoiceInsert::CRSViewVoiceInsert(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSViewVoiceInsert)
	m_User = _T("");
	m_ID = 0;
	m_Name = _T("");
	m_FileName = _T("");
	m_Path = 0;
	m_Start = 0;
	m_Finish = 0;
	m_TalentID = 0;
	m_Activ = 0;
	m_PathName = _T("");
	m_nFields = 10;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSViewVoiceInsert::GetDefaultConnect()
{
	return strConnect;
}

CString CRSViewVoiceInsert::GetDefaultSQL()
{
	return _T("[dbo].[ViewVoiceInsert]");
}

void CRSViewVoiceInsert::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSViewVoiceInsert)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[User]"), m_User);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Text(pFX, _T("[FileName]"), m_FileName);
	RFX_Long(pFX, _T("[Path]"), m_Path);
	RFX_Long(pFX, _T("[Start]"), m_Start);
	RFX_Long(pFX, _T("[Finish]"), m_Finish);
	RFX_Long(pFX, _T("[TalentID]"), m_TalentID);
	RFX_Long(pFX, _T("[Activ]"), m_Activ);
	RFX_Text(pFX, _T("[PathName]"), m_PathName);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSViewVoiceInsert diagnostics

#ifdef _DEBUG
void CRSViewVoiceInsert::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSViewVoiceInsert::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
