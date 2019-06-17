#if !defined(AFX_MUSICSELECTOR_H__9ECB99D4_533F_44EA_94A9_7C78599D1E41__INCLUDED_)
#define AFX_MUSICSELECTOR_H__9ECB99D4_533F_44EA_94A9_7C78599D1E41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MusicSelector.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMusicSelector dialog

class CMusicSelector : public CDialog
{
// Construction
public:
	CMusicSelector(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMusicSelector)
	enum { IDD = IDD_SELECTOR };
	CListCtrl	m_cList;
	//}}AFX_DATA

	CString m_strConnect,
			m_strSQL,
			m_strSort,
			m_strSongName;
	long	m_MusicID;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMusicSelector)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMusicSelector)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MUSICSELECTOR_H__9ECB99D4_533F_44EA_94A9_7C78599D1E41__INCLUDED_)
