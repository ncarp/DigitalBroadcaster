// RSViewTraffic.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSViewTraffic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSViewTraffic

IMPLEMENT_DYNAMIC(CRSViewTraffic, CRecordset)

CRSViewTraffic::CRSViewTraffic(CString str,CDatabase *pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRSViewTraffic)
	m_ID = 0;
	m_BlockID = 0;
	m_Position = 0;
	m_SpotID = 0;
	m_TypeOfBusinessID = 0;
	m_MainVoiceID = 0;
	m_N = 0;
	m_nFields = 8;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSViewTraffic::GetDefaultConnect()
{
	return strConnect;
}

CString CRSViewTraffic::GetDefaultSQL()
{
	return _T("[dbo].[ViewTraffic]");
}

void CRSViewTraffic::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSViewTraffic)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Long(pFX, _T("[BlockID]"), m_BlockID);
	RFX_Date(pFX, _T("[BlockDate]"), m_BlockDate);
	RFX_Long(pFX, _T("[Position]"), m_Position);
	RFX_Long(pFX, _T("[SpotID]"), m_SpotID);
	RFX_Long(pFX, _T("[TypeOfBusinessID]"), m_TypeOfBusinessID);
	RFX_Long(pFX, _T("[MainVoiceID]"), m_MainVoiceID);
	RFX_Long(pFX, _T("[N]"), m_N);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSViewTraffic diagnostics

#ifdef _DEBUG
void CRSViewTraffic::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSViewTraffic::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
