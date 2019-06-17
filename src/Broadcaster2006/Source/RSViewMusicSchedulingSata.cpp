// RSViewMusicSchedulingSata.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSViewMusicSchedulingSata.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSViewMusicSchedulingSata

IMPLEMENT_DYNAMIC(CRSViewMusicSchedulingSata, CRecordset)

CRSViewMusicSchedulingSata::CRSViewMusicSchedulingSata(CString str,CDatabase *pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRSViewMusicSchedulingSata)
	m_TrackID = 0;
	m_TrackTitle = _T("");
	m_ArtistName = _T("");
	m_TrackLength = 0;
	m_TrackIntroTime = 0;
	m_TrackRythm = 0;
	m_LanguageID = 0;
	m_CategoryID = 0;
	m_ArtistID = 0;
	m_nFields = 11;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSViewMusicSchedulingSata::GetDefaultConnect()
{
	return strConnect;
}

CString CRSViewMusicSchedulingSata::GetDefaultSQL()
{
	return _T("[dbo].[ViewMusicSchedulingData]");
}

void CRSViewMusicSchedulingSata::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSViewMusicSchedulingSata)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Date(pFX, _T("[MaxMusicDate]"), m_MaxMusicDate);
	RFX_Long(pFX, _T("[TrackID]"), m_TrackID);
	RFX_Text(pFX, _T("[TrackTitle]"), m_TrackTitle);
	RFX_Text(pFX, _T("[ArtistName]"), m_ArtistName);
	RFX_Long(pFX, _T("[TrackLength]"), m_TrackLength);
	RFX_Long(pFX, _T("[TrackIntroTime]"), m_TrackIntroTime);
	RFX_Long(pFX, _T("[TrackRythm]"), m_TrackRythm);
	RFX_Long(pFX, _T("[LanguageID]"), m_LanguageID);
	RFX_Long(pFX, _T("[CategoryID]"), m_CategoryID);
	RFX_Long(pFX, _T("[ArtistID]"), m_ArtistID);
	RFX_Date(pFX, _T("[MaxArtistDate]"), m_MaxArtistDate);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSViewMusicSchedulingSata diagnostics

#ifdef _DEBUG
void CRSViewMusicSchedulingSata::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSViewMusicSchedulingSata::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
