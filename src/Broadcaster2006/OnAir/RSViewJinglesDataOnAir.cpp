// RSViewJinglesDataOnAir.cpp : implementation file
//

#include "stdafx.h"

#include "RSViewJinglesDataOnAir.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSViewJinglesDataOnAir

IMPLEMENT_DYNAMIC(CRSViewJinglesDataOnAir, CRecordset)

CRSViewJinglesDataOnAir::CRSViewJinglesDataOnAir(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSViewJinglesDataOnAir)
	m_ID = 0;
	m_TypeID = 0;
	m_Name = _T("");
	m_Rythm = 0;
	m_Start = 0;
	m_Intro = 0;
	m_Mix = 0;
	m_Finish = 0;
	m_LoopA = 0;
	m_LoopB = 0;
	m_FileName = _T("");
	m_TypeName = _T("");
	m_Path = _T("");
	m_nFields = 13;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	m_strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSViewJinglesDataOnAir::GetDefaultConnect()
{
	return m_strConnect;
}

CString CRSViewJinglesDataOnAir::GetDefaultSQL()
{
	return _T("[dbo].[ViewJinglesData_OnAir]");
}

void CRSViewJinglesDataOnAir::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSViewJinglesDataOnAir)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Long(pFX, _T("[TypeID]"), m_TypeID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Long(pFX, _T("[Rythm]"), m_Rythm);
	RFX_Long(pFX, _T("[Start]"), m_Start);
	RFX_Long(pFX, _T("[Intro]"), m_Intro);
	RFX_Long(pFX, _T("[Mix]"), m_Mix);
	RFX_Long(pFX, _T("[Finish]"), m_Finish);
	RFX_Long(pFX, _T("[LoopA]"), m_LoopA);
	RFX_Long(pFX, _T("[LoopB]"), m_LoopB);
	RFX_Text(pFX, _T("[FileName]"), m_FileName);
	RFX_Text(pFX, _T("[TypeName]"), m_TypeName);
	RFX_Text(pFX, _T("[Path]"), m_Path);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSViewJinglesDataOnAir diagnostics

#ifdef _DEBUG
void CRSViewJinglesDataOnAir::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSViewJinglesDataOnAir::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
