#if !defined(AFX_RSVIEWDISCOGRAPHY_H__FB695F54_0609_43C2_AD95_1AAC16F199D5__INCLUDED_)
#define AFX_RSVIEWDISCOGRAPHY_H__FB695F54_0609_43C2_AD95_1AAC16F199D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSViewDiscography.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSViewDiscography recordset

class CRSViewDiscography : public CRecordset
{
public:
	CRSViewDiscography(CString str);
	DECLARE_DYNAMIC(CRSViewDiscography)

// Field/Param Data
	//{{AFX_FIELD(CRSViewDiscography, CRecordset)
	long	m_ID;
	long	m_ArtistID;
	CString	m_Title;
	CString	m_Artist;
	//}}AFX_FIELD

	CString strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSViewDiscography)
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

#endif // !defined(AFX_RSVIEWDISCOGRAPHY_H__FB695F54_0609_43C2_AD95_1AAC16F199D5__INCLUDED_)
