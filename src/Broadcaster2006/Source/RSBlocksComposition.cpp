// RSBlocksComposition.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSBlocksComposition.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSBlocksComposition

IMPLEMENT_DYNAMIC(CRSBlocksComposition, CRecordset)

CRSBlocksComposition::CRSBlocksComposition(CString str,CDatabase *pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRSBlocksComposition)
	m_ID = 0;
	m_Position = 0;
	m_ItemType = 0;
	m_ItemID = 0;
	m_Sun = 0;
	m_Mon = 0;
	m_Tue = 0;
	m_Wed = 0;
	m_Thu = 0;
	m_Fri = 0;
	m_Sat = 0;
	m_nFields = 13;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSBlocksComposition::GetDefaultConnect()
{
	return strConnect;
}

CString CRSBlocksComposition::GetDefaultSQL()
{
	return _T("[dbo].[BlocksComposition]");
}

void CRSBlocksComposition::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSBlocksComposition)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Long(pFX, _T("[Position]"), m_Position);
	RFX_Long(pFX, _T("[ItemType]"), m_ItemType);
	RFX_Long(pFX, _T("[ItemID]"), m_ItemID);
	RFX_Date(pFX, _T("[StartingDate]"), m_StartingDate);
	RFX_Date(pFX, _T("[EndingDate]"), m_EndingDate);
	RFX_Long(pFX, _T("[Sun]"), m_Sun);
	RFX_Long(pFX, _T("[Mon]"), m_Mon);
	RFX_Long(pFX, _T("[Tue]"), m_Tue);
	RFX_Long(pFX, _T("[Wed]"), m_Wed);
	RFX_Long(pFX, _T("[Thu]"), m_Thu);
	RFX_Long(pFX, _T("[Fri]"), m_Fri);
	RFX_Long(pFX, _T("[Sat]"), m_Sat);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSBlocksComposition diagnostics

#ifdef _DEBUG
void CRSBlocksComposition::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSBlocksComposition::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
 