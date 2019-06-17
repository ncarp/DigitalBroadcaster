#if !defined(AFX_LOGONBACK_H__A3663BAC_09A8_444D_B3BB_1BDF3393B223__INCLUDED_)
#define AFX_LOGONBACK_H__A3663BAC_09A8_444D_B3BB_1BDF3393B223__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LogOnBack.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLogOnBack frame

class CLogOnBack : public CFrameWnd
{
	DECLARE_DYNCREATE(CLogOnBack)
public:
	CLogOnBack();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLogOnBack)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CLogOnBack();

	// Generated message map functions
	//{{AFX_MSG(CLogOnBack)
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGONBACK_H__A3663BAC_09A8_444D_B3BB_1BDF3393B223__INCLUDED_)
