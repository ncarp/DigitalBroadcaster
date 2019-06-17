#if !defined(AFX_USERFRAME_H__4C9683C7_1BB5_4D39_9717_BCC739737E5B__INCLUDED_)
#define AFX_USERFRAME_H__4C9683C7_1BB5_4D39_9717_BCC739737E5B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UserFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUserFrame frame

class CUserFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CUserFrame)
protected:
	CUserFrame();           // protected constructor used by dynamic creation

// Attributes
public:
	CToolBarCtrl	m_wndToolBar;
	CReBar			m_wndReBar;

// Operations
public:
	void	OnAdd();
	void	OnEdit();
	void	OnCut();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserFrame)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CUserFrame();

	// Generated message map functions
	//{{AFX_MSG(CUserFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERFRAME_H__4C9683C7_1BB5_4D39_9717_BCC739737E5B__INCLUDED_)
