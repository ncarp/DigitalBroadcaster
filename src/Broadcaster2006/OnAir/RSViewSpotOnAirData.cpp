// RSViewSpotOnAirData.cpp : implementation file
//

#include "stdafx.h"
#include "RSViewSpotOnAirData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSViewSpotOnAirData

IMPLEMENT_DYNAMIC(CRSViewSpotOnAirData, CRecordset)

CRSViewSpotOnAirData::CRSViewSpotOnAirData(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSViewSpotOnAirData)
	m_CustomerID = 0;
	m_SpotID = 0;
	m_Path = _T("");
	m_CustomerName = _T("");
	m_Name = _T("");
	m_FileName = _T("");
	m_Start = 0;
	m_Mix = 0;
	m_Finish = 0;
	m_MainVoiceID = 0;
	m_TypeOfBusinessID = 0;
	m_nFields = 11;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	m_strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSViewSpotOnAirData::GetDefaultConnect()
{
	return m_strConnect;
}

CString CRSViewSpotOnAirData::GetDefaultSQL()
{
	return _T("[dbo].[ViewSpotOnAirData]");
}

void CRSViewSpotOnAirData::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSViewSpotOnAirData)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[CustomerID]"), m_CustomerID);
	RFX_Long(pFX, _T("[SpotID]"), m_SpotID);
	RFX_Text(pFX, _T("[Path]"), m_Path);
	RFX_Text(pFX, _T("[CustomerName]"), m_CustomerName);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Text(pFX, _T("[FileName]"), m_FileName);
	RFX_Long(pFX, _T("[Start]"), m_Start);
	RFX_Long(pFX, _T("[Mix]"), m_Mix);
	RFX_Long(pFX, _T("[Finish]"), m_Finish);
	RFX_Long(pFX, _T("[MainVoiceID]"), m_MainVoiceID);
	RFX_Long(pFX, _T("[TypeOfBusinessID]"), m_TypeOfBusinessID);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSViewSpotOnAirData diagnostics

#ifdef _DEBUG
void CRSViewSpotOnAirData::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSViewSpotOnAirData::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
