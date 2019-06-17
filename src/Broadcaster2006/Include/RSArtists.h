#if !defined(AFX_RSARTISTS_H__60BD019F_2EAF_45FB_8D56_398C25F0B5E6__INCLUDED_)
#define AFX_RSARTISTS_H__60BD019F_2EAF_45FB_8D56_398C25F0B5E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSArtists.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSArtists recordset

class CRSArtists : public CRecordset
{
public:
	CRSArtists(CString str,CDatabase *db);
	DECLARE_DYNAMIC(CRSArtists)

// Field/Param Data
	//{{AFX_FIELD(CRSArtists, CRecordset)
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
	TIMESTAMP_STRUCT	m_Birthdate;
	long	m_RecordLabelID;
	//}}AFX_FIELD

	CString m_strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSArtists)
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

#endif // !defined(AFX_RSARTISTS_H__60BD019F_2EAF_45FB_8D56_398C25F0B5E6__INCLUDED_)
