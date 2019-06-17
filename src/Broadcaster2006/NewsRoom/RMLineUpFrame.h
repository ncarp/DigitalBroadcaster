#if !defined(AFX_RMLINEUPFRAME_H__B08D1903_FF5E_4D4F_9414_8C1D1C8F4BD2__INCLUDED_)
#define AFX_RMLINEUPFRAME_H__B08D1903_FF5E_4D4F_9414_8C1D1C8F4BD2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RMLineUpFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRMLineUpFrame frame

class CRMLineUpFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CRMLineUpFrame)
protected:
	CRMLineUpFrame();           // protected constructor used by dynamic creation

// Attributes
public:
	CSplitterWnd	m_wndSplitter;
	CToolBarCtrl	m_wndToolBar;
	CReBar			m_wndReBar;

// Operations
public:
	void	OnNew();
	void	OnCut();
	void	OnEdit();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRMLineUpFrame)
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CRMLineUpFrame();

	// Generated message map functions
	//{{AFX_MSG(CRMLineUpFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RMLINEUPFRAME_H__B08D1903_FF5E_4D4F_9414_8C1D1C8F4BD2__INCLUDED_)
