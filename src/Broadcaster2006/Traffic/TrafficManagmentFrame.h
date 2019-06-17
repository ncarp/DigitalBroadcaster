#if !defined(AFX_TRAFFICMANAGMENTFRAME_H__0B24D95F_B250_4FFF_8DD8_EE2D2B17B28C__INCLUDED_)
#define AFX_TRAFFICMANAGMENTFRAME_H__0B24D95F_B250_4FFF_8DD8_EE2D2B17B28C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TrafficManagmentFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTrafficManagmentFrame frame

class CTrafficManagmentFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CTrafficManagmentFrame)
protected:
	CTrafficManagmentFrame();           // protected constructor used by dynamic creation

// Attributes
public:
	CSplitterWnd	m_wndSplitter;
	CToolBarCtrl	m_wndToolBar;
	CReBar			m_wndReBar;

// Operations
public:
	void OnNewSpot();
	void OnEdit();
	void OnCut();
	void OnNewSchedule();
	void OnQueryBlocks();
	void OnPFL();
	void OnInfo();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrafficManagmentFrame)
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CTrafficManagmentFrame();

	// Generated message map functions
	//{{AFX_MSG(CTrafficManagmentFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRAFFICMANAGMENTFRAME_H__0B24D95F_B250_4FFF_8DD8_EE2D2B17B28C__INCLUDED_)
