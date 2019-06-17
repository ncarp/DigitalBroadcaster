#if !defined(AFX_ARTIST_H__696D9AC0_9805_4A3D_A0BE_A2656B8E89E1__INCLUDED_)
#define AFX_ARTIST_H__696D9AC0_9805_4A3D_A0BE_A2656B8E89E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Artist.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CArtist dialog

class CArtist : public CDialog
{
// Construction
public:
	CArtist(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CArtist)
	enum { IDD = IDD_ARTIST };
	CComboBox	m_cNationality;
	CComboBox	m_cLabel;
	CString	m_Adress;
	COleDateTime	m_Date;
	CString	m_eMail;
	CString	m_FanClub;
	CString	m_Label;
	CString	m_Name;
	CString	m_Nationality;
	CString	m_Remarks;
	CString	m_WWW;
	//}}AFX_DATA

	long	m_ArtistID,
			m_NationalityID,
			m_LabelID;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CArtist)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CArtist)
	virtual BOOL OnInitDialog();
	afx_msg void OnKillfocusLabel();
	afx_msg void OnSelchangeLabel();
	afx_msg void OnKillfocusNationality();
	afx_msg void OnSelchangeNationality();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARTIST_H__696D9AC0_9805_4A3D_A0BE_A2656B8E89E1__INCLUDED_)
