// RSViewArtistFull.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSViewArtistFull.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSViewArtistFull

IMPLEMENT_DYNAMIC(CRSViewArtistFull, CRecordset)

CRSViewArtistFull::CRSViewArtistFull(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSViewArtistFull)
	m_ID = 0;
	m_Name = _T("");
	m_Adress = _T("");
	m_www = _T("");
	m_Activ = 0;
	m_NationalityID = 0;
	m_Obs = _T("");
	m_eMail = _T("");
	m_DRM35 = _T("");
	m_FanClub = _T("");
	m_RecordLabelID = 0;
	m_Nationality = _T("");
	m_Label = _T("");
	m_nFields = 15;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSViewArtistFull::GetDefaultConnect()
{
	return _T("ODBC;DSN=Broadcaster");
}

CString CRSViewArtistFull::GetDefaultSQL()
{
	return _T("[dbo].[ViewArtistFull]");
}

void CRSViewArtistFull::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSViewArtistFull)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Text(pFX, _T("[Adress]"), m_Adress);
	RFX_Text(pFX, _T("[www]"), m_www);
	RFX_Long(pFX, _T("[Activ]"), m_Activ);
	RFX_Long(pFX, _T("[NationalityID]"), m_NationalityID);
	RFX_Text(pFX, _T("[Obs]"), m_Obs);
	RFX_Text(pFX, _T("[eMail]"), m_eMail);
	RFX_LongBinary(pFX, _T("[Photo]"), m_Photo);
	RFX_Text(pFX, _T("[DRM35]"), m_DRM35);
	RFX_Text(pFX, _T("[FanClub]"), m_FanClub);
	RFX_Date(pFX, _T("[Birthdate]"), m_Birthdate);
	RFX_Long(pFX, _T("[RecordLabelID]"), m_RecordLabelID);
	RFX_Text(pFX, _T("[Nationality]"), m_Nationality);
	RFX_Text(pFX, _T("[Label]"), m_Label);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSViewArtistFull diagnostics

#ifdef _DEBUG
void CRSViewArtistFull::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSViewArtistFull::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
