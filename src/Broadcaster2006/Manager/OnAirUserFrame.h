#if !defined(AFX_ONAIRUSERFRAME_H__1157154B_D48B_4B2E_AF6F_A8E167355423__INCLUDED_)
#define AFX_ONAIRUSERFRAME_H__1157154B_D48B_4B2E_AF6F_A8E167355423__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OnAirUserFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COnAirUserFrame frame

class COnAirUserFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(COnAirUserFrame)
protected:
	COnAirUserFrame();           // protected constructor used by dynamic creation

// Attributes
public:
	CSplitterWnd	m_wndSplitter;
	CToolBarCtrl	m_wndToolBar;
	CReBar			m_wndReBar;
// Operations
public:
	void OnNew();
	void OnEdit();
	void OnCut();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COnAirUserFrame)
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~COnAirUserFrame();

	// Generated message map functions
	//{{AFX_MSG(COnAirUserFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ONAIRUSERFRAME_H__1157154B_D48B_4B2E_AF6F_A8E167355423__INCLUDED_)
