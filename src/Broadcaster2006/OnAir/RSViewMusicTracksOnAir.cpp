// RSViewMusicTracksOnAir.cpp : implementation file
//

#include "stdafx.h"
#include "RSViewMusicTracksOnAir.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSViewMusicTracksOnAir

IMPLEMENT_DYNAMIC(CRSViewMusicTracksOnAir, CRecordset)

CRSViewMusicTracksOnAir::CRSViewMusicTracksOnAir(CString str,CDatabase *pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRSViewMusicTracksOnAir)
	m_TrackID = 0;
	m_TrackTitle = _T("");
	m_ArtistName = _T("");
	m_TrackLength = 0;
	m_TrackIntroTime = 0;
	m_TrackRythm = 0;
	m_ArtistID = 0;
	m_CategoryID = 0;
	m_LanguageID = 0;
	m_nFields = 9;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSViewMusicTracksOnAir::GetDefaultConnect()
{
	return strConnect;
}

CString CRSViewMusicTracksOnAir::GetDefaultSQL()
{
	return _T("[dbo].[ViewMusicTracks_OnAir]");
}

void CRSViewMusicTracksOnAir::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSViewMusicTracksOnAir)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[TrackID]"), m_TrackID);
	RFX_Text(pFX, _T("[TrackTitle]"), m_TrackTitle);
	RFX_Text(pFX, _T("[ArtistName]"), m_ArtistName);
	RFX_Long(pFX, _T("[TrackLength]"), m_TrackLength);
	RFX_Long(pFX, _T("[TrackIntroTime]"), m_TrackIntroTime);
	RFX_Long(pFX, _T("[TrackRythm]"), m_TrackRythm);
	RFX_Long(pFX, _T("[ArtistID]"), m_ArtistID);
	RFX_Long(pFX, _T("[CategoryID]"), m_CategoryID);
	RFX_Long(pFX, _T("[LanguageID]"), m_LanguageID);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSViewMusicTracksOnAir diagnostics

#ifdef _DEBUG
void CRSViewMusicTracksOnAir::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSViewMusicTracksOnAir::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
