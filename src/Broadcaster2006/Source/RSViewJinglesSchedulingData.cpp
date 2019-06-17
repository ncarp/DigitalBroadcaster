// RSViewJinglesSchedulingData.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSViewJinglesSchedulingData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSViewJinglesSchedulingData

IMPLEMENT_DYNAMIC(CRSViewJinglesSchedulingData, CRecordset)

CRSViewJinglesSchedulingData::CRSViewJinglesSchedulingData(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSViewJinglesSchedulingData)
	m_JingleID = 0;
	m_Name = _T("");
	m_Rythm = 0;
	m_Length = 0;
	m_Intro = 0;
	m_JingleType = _T("");
	m_nFields = 9;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSViewJinglesSchedulingData::GetDefaultConnect()
{
	return strConnect;
}

CString CRSViewJinglesSchedulingData::GetDefaultSQL()
{
	return _T("[dbo].[ViewJinglesSchedulingData]");
}

void CRSViewJinglesSchedulingData::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSViewJinglesSchedulingData)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[JingleID]"), m_JingleID);
	RFX_Date(pFX, _T("[StartingDate]"), m_StartingDate);
	RFX_Date(pFX, _T("[EndingDate]"), m_EndingDate);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Long(pFX, _T("[Rythm]"), m_Rythm);
	RFX_Long(pFX, _T("[Length]"), m_Length);
	RFX_Long(pFX, _T("[Intro]"), m_Intro);
	RFX_Text(pFX, _T("[JingleType]"), m_JingleType);
	RFX_Date(pFX, _T("[MaxDate]"), m_MaxDate);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSViewJinglesSchedulingData diagnostics

#ifdef _DEBUG
void CRSViewJinglesSchedulingData::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSViewJinglesSchedulingData::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
