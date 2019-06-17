#if !defined(AFX_RSVIEWARTISTFULL_H__BEF770D9_1B89_43D1_B475_7A8B692A9AAE__INCLUDED_)
#define AFX_RSVIEWARTISTFULL_H__BEF770D9_1B89_43D1_B475_7A8B692A9AAE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSViewArtistFull.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSViewArtistFull recordset

class CRSViewArtistFull : public CRecordset
{
public:
	CRSViewArtistFull(CString str);
	DECLARE_DYNAMIC(CRSViewArtistFull)

// Field/Param Data
	//{{AFX_FIELD(CRSViewArtistFull, CRecordset)
	long	m_ID;
	CString	m_Name;
	CString	m_Adress;
	CString	m_www;
	long	m_Activ;
	long	m_NationalityID;
	CString	m_Obs;
	CString	m_eMail;
	CLongBinary	m_Photo;
	CString	m_DRM35;
	CString	m_FanClub;
	COleDateTime m_Birthdate;
	long	m_RecordLabelID;
	CString	m_Nationality;
	CString	m_Label;
	//}}AFX_FIELD

	CString strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSViewArtistFull)
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

#endif // !defined(AFX_RSVIEWARTISTFULL_H__BEF770D9_1B89_43D1_B475_7A8B692A9AAE__INCLUDED_)
