#if !defined(AFX_MUSICCATEGORYWND_H__045A0D8B_64D6_4BD1_86C6_49C6F0B8A259__INCLUDED_)
#define AFX_MUSICCATEGORYWND_H__045A0D8B_64D6_4BD1_86C6_49C6F0B8A259__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MusicCategoryWnd.h : header file
//

#include "OnAirListBox.h"

/////////////////////////////////////////////////////////////////////////////
// CMusicCategoryWnd frame

class CMusicCategoryWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CMusicCategoryWnd)
public:
	CMusicCategoryWnd();           // protected constructor used by dynamic creation

// Attributes
public:
	CComboBoxEx*	m_pSelection;
	CReBar*			m_pRebar;
	COnAirListBox*	m_pList;
	CHeaderCtrl*	m_pHeader;
// Operations
public:
	void OnInfo();
	void OnPFL();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMusicCategoryWnd)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMusicCategoryWnd();
	static UINT ThreadRefreshList(LPVOID lpv);
	// Generated message map functions
	//{{AFX_MSG(CMusicCategoryWnd)
	afx_msg void OnRefresh();
	afx_msg void OnSelChange();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MUSICCATEGORYWND_H__045A0D8B_64D6_4BD1_86C6_49C6F0B8A259__INCLUDED_)
