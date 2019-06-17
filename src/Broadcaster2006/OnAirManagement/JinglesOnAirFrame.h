#if !defined(AFX_JINGLESONAIRFRAME_H__17F4D62C_9927_453E_A149_888E9A65EE87__INCLUDED_)
#define AFX_JINGLESONAIRFRAME_H__17F4D62C_9927_453E_A149_888E9A65EE87__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// JinglesOnAirFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CJinglesOnAirFrame frame

class CJinglesOnAirFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CJinglesOnAirFrame)
protected:
	CJinglesOnAirFrame();           // protected constructor used by dynamic creation

// Attributes
public:
	CSplitterWnd	m_wndSplitter;
	CToolBarCtrl	m_wndToolBar;
	CReBar			m_wndReBar;
// Operations
public:
	void	OnCut();
	void	OnEdit();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJinglesOnAirFrame)
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CJinglesOnAirFrame();

	// Generated message map functions
	//{{AFX_MSG(CJinglesOnAirFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JINGLESONAIRFRAME_H__17F4D62C_9927_453E_A149_888E9A65EE87__INCLUDED_)
