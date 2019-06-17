#if !defined(AFX_JINGLESFRAME_H__DE890D7E_B976_4CA6_A3D4_6A05CEB77F03__INCLUDED_)
#define AFX_JINGLESFRAME_H__DE890D7E_B976_4CA6_A3D4_6A05CEB77F03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// JinglesFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CJinglesFrame frame

class CJinglesFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CJinglesFrame)
protected:
	CJinglesFrame();           // protected constructor used by dynamic creation

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
	//{{AFX_VIRTUAL(CJinglesFrame)
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CJinglesFrame();

	// Generated message map functions
	//{{AFX_MSG(CJinglesFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JINGLESFRAME_H__DE890D7E_B976_4CA6_A3D4_6A05CEB77F03__INCLUDED_)
