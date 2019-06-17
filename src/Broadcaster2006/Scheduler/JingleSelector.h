#if !defined(AFX_JINGLESELECTOR_H__52B12E7F_729B_404F_8CF6_148C6D6B30D4__INCLUDED_)
#define AFX_JINGLESELECTOR_H__52B12E7F_729B_404F_8CF6_148C6D6B30D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// JingleSelector.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CJingleSelector dialog

class CJingleSelector : public CDialog
{
// Construction
public:
	CJingleSelector(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CJingleSelector)
	enum { IDD = IDD_JINGLESELECTOR };
	CListCtrl	m_cList;
	//}}AFX_DATA

	CString m_strConnect,
			m_strSQL,
			m_strSort,
			m_strJingleName;
	long	m_JingleID;

	COleDateTime	m_Date;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJingleSelector)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CJingleSelector)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JINGLESELECTOR_H__52B12E7F_729B_404F_8CF6_148C6D6B30D4__INCLUDED_)
