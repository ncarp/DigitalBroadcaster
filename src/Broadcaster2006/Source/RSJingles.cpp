// RSJingles.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSJingles.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSJingles

IMPLEMENT_DYNAMIC(CRSJingles, CRecordset)

CRSJingles::CRSJingles(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSJingles)
	m_ID = 0;
	m_TypeID = 0;
	m_Name = _T("");
	m_Rythm = 0;
	m_LoopA = 0;
	m_LoopB = 0;
	m_Start = 0;
	m_Intro = 0;
	m_Mix = 0;
	m_Finish = 0;
	m_Activ = 0;
	m_Ready = 0;
	m_PathID = 0;
	m_FileName = _T("");
	m_DRM35 = _T("");
	m_nFields = 15;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSJingles::GetDefaultConnect()
{
	return strConnect;
}

CString CRSJingles::GetDefaultSQL()
{
	return _T("[dbo].[Jingles]");
}

void CRSJingles::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSJingles)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Long(pFX, _T("[TypeID]"), m_TypeID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Long(pFX, _T("[Rythm]"), m_Rythm);
	RFX_Long(pFX, _T("[LoopA]"), m_LoopA);
	RFX_Long(pFX, _T("[LoopB]"), m_LoopB);
	RFX_Long(pFX, _T("[Start]"), m_Start);
	RFX_Long(pFX, _T("[Intro]"), m_Intro);
	RFX_Long(pFX, _T("[Mix]"), m_Mix);
	RFX_Long(pFX, _T("[Finish]"), m_Finish);
	RFX_Long(pFX, _T("[Activ]"), m_Activ);
	RFX_Long(pFX, _T("[Ready]"), m_Ready);
	RFX_Long(pFX, _T("[PathID]"), m_PathID);
	RFX_Text(pFX, _T("[FileName]"), m_FileName);
	RFX_Text(pFX, _T("[DRM35]"), m_DRM35);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSJingles diagnostics

#ifdef _DEBUG
void CRSJingles::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSJingles::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
