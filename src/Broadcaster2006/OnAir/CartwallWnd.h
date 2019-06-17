#if !defined(AFX_CARTWALLWND_H__3D572516_0442_4A9F_B8D3_AFB82B8A43A0__INCLUDED_)
#define AFX_CARTWALLWND_H__3D572516_0442_4A9F_B8D3_AFB82B8A43A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CartwallWnd.h : header file
//

#include "CartwallList.h"

/////////////////////////////////////////////////////////////////////////////
// CCartwallWnd frame

class CCartwallWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CCartwallWnd)
public:
	CCartwallWnd();           // protected constructor used by dynamic creation

// Attributes
public:
	CReBar			*m_pRebar;
	CToolBarCtrl	*m_pToolBar;
	CCartwallList	*m_pList;
	CString			m_strCartName;
	long			m_CartwallID;

// Operations
public:
	LRESULT OnStopAll(WPARAM=0,LPARAM=0);
	LRESULT OnPlayCart(WPARAM,LPARAM=0);
	void OnNew();
	void OnSave();
	void OnLoad();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCartwallWnd)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CCartwallWnd();

	// Generated message map functions
	//{{AFX_MSG(CCartwallWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CARTWALLWND_H__3D572516_0442_4A9F_B8D3_AFB82B8A43A0__INCLUDED_)
