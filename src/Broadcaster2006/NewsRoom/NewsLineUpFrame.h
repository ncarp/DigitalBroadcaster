#if !defined(AFX_NEWSLINEUPFRAME_H__2CB13DB7_3C80_464B_B534_60CDBB70B114__INCLUDED_)
#define AFX_NEWSLINEUPFRAME_H__2CB13DB7_3C80_464B_B534_60CDBB70B114__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewsLineUpFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewsLineUpFrame frame

class CNewsLineUpFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CNewsLineUpFrame)
protected:
	CNewsLineUpFrame();           // protected constructor used by dynamic creation

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
	//{{AFX_VIRTUAL(CNewsLineUpFrame)
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CNewsLineUpFrame();

	// Generated message map functions
	//{{AFX_MSG(CNewsLineUpFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWSLINEUPFRAME_H__2CB13DB7_3C80_464B_B534_60CDBB70B114__INCLUDED_)
