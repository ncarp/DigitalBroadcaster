#if !defined(AFX_NEWSTEXT_H__26F57D2F_0F32_4E00_9FC3_2D5D9B33A6FE__INCLUDED_)
#define AFX_NEWSTEXT_H__26F57D2F_0F32_4E00_9FC3_2D5D9B33A6FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewsText.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewsText dialog

class CNewsText : public CDialog
{
// Construction
public:
	CNewsText(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNewsText)
	enum { IDD = IDD_TEXT };
	CComboBox	m_cType;
	COleDateTime	m_Date;
	CString	m_KeyWords;
	CString	m_Name;
	CString	m_Text;
	CString	m_Type;
	//}}AFX_DATA
	
	long m_TypeID;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewsText)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewsText)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnKillfocusTexttype();
	afx_msg void OnSelchangeTexttype();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWSTEXT_H__26F57D2F_0F32_4E00_9FC3_2D5D9B33A6FE__INCLUDED_)
