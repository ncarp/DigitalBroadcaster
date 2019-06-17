// RSOnAirLog.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSOnAirLog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSOnAirLog

IMPLEMENT_DYNAMIC(CRSOnAirLog, CRecordset)

CRSOnAirLog::CRSOnAirLog(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSOnAirLog)
	m_ComputerID = 0;
	m_UserID = 0;
	m_ItemType = 0;
	m_ItemID = 0;
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSOnAirLog::GetDefaultConnect()
{
	return strConnect;
}

CString CRSOnAirLog::GetDefaultSQL()
{
	return _T("[dbo].[OnAirLog]");
}

void CRSOnAirLog::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSOnAirLog)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Date(pFX, _T("[Date]"), m_Date);
	RFX_Long(pFX, _T("[ComputerID]"), m_ComputerID);
	RFX_Long(pFX, _T("[UserID]"), m_UserID);
	RFX_Long(pFX, _T("[ItemType]"), m_ItemType);
	RFX_Long(pFX, _T("[ItemID]"), m_ItemID);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSOnAirLog diagnostics

#ifdef _DEBUG
void CRSOnAirLog::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSOnAirLog::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
