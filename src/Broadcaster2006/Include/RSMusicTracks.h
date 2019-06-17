#if !defined(AFX_RSMUSICTRACKS_H__9516EF1A_6F87_4422_9EF9_EEB63925776A__INCLUDED_)
#define AFX_RSMUSICTRACKS_H__9516EF1A_6F87_4422_9EF9_EEB63925776A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSMusicTracks.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSMusicTracks recordset

class CRSMusicTracks : public CRecordset
{
public:
	CRSMusicTracks(CString str);
	DECLARE_DYNAMIC(CRSMusicTracks)

// Field/Param Data
	//{{AFX_FIELD(CRSMusicTracks, CRecordset)
	long	m_ID;
	long	m_ArtistID;
	CString	m_Title;
	CString	m_Lyrics;
	CString	m_Music;
	CString	m_Producer;
	CString	m_Musicians;
	CString	m_Studio;
	CString	m_Tecnicians;
	long	m_RecordID;
	long	m_RecordLabelID;
	long	m_LanguageID;
	long	m_CategoryID;
	long	m_Rythm;
	TIMESTAMP_STRUCT	m_Date;
	CString	m_Obs;
	long	m_Available;
	long	m_Activ;
	CString	m_Storage;
	long	m_PathID;
	long	m_Start;
	long	m_FadeIn;
	long	m_Intro;
	long	m_FadeOut;
	long	m_Mix;
	long	m_Finish;
	long	m_LoopA;
	long	m_LoopB;
	CString	m_FileType;
	//}}AFX_FIELD

	CString strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSMusicTracks)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RSMUSICTRACKS_H__9516EF1A_6F87_4422_9EF9_EEB63925776A__INCLUDED_)
