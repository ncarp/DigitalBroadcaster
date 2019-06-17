#if !defined(AFX_RSVIEWMUSICTRACKSONAIR_H__30FD9204_05AE_48D8_BF94_C0EF5F337517__INCLUDED_)
#define AFX_RSVIEWMUSICTRACKSONAIR_H__30FD9204_05AE_48D8_BF94_C0EF5F337517__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSViewMusicTracksOnAir.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSViewMusicTracksOnAir recordset

class CRSViewMusicTracksOnAir : public CRecordset
{
public:
	CRSViewMusicTracksOnAir(CString str="",CDatabase *pdb=NULL);
	DECLARE_DYNAMIC(CRSViewMusicTracksOnAir)

// Field/Param Data
	//{{AFX_FIELD(CRSViewMusicTracksOnAir, CRecordset)
	long	m_TrackID;
	CString	m_TrackTitle;
	CString	m_ArtistName;
	long	m_TrackLength;
	long	m_TrackIntroTime;
	long	m_TrackRythm;
	long	m_ArtistID;
	long	m_CategoryID;
	long	m_LanguageID;
	//}}AFX_FIELD

	CString	strConnect;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSViewMusicTracksOnAir)
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

#endif // !defined(AFX_RSVIEWMUSICTRACKSONAIR_H__30FD9204_05AE_48D8_BF94_C0EF5F337517__INCLUDED_)
