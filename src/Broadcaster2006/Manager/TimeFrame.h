#if !defined(AFX_TIMEFRAME_H__64D46721_BC9E_451B_9031_B30B64E89C2A__INCLUDED_)
#define AFX_TIMEFRAME_H__64D46721_BC9E_451B_9031_B30B64E89C2A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TimeFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTimeFrame frame

class CTimeFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CTimeFrame)
protected:
	CTimeFrame();           // protected constructor used by dynamic creation

// Attributes
public:
	CToolBarCtrl	m_wndToolBar;
	CReBar			m_wndReBar;
// Operations
public:
	virtual void	OnNew();
	virtual void	OnEdit();
	virtual void	OnCut();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTimeFrame)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CTimeFrame();

	// Generated message map functions
	//{{AFX_MSG(CTimeFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIMEFRAME_H__64D46721_BC9E_451B_9031_B30B64E89C2A__INCLUDED_)
