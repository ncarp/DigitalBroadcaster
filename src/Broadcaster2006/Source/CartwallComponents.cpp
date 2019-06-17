// CartwallComponents.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\CartwallComponents.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCartwallComponents

IMPLEMENT_DYNAMIC(CCartwallComponents, CRecordset)

CCartwallComponents::CCartwallComponents(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CCartwallComponents)
	m_CartwallID = 0;
	m_Position = 0;
	m_Type = 0;
	m_ElementID = 0;
	m_AutoFade = 0;
	m_Loop = 0;
	m_nFields = 6;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CCartwallComponents::GetDefaultConnect()
{
	return strConnect;
}

CString CCartwallComponents::GetDefaultSQL()
{
	return _T("[dbo].[CartwallContents]");
}

void CCartwallComponents::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CCartwallComponents)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[CartwallID]"), m_CartwallID);
	RFX_Long(pFX, _T("[Position]"), m_Position);
	RFX_Long(pFX, _T("[Type]"), m_Type);
	RFX_Long(pFX, _T("[ElementID]"), m_ElementID);
	RFX_Long(pFX, _T("[AutoFade]"), m_AutoFade);
	RFX_Long(pFX, _T("[Loop]"), m_Loop);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CCartwallComponents diagnostics

#ifdef _DEBUG
void CCartwallComponents::AssertValid() const
{
	CRecordset::AssertValid();
}

void CCartwallComponents::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
