#if !defined(AFX_RMSWND_H__19B6CB3F_DEA6_41BB_95A2_4C7AA40F4B70__INCLUDED_)
#define AFX_RMSWND_H__19B6CB3F_DEA6_41BB_95A2_4C7AA40F4B70__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RMsWnd.h : header file
//

#include "OnAirListBox.h"
/////////////////////////////////////////////////////////////////////////////
// CRMsWnd frame

class CRMsWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CRMsWnd)
public:
	CRMsWnd();           // protected constructor used by dynamic creation

// Attributes
public:
	CHeaderCtrl		*m_pHeader;
	CReBar			*m_pRebar;
	COnAirListBox	*m_pList;

// Operations
public:
	void	OnRefresh();
	void	OnPFL();

	static UINT ThreadRefreshList(LPVOID lp);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRMsWnd)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CRMsWnd();

	// Generated message map functions
	//{{AFX_MSG(CRMsWnd)
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RMSWND_H__19B6CB3F_DEA6_41BB_95A2_4C7AA40F4B70__INCLUDED_)
