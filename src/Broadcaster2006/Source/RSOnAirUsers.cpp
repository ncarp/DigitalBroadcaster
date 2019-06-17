// RSOnAirUsers.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSOnAirUsers.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSOnAirUsers

IMPLEMENT_DYNAMIC(CRSOnAirUsers, CRecordset)

CRSOnAirUsers::CRSOnAirUsers(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSOnAirUsers)
	m_ID = 0;
	m_Name = _T("");
	m_Password = _T("");
	m_StationAccess = _T("");
	m_Activ = 0;
	m_Blocks = 0;
	m_MusicEditing = 0;
	m_Scheduler = 0;
	m_SoundRecorder = 0;
	m_nFields = 9;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSOnAirUsers::GetDefaultConnect()
{
	return strConnect;
}

CString CRSOnAirUsers::GetDefaultSQL()
{
	return _T("[dbo].[OnAirUser]");
}

void CRSOnAirUsers::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSOnAirUsers)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Text(pFX, _T("[Password]"), m_Password);
	RFX_Text(pFX, _T("[StationAccess]"), m_StationAccess);
	RFX_Long(pFX, _T("[Activ]"), m_Activ);
	RFX_Long(pFX, _T("[Blocks]"), m_Blocks);
	RFX_Long(pFX, _T("[MusicEditing]"), m_MusicEditing);
	RFX_Long(pFX, _T("[Scheduler]"), m_Scheduler);
	RFX_Long(pFX, _T("[SoundRecorder]"), m_SoundRecorder);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSOnAirUsers diagnostics

#ifdef _DEBUG
void CRSOnAirUsers::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSOnAirUsers::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
