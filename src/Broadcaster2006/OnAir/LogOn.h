#if !defined(AFX_LOGON_H__BAFEBA47_85B1_4FF6_B54C_7149CBDCAC95__INCLUDED_)
#define AFX_LOGON_H__BAFEBA47_85B1_4FF6_B54C_7149CBDCAC95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LogOn.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLogOn frame

class CLogOn : public CFrameWnd
{
	DECLARE_DYNCREATE(CLogOn)
public:
	CLogOn();           // protected constructor used by dynamic creation

// Attributes
public:
	CComboBox*	m_pUser;
	CEdit*		m_pPass;
	CButton*	m_pOK;
// Operations

public:
	void OnUserSelChange();
	void OnOK();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLogOn)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CLogOn();

	// Generated message map functions
	//{{AFX_MSG(CLogOn)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGON_H__BAFEBA47_85B1_4FF6_B54C_7149CBDCAC95__INCLUDED_)
