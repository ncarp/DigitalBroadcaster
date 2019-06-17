#if !defined(AFX_RSVIEWMUSICFULL_H__E94B1DCD_29C6_4B8F_AC7C_2341EE524260__INCLUDED_)
#define AFX_RSVIEWMUSICFULL_H__E94B1DCD_29C6_4B8F_AC7C_2341EE524260__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSViewMusicFull.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSViewMusicFull recordset

class CRSViewMusicFull : public CRecordset
{
public:
	CRSViewMusicFull(CString str);
	DECLARE_DYNAMIC(CRSViewMusicFull)

// Field/Param Data
	//{{AFX_FIELD(CRSViewMusicFull, CRecordset)
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
	COleDateTime	m_Date;
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
	CString	m_Artist;
	CString	m_Record;
	CString	m_Label;
	CString	m_Expression;
	CString	m_Category;
	CString	m_Path;
	//}}AFX_FIELD

	CString strConnect;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSViewMusicFull)
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

#endif // !defined(AFX_RSVIEWMUSICFULL_H__E94B1DCD_29C6_4B8F_AC7C_2341EE524260__INCLUDED_)
