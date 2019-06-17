// RSViewBlocksStatusOnSpots.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSViewBlocksStatusOnSpots.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSViewBlocksStatusOnSpots

IMPLEMENT_DYNAMIC(CRSViewBlocksStatusOnSpots, CRecordset)

CRSViewBlocksStatusOnSpots::CRSViewBlocksStatusOnSpots(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSViewBlocksStatusOnSpots)
	m_BlockID = 0;
	m_nSpots = 0;
	m_SpotsLength = 0;
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	m_strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSViewBlocksStatusOnSpots::GetDefaultConnect()
{
	return m_strConnect;
}

CString CRSViewBlocksStatusOnSpots::GetDefaultSQL()
{
	return _T("[dbo].[ViewBlockStatus-nSpots]");
}

void CRSViewBlocksStatusOnSpots::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSViewBlocksStatusOnSpots)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[BlockID]"), m_BlockID);
	RFX_Date(pFX, _T("[BlockDate]"), m_BlockDate);
	RFX_Long(pFX, _T("[nSpots]"), m_nSpots);
	RFX_Long(pFX, _T("[SpotsLength]"), m_SpotsLength);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSViewBlocksStatusOnSpots diagnostics

#ifdef _DEBUG
void CRSViewBlocksStatusOnSpots::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSViewBlocksStatusOnSpots::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
