#if !defined(AFX_TEXTMANAGEMENTFRAME_H__3DAED886_628A_4ECF_B880_B6F193953A6E__INCLUDED_)
#define AFX_TEXTMANAGEMENTFRAME_H__3DAED886_628A_4ECF_B880_B6F193953A6E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TextManagementFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTextManagementFrame frame

class CTextManagementFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CTextManagementFrame)
protected:
	CTextManagementFrame();           // protected constructor used by dynamic creation

// Attributes
public:
	CSplitterWnd	m_wndSplitter;
	CToolBarCtrl	m_wndToolBar;
	CReBar			m_wndReBar;

// Operations
public:
	void	OnNew();
	void	OnEdit();
	void	OnCut();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTextManagementFrame)
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CTextManagementFrame();

	// Generated message map functions
	//{{AFX_MSG(CTextManagementFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEXTMANAGEMENTFRAME_H__3DAED886_628A_4ECF_B880_B6F193953A6E__INCLUDED_)
