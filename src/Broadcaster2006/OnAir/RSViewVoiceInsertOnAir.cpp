// RSViewVoiceInsertOnAir.cpp : implementation file
//

#include "stdafx.h"
#include "RSViewVoiceInsertOnAir.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSViewVoiceInsertOnAir

IMPLEMENT_DYNAMIC(CRSViewVoiceInsertOnAir, CRecordset)

CRSViewVoiceInsertOnAir::CRSViewVoiceInsertOnAir(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSViewVoiceInsertOnAir)
	m_ID = 0;
	m_Name = _T("");
	m_FileName = _T("");
	m_Path = _T("");
	m_Start = 0;
	m_Finish = 0;
	m_nFields = 6;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	m_strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSViewVoiceInsertOnAir::GetDefaultConnect()
{
	return m_strConnect;
}

CString CRSViewVoiceInsertOnAir::GetDefaultSQL()
{
	return _T("[dbo].[ViewVoiceInsertOnAir]");
}

void CRSViewVoiceInsertOnAir::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSViewVoiceInsertOnAir)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Text(pFX, _T("[FileName]"), m_FileName);
	RFX_Text(pFX, _T("[Path]"), m_Path);
	RFX_Long(pFX, _T("[Start]"), m_Start);
	RFX_Long(pFX, _T("[Finish]"), m_Finish);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSViewVoiceInsertOnAir diagnostics

#ifdef _DEBUG
void CRSViewVoiceInsertOnAir::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSViewVoiceInsertOnAir::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
