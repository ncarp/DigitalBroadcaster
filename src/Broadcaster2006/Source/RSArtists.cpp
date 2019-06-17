// RSArtists.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSArtists.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSArtists

IMPLEMENT_DYNAMIC(CRSArtists, CRecordset)

CRSArtists::CRSArtists(CString str,CDatabase *db=NULL)
	: CRecordset(db)
{
	//{{AFX_FIELD_INIT(CRSArtists)
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
	m_nFields = 13;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	m_strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSArtists::GetDefaultConnect()
{
	return m_strConnect;
}

CString CRSArtists::GetDefaultSQL()
{
	return _T("[dbo].[Artists]");
}

void CRSArtists::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSArtists)
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
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSArtists diagnostics

#ifdef _DEBUG
void CRSArtists::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSArtists::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
