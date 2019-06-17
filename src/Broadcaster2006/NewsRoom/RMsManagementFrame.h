#if !defined(AFX_RMSMANAGEMENTFRAME_H__108DFA59_9E1E_4C6E_BE50_1F20E527EC80__INCLUDED_)
#define AFX_RMSMANAGEMENTFRAME_H__108DFA59_9E1E_4C6E_BE50_1F20E527EC80__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RMsManagementFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRMsManagementFrame frame

class CRMsManagementFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CRMsManagementFrame)
protected:
	CRMsManagementFrame();           // protected constructor used by dynamic creation

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
	void	OnPFL();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRMsManagementFrame)
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CRMsManagementFrame();

	// Generated message map functions
	//{{AFX_MSG(CRMsManagementFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RMSMANAGEMENTFRAME_H__108DFA59_9E1E_4C6E_BE50_1F20E527EC80__INCLUDED_)
