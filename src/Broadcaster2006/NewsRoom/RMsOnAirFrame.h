#if !defined(AFX_RMSONAIRFRAME_H__807DF0FB_5531_4948_A8E8_AE910F874F3A__INCLUDED_)
#define AFX_RMSONAIRFRAME_H__807DF0FB_5531_4948_A8E8_AE910F874F3A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RMsOnAirFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRMsOnAirFrame frame

class CRMsOnAirFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CRMsOnAirFrame)
protected:
	CRMsOnAirFrame();           // protected constructor used by dynamic creation

// Attributes
public:
	CSplitterWnd	m_wndSplitter;
	CToolBarCtrl	m_wndToolBar;
	CReBar			m_wndReBar;
// Operations
public:
	void OnEdit();
	void OnCut();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRMsOnAirFrame)
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CRMsOnAirFrame();

	// Generated message map functions
	//{{AFX_MSG(CRMsOnAirFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RMSONAIRFRAME_H__807DF0FB_5531_4948_A8E8_AE910F874F3A__INCLUDED_)
