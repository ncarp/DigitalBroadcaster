// RSViewMusicDataPlaying.cpp : implementation file
//

#include "stdafx.h"
#include "RSViewMusicDataPlaying.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSViewMusicDataPlaying

IMPLEMENT_DYNAMIC(CRSViewMusicDataPlaying, CRecordset)

CRSViewMusicDataPlaying::CRSViewMusicDataPlaying(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSViewMusicDataPlaying)
	m_Title = _T("");
	m_Artist = _T("");
	m_Path = _T("");
	m_ArtistID = 0;
	m_Rythm = 0;
	m_Start = 0;
	m_FadeIn = 0;
	m_Intro = 0;
	m_FadeOut = 0;
	m_Mix = 0;
	m_Finish = 0;
	m_LoopA = 0;
	m_LoopB = 0;
	m_ID = 0;
	m_FileType = _T("");
	m_nFields = 15;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	m_strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSViewMusicDataPlaying::GetDefaultConnect()
{
	return m_strConnect;
}

CString CRSViewMusicDataPlaying::GetDefaultSQL()
{
	return _T("[dbo].[ViewMusicData_Playing]");
}

void CRSViewMusicDataPlaying::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSViewMusicDataPlaying)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[Title]"), m_Title);
	RFX_Text(pFX, _T("[Artist]"), m_Artist);
	RFX_Text(pFX, _T("[Path]"), m_Path);
	RFX_Long(pFX, _T("[ArtistID]"), m_ArtistID);
	RFX_Long(pFX, _T("[Rythm]"), m_Rythm);
	RFX_Long(pFX, _T("[Start]"), m_Start);
	RFX_Long(pFX, _T("[FadeIn]"), m_FadeIn);
	RFX_Long(pFX, _T("[Intro]"), m_Intro);
	RFX_Long(pFX, _T("[FadeOut]"), m_FadeOut);
	RFX_Long(pFX, _T("[Mix]"), m_Mix);
	RFX_Long(pFX, _T("[Finish]"), m_Finish);
	RFX_Long(pFX, _T("[LoopA]"), m_LoopA);
	RFX_Long(pFX, _T("[LoopB]"), m_LoopB);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[FileType]"), m_FileType);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSViewMusicDataPlaying diagnostics

#ifdef _DEBUG
void CRSViewMusicDataPlaying::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSViewMusicDataPlaying::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
