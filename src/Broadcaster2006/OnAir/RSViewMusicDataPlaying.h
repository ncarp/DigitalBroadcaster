#if !defined(AFX_RSVIEWMUSICDATAPLAYING_H__C7560C92_DB21_4785_93E6_001D7A190804__INCLUDED_)
#define AFX_RSVIEWMUSICDATAPLAYING_H__C7560C92_DB21_4785_93E6_001D7A190804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSViewMusicDataPlaying.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSViewMusicDataPlaying recordset

class CRSViewMusicDataPlaying : public CRecordset
{
public:
	CRSViewMusicDataPlaying(CString str);
	DECLARE_DYNAMIC(CRSViewMusicDataPlaying)

// Field/Param Data
	//{{AFX_FIELD(CRSViewMusicDataPlaying, CRecordset)
	CString	m_Title;
	CString	m_Artist;
	CString	m_Path;
	long	m_ArtistID;
	long	m_Rythm;
	long	m_Start;
	long	m_FadeIn;
	long	m_Intro;
	long	m_FadeOut;
	long	m_Mix;
	long	m_Finish;
	long	m_LoopA;
	long	m_LoopB;
	long	m_ID;
	CString	m_FileType;
	//}}AFX_FIELD

	CString	m_strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSViewMusicDataPlaying)
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

#endif // !defined(AFX_RSVIEWMUSICDATAPLAYING_H__C7560C92_DB21_4785_93E6_001D7A190804__INCLUDED_)
