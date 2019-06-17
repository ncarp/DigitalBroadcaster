#if !defined(AFX_SCHEDULEFRAME_H__D0FB9F5A_6E6C_4B8A_83E9_C61FAC31B8A9__INCLUDED_)
#define AFX_SCHEDULEFRAME_H__D0FB9F5A_6E6C_4B8A_83E9_C61FAC31B8A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScheduleFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CScheduleFrame frame

class CScheduleFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CScheduleFrame)
protected:
	CScheduleFrame();           // protected constructor used by dynamic creation

// Attributes
public:
	CSplitterWnd	m_wndSplitter;
	CToolBarCtrl	m_wndToolBar;
	CReBar			m_wndReBar;
// Operations
public:
	virtual	void	OnPFL();
	virtual void	OnLock();
	virtual void	OnCut();
	virtual void	OnEdit();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScheduleFrame)
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CScheduleFrame();

	// Generated message map functions
	//{{AFX_MSG(CScheduleFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCHEDULEFRAME_H__D0FB9F5A_6E6C_4B8A_83E9_C61FAC31B8A9__INCLUDED_)
