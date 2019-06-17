// RSPath.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSPath.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSPath

IMPLEMENT_DYNAMIC(CRSPath, CRecordset)

CRSPath::CRSPath(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSPath)
	m_ID = 0;
	m_Path = _T("");
	m_Music = 0;
	m_Jingles = 0;
	m_Spots = 0;
	m_RMs = 0;
	m_TimeSignal = 0;
	m_Takes = 0;
	m_Producer = 0;
	m_nFields = 9;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	m_strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSPath::GetDefaultConnect()
{
	return m_strConnect;
}

CString CRSPath::GetDefaultSQL()
{
	return _T("[dbo].[HD]");
}

void CRSPath::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSPath)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Path]"), m_Path);
	RFX_Long(pFX, _T("[Music]"), m_Music);
	RFX_Long(pFX, _T("[Jingles]"), m_Jingles);
	RFX_Long(pFX, _T("[Spots]"), m_Spots);
	RFX_Long(pFX, _T("[RMs]"), m_RMs);
	RFX_Long(pFX, _T("[TimeSignal]"), m_TimeSignal);
	RFX_Long(pFX, _T("[Takes]"), m_Takes);
	RFX_Long(pFX, _T("[Producer]"), m_Producer);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSPath diagnostics

#ifdef _DEBUG
void CRSPath::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSPath::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
