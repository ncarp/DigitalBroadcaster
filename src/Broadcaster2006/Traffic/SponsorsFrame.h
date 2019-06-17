#if !defined(AFX_SPONSORSFRAME_H__D86476F7_2FF3_4441_B16A_AD1C3094DE78__INCLUDED_)
#define AFX_SPONSORSFRAME_H__D86476F7_2FF3_4441_B16A_AD1C3094DE78__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SponsorsFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSponsorsFrame frame

class CSponsorsFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CSponsorsFrame)
protected:
	CSponsorsFrame();           // protected constructor used by dynamic creation

// Attributes
public:
	CSplitterWnd	m_wndSplitter;
	CToolBarCtrl	m_wndToolBar;
	CReBar			m_wndReBar;

// Operations
public:
	void			OnEdit();
	void			OnCut();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSponsorsFrame)
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSponsorsFrame();

	// Generated message map functions
	//{{AFX_MSG(CSponsorsFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPONSORSFRAME_H__D86476F7_2FF3_4441_B16A_AD1C3094DE78__INCLUDED_)
