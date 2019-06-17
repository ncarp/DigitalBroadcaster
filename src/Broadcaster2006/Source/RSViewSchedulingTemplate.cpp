// RSViewSchedulingTemplate.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSViewSchedulingTemplate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSViewSchedulingTemplate

IMPLEMENT_DYNAMIC(CRSViewSchedulingTemplate, CRecordset)

CRSViewSchedulingTemplate::CRSViewSchedulingTemplate(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSViewSchedulingTemplate)
	m_ID = 0;
	m_Type = 0;
	m_Name = _T("");
	m_CategoryName = _T("");
	m_Category = 0;
	m_PlayList = 0;
	m_PlayListName = _T("");
	m_Expression = 0;
	m_ExpressionName = _T("");
	m_MinRythm = 0;
	m_MaxRythm = 0;
	m_MinLen = 0;
	m_MaxLen = 0;
	m_ArtistQuarantine = 0;
	m_RandomFactor = 0;
	m_SongQuarantine = 0;
	m_nFields = 16;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSViewSchedulingTemplate::GetDefaultConnect()
{
	return strConnect;;
}

CString CRSViewSchedulingTemplate::GetDefaultSQL()
{
	return _T("[dbo].[ViewSchedulingTemplate]");
}

void CRSViewSchedulingTemplate::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSViewSchedulingTemplate)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Long(pFX, _T("[Type]"), m_Type);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Text(pFX, _T("[CategoryName]"), m_CategoryName);
	RFX_Long(pFX, _T("[Category]"), m_Category);
	RFX_Long(pFX, _T("[PlayList]"), m_PlayList);
	RFX_Text(pFX, _T("[PlayListName]"), m_PlayListName);
	RFX_Long(pFX, _T("[Expression]"), m_Expression);
	RFX_Text(pFX, _T("[ExpressionName]"), m_ExpressionName);
	RFX_Long(pFX, _T("[MinRythm]"), m_MinRythm);
	RFX_Long(pFX, _T("[MaxRythm]"), m_MaxRythm);
	RFX_Long(pFX, _T("[MinLen]"), m_MinLen);
	RFX_Long(pFX, _T("[MaxLen]"), m_MaxLen);
	RFX_Long(pFX, _T("[ArtistQuarantine]"), m_ArtistQuarantine);
	RFX_Long(pFX, _T("[RandomFactor]"), m_RandomFactor);
	RFX_Long(pFX, _T("[SongQuarantine]"), m_SongQuarantine);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSViewSchedulingTemplate diagnostics

#ifdef _DEBUG
void CRSViewSchedulingTemplate::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSViewSchedulingTemplate::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
