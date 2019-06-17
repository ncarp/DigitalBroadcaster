#if !defined(AFX_NEWSLINEUP_H__1928A7EA_9BDE_4C5A_A682_DBA337F3328B__INCLUDED_)
#define AFX_NEWSLINEUP_H__1928A7EA_9BDE_4C5A_A682_DBA337F3328B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewsLineUp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewsLineUp dialog

class CNewsLineUp : public CDialog
{
// Construction
public:
	CNewsLineUp(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNewsLineUp)
	enum { IDD = IDD_NEWSLINEUP };
	CTreeCtrl	m_cNews;
	CListCtrl	m_cLineUp;
	CString	m_Name;
	//}}AFX_DATA

	long	m_lNewsID[200];
	int		m_nNews;
	long	m_ID;
	CString	m_strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewsLineUp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewsLineUp)
	virtual void OnOK();
	afx_msg void OnRemove();
	afx_msg void OnMoveup();
	afx_msg void OnMovedown();
	afx_msg void OnDblclkNews(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWSLINEUP_H__1928A7EA_9BDE_4C5A_A682_DBA337F3328B__INCLUDED_)
