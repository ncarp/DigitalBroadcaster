#if !defined(AFX_RSVIEWMUSICSCHEDULINGSATA_H__5137EA63_4DC3_4BBD_9A6E_A4C11C2C1272__INCLUDED_)
#define AFX_RSVIEWMUSICSCHEDULINGSATA_H__5137EA63_4DC3_4BBD_9A6E_A4C11C2C1272__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSViewMusicSchedulingSata.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSViewMusicSchedulingSata recordset

class CRSViewMusicSchedulingSata : public CRecordset
{
public:
	CRSViewMusicSchedulingSata(CString str,CDatabase *db=NULL);
	DECLARE_DYNAMIC(CRSViewMusicSchedulingSata)

// Field/Param Data
	//{{AFX_FIELD(CRSViewMusicSchedulingSata, CRecordset)
	COleDateTime m_MaxMusicDate;
	long	m_TrackID;
	CString	m_TrackTitle;
	CString	m_ArtistName;
	long	m_TrackLength;
	long	m_TrackIntroTime;
	long	m_TrackRythm;
	long	m_LanguageID;
	long	m_CategoryID;
	long	m_ArtistID;
	COleDateTime m_MaxArtistDate;
	//}}AFX_FIELD

	CString strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSViewMusicSchedulingSata)
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

#endif // !defined(AFX_RSVIEWMUSICSCHEDULINGSATA_H__5137EA63_4DC3_4BBD_9A6E_A4C11C2C1272__INCLUDED_)
