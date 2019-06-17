#if !defined(AFX_JINGLESWND_H__9E079207_071F_4899_851E_3A74D2B43941__INCLUDED_)
#define AFX_JINGLESWND_H__9E079207_071F_4899_851E_3A74D2B43941__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// JinglesWnd.h : header file
//
#include "OnAirListBox.h"

/////////////////////////////////////////////////////////////////////////////
// CJinglesWnd frame

class CJinglesWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CJinglesWnd)
public:
	CJinglesWnd();           // protected constructor used by dynamic creation

// Attributes
public:
	CHeaderCtrl		*m_pHeader;
	CReBar			*m_pRebar;
	COnAirListBox	*m_pList;
// Operations
public:
	void OnPFL();
	static UINT ThreadRefreshList(LPVOID lp);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJinglesWnd)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CJinglesWnd();

	// Generated message map functions
	//{{AFX_MSG(CJinglesWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnRefresh();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JINGLESWND_H__9E079207_071F_4899_851E_3A74D2B43941__INCLUDED_)
