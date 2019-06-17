// RSVoiceInsert.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSVoiceInsert.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSVoiceInsert

IMPLEMENT_DYNAMIC(CRSVoiceInsert, CRecordset)

CRSVoiceInsert::CRSVoiceInsert(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSVoiceInsert)
	m_ID = 0;
	m_Name = _T("");
	m_FileName = _T("");
	m_Path = 0;
	m_Start = 0;
	m_Finish = 0;
	m_TalentID = 0;
	m_Activ = 0;
	m_nFields = 8;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	m_strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSVoiceInsert::GetDefaultConnect()
{
	return m_strConnect;
}

CString CRSVoiceInsert::GetDefaultSQL()
{
	return _T("[dbo].[VoiceInserts]");
}

void CRSVoiceInsert::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSVoiceInsert)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Text(pFX, _T("[FileName]"), m_FileName);
	RFX_Long(pFX, _T("[Path]"), m_Path);
	RFX_Long(pFX, _T("[Start]"), m_Start);
	RFX_Long(pFX, _T("[Finish]"), m_Finish);
	RFX_Long(pFX, _T("[TalentID]"), m_TalentID);
	RFX_Long(pFX, _T("[Activ]"), m_Activ);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSVoiceInsert diagnostics

#ifdef _DEBUG
void CRSVoiceInsert::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSVoiceInsert::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
