#if !defined(AFX_ONAIRWND_H__8A15148D_1861_4E0C_AFA6_201B5AE3CF53__INCLUDED_)
#define AFX_ONAIRWND_H__8A15148D_1861_4E0C_AFA6_201B5AE3CF53__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OnAirWnd.h : header file
//

#include "MainClockWnd.h"
#include "TrafficInfoWnd.h"
#include "ProgInfoWnd.h"
#include "LogoWnd.h"
#include "GenericInfoWnd.h"
#include "StatusWnd.h"
#include "ContainerWnd.h"
#include "PFLWnd.h"
#include "wndvu.h"

/////////////////////////////////////////////////////////////////////////////
// COnAirWnd window

class COnAirWnd : public CFrameWnd
{
// Construction
public:
	COnAirWnd();

// Attributes
public:
	CMainClockWnd	*m_wndMainClock;
	CLogoWnd		*m_wndLogoRight,
					*m_wndLogoLeft;
	CGenericInfoWnd *m_wndInfo;
	CStatusWnd		*m_wndStatus;
	CContainerWnd	*m_wndContainer1,
					*m_wndContainer2,
					*m_wndContainer3,
					*m_wndContainer4;
	CWndVU			*m_wndVU1,
					*m_wndVU2;
	int				m_nStartupStep;
	int				m_nHaspFailed;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COnAirWnd)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	//}}AFX_VIRTUAL

// Implementation
public:
	void CreateToolBackground(int W,int H);
	BOOL GetWindowConfig();
	virtual ~COnAirWnd();
	LRESULT	OnUserLogOff(WPARAM,LPARAM);
	// Generated message map functions
protected:
	//{{AFX_MSG(COnAirWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSysColorChange();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ONAIRWND_H__8A15148D_1861_4E0C_AFA6_201B5AE3CF53__INCLUDED_)
