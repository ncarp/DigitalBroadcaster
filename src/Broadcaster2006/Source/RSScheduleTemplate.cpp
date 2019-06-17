// RSScheduleTemplate.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSScheduleTemplate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSScheduleTemplate

IMPLEMENT_DYNAMIC(CRSScheduleTemplate, CRecordset)

CRSScheduleTemplate::CRSScheduleTemplate(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSScheduleTemplate)
	m_ID = 0;
	m_Type = 0;
	m_Name = _T("");
	m_strSQL = _T("");
	m_Category = 0;
	m_Expression = 0;
	m_MaxLen = 0;
	m_MaxRythm = 0;
	m_MinLen = 0;
	m_MinRythm = 0;
	m_PlayList = 0;
	m_ArtistQuarantine = 0;
	m_RandomFactor = 0;
	m_SongQuarantine = 0;
	m_nFields = 14;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSScheduleTemplate::GetDefaultConnect()
{
	return strConnect;
}

CString CRSScheduleTemplate::GetDefaultSQL()
{
	return _T("[dbo].[SchedulingTemplate]");
}

void CRSScheduleTemplate::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSScheduleTemplate)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Long(pFX, _T("[Type]"), m_Type);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Text(pFX, _T("[strSQL]"), m_strSQL);
	RFX_Long(pFX, _T("[Category]"), m_Category);
	RFX_Long(pFX, _T("[Expression]"), m_Expression);
	RFX_Long(pFX, _T("[MaxLen]"), m_MaxLen);
	RFX_Long(pFX, _T("[MaxRythm]"), m_MaxRythm);
	RFX_Long(pFX, _T("[MinLen]"), m_MinLen);
	RFX_Long(pFX, _T("[MinRythm]"), m_MinRythm);
	RFX_Long(pFX, _T("[PlayList]"), m_PlayList);
	RFX_Long(pFX, _T("[ArtistQuarantine]"), m_ArtistQuarantine);
	RFX_Long(pFX, _T("[RandomFactor]"), m_RandomFactor);
	RFX_Long(pFX, _T("[SongQuarantine]"), m_SongQuarantine);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSScheduleTemplate diagnostics

#ifdef _DEBUG
void CRSScheduleTemplate::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSScheduleTemplate::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
