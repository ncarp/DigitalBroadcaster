// RSViewTimeSignal.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSViewTimeSignal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSViewTimeSignal

IMPLEMENT_DYNAMIC(CRSViewTimeSignal, CRecordset)

CRSViewTimeSignal::CRSViewTimeSignal(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSViewTimeSignal)
	m_ID = 0;
	m_Name = _T("");
	m_FolderName = _T("");
	m_Path = _T("");
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}

CString CRSViewTimeSignal::GetDefaultConnect()
{
	return strConnect;
}

CString CRSViewTimeSignal::GetDefaultSQL()
{
	return _T("[dbo].[ViewTimeSignal]");
}

void CRSViewTimeSignal::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSViewTimeSignal)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Text(pFX, _T("[FolderName]"), m_FolderName);
	RFX_Text(pFX, _T("[Path]"), m_Path);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSViewTimeSignal diagnostics

#ifdef _DEBUG
void CRSViewTimeSignal::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSViewTimeSignal::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
