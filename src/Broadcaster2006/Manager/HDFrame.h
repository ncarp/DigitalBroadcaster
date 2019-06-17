#if !defined(AFX_HDFRAME_H__0287C347_06D1_4532_AAA1_BF4BB2C5D809__INCLUDED_)
#define AFX_HDFRAME_H__0287C347_06D1_4532_AAA1_BF4BB2C5D809__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HDFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHDFrame frame

class CHDFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CHDFrame)
protected:
	CHDFrame();           // protected constructor used by dynamic creation

// Attributes
public:
	CToolBarCtrl	m_wndToolBar;
	CReBar			m_wndReBar;

// Operations
public:
	virtual void OnNew();
	virtual void OnEdit();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHDFrame)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CHDFrame();

	// Generated message map functions
	//{{AFX_MSG(CHDFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HDFRAME_H__0287C347_06D1_4532_AAA1_BF4BB2C5D809__INCLUDED_)
