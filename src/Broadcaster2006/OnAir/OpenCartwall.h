#if !defined(AFX_OPENCARTWALL_H__96996CF8_9CE7_43FF_B98E_185E5C8EF7EE__INCLUDED_)
#define AFX_OPENCARTWALL_H__96996CF8_9CE7_43FF_B98E_185E5C8EF7EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OpenCartwall.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COpenCartwall dialog

class COpenCartwall : public CDialog
{
// Construction
public:
	COpenCartwall(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COpenCartwall)
	enum { IDD = IDD_OPENCARTWALL };
	CListBox	m_cList;
	BOOL	m_Info;
	int		m_Cart;
	//}}AFX_DATA

	CString m_strCartName;
	long m_CartID;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COpenCartwall)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COpenCartwall)
	afx_msg void OnDblclkList1();
	virtual void OnOK();
	afx_msg void OnInfo();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPENCARTWALL_H__96996CF8_9CE7_43FF_B98E_185E5C8EF7EE__INCLUDED_)
