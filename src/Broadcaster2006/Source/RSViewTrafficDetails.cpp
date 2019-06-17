// RSViewTrafficDetails.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSViewTrafficDetails.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSViewTrafficDetails

IMPLEMENT_DYNAMIC(CRSViewTrafficDetails, CRecordset)

CRSViewTrafficDetails::CRSViewTrafficDetails(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSViewTrafficDetails)
	m_ID = 0;
	m_BlockID = 0;
	m_BlockName = _T("");
	m_BlockTime = 0;
	m_SpotID = 0;
	m_SpotName = _T("");
	m_TypeOfBusinessID = 0;
	m_SpotLength = 0;
	m_Position = 0;
	m_Aired = 0;
	m_Business = _T("");
	m_CustomerName = _T("");
	m_ScheduleID = 0;
	m_nFields = 14;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	m_strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSViewTrafficDetails::GetDefaultConnect()
{
	return m_strConnect;
}

CString CRSViewTrafficDetails::GetDefaultSQL()
{
	return _T("[dbo].[ViewTrafficDetails]");
}

void CRSViewTrafficDetails::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSViewTrafficDetails)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Long(pFX, _T("[BlockID]"), m_BlockID);
	RFX_Text(pFX, _T("[BlockName]"), m_BlockName);
	RFX_Long(pFX, _T("[BlockTime]"), m_BlockTime);
	RFX_Date(pFX, _T("[BlockDate]"), m_BlockDate);
	RFX_Long(pFX, _T("[SpotID]"), m_SpotID);
	RFX_Text(pFX, _T("[SpotName]"), m_SpotName);
	RFX_Long(pFX, _T("[TypeOfBusinessID]"), m_TypeOfBusinessID);
	RFX_Long(pFX, _T("[SpotLength]"), m_SpotLength);
	RFX_Long(pFX, _T("[Position]"), m_Position);
	RFX_Long(pFX, _T("[Aired]"), m_Aired);
	RFX_Text(pFX, _T("[Business]"), m_Business);
	RFX_Text(pFX, _T("[CustomerName]"), m_CustomerName);
	RFX_Long(pFX, _T("[ScheduleID]"), m_ScheduleID);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSViewTrafficDetails diagnostics

#ifdef _DEBUG
void CRSViewTrafficDetails::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSViewTrafficDetails::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
