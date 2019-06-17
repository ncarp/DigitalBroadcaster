// RSViewMusicFull.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSViewMusicFull.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSViewMusicFull

IMPLEMENT_DYNAMIC(CRSViewMusicFull, CRecordset)

CRSViewMusicFull::CRSViewMusicFull(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSViewMusicFull)
	m_ID = 0;
	m_ArtistID = 0;
	m_Title = _T("");
	m_Lyrics = _T("");
	m_Music = _T("");
	m_Producer = _T("");
	m_Musicians = _T("");
	m_Studio = _T("");
	m_Tecnicians = _T("");
	m_RecordID = 0;
	m_RecordLabelID = 0;
	m_LanguageID = 0;
	m_CategoryID = 0;
	m_Rythm = 0;
	m_Obs = _T("");
	m_Available = 0;
	m_Activ = 0;
	m_Storage = _T("");
	m_PathID = 0;
	m_Start = 0;
	m_FadeIn = 0;
	m_Intro = 0;
	m_FadeOut = 0;
	m_Mix = 0;
	m_Finish = 0;
	m_LoopA = 0;
	m_LoopB = 0;
	m_FileType = _T("");
	m_Artist = _T("");
	m_Record = _T("");
	m_Label = _T("");
	m_Expression = _T("");
	m_Category = _T("");
	m_Path = _T("");
	m_nFields = 35;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSViewMusicFull::GetDefaultConnect()
{
	return strConnect;
}

CString CRSViewMusicFull::GetDefaultSQL()
{
	return _T("[dbo].[ViewMusicFull]");
}

void CRSViewMusicFull::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSViewMusicFull)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Long(pFX, _T("[ArtistID]"), m_ArtistID);
	RFX_Text(pFX, _T("[Title]"), m_Title);
	RFX_Text(pFX, _T("[Lyrics]"), m_Lyrics);
	RFX_Text(pFX, _T("[Music]"), m_Music);
	RFX_Text(pFX, _T("[Producer]"), m_Producer);
	RFX_Text(pFX, _T("[Musicians]"), m_Musicians);
	RFX_Text(pFX, _T("[Studio]"), m_Studio);
	RFX_Text(pFX, _T("[Tecnicians]"), m_Tecnicians);
	RFX_Long(pFX, _T("[RecordID]"), m_RecordID);
	RFX_Long(pFX, _T("[RecordLabelID]"), m_RecordLabelID);
	RFX_Long(pFX, _T("[LanguageID]"), m_LanguageID);
	RFX_Long(pFX, _T("[CategoryID]"), m_CategoryID);
	RFX_Long(pFX, _T("[Rythm]"), m_Rythm);
	RFX_Date(pFX, _T("[Date]"), m_Date);
	RFX_Text(pFX, _T("[Obs]"), m_Obs);
	RFX_Long(pFX, _T("[Available]"), m_Available);
	RFX_Long(pFX, _T("[Activ]"), m_Activ);
	RFX_Text(pFX, _T("[Storage]"), m_Storage);
	RFX_Long(pFX, _T("[PathID]"), m_PathID);
	RFX_Long(pFX, _T("[Start]"), m_Start);
	RFX_Long(pFX, _T("[FadeIn]"), m_FadeIn);
	RFX_Long(pFX, _T("[Intro]"), m_Intro);
	RFX_Long(pFX, _T("[FadeOut]"), m_FadeOut);
	RFX_Long(pFX, _T("[Mix]"), m_Mix);
	RFX_Long(pFX, _T("[Finish]"), m_Finish);
	RFX_Long(pFX, _T("[LoopA]"), m_LoopA);
	RFX_Long(pFX, _T("[LoopB]"), m_LoopB);
	RFX_Text(pFX, _T("[FileType]"), m_FileType);
	RFX_Text(pFX, _T("[Artist]"), m_Artist);
	RFX_Text(pFX, _T("[Record]"), m_Record);
	RFX_Text(pFX, _T("[Label]"), m_Label);
	RFX_Text(pFX, _T("[Expression]"), m_Expression);
	RFX_Text(pFX, _T("[Category]"), m_Category);
	RFX_Text(pFX, _T("[Path]"), m_Path);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSViewMusicFull diagnostics

#ifdef _DEBUG
void CRSViewMusicFull::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSViewMusicFull::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
