// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__DCF8C913_AE91_45E6_A3A8_2BAA4C2EFA0F__INCLUDED_)
#define AFX_MAINFRM_H__DCF8C913_AE91_45E6_A3A8_2BAA4C2EFA0F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:

// Overides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnRmsManagement();
	afx_msg void OnRmslineup();
	afx_msg void OnRmsonair();
	afx_msg void OnTextManagement();
	afx_msg void OnTextOnAir();
	afx_msg void OnNewslineup();
	afx_msg void OnViewHorizontal();
	afx_msg void OnViewVertical();
	afx_msg void OnHelpHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__DCF8C913_AE91_45E6_A3A8_2BAA4C2EFA0F__INCLUDED_)
