#if !defined(AFX_MUSICCONTAINERWND_H__A22EC19F_D0D5_4BFB_9734_6E212F28CCC9__INCLUDED_)
#define AFX_MUSICCONTAINERWND_H__A22EC19F_D0D5_4BFB_9734_6E212F28CCC9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MusicContainerWnd.h : header file
//
#include "MusicWnd.h"
#include "MusicPlayListWnd.h"
#include "MusicCategoryWnd.h"
#include "MusicSearchWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CMusicContainerWnd frame

class CMusicContainerWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CMusicContainerWnd)
public:
	CMusicContainerWnd();           // protected constructor used by dynamic creation

// Attributes
public:
	CComboBoxEx*		m_ctrlSelection;
	CMusicWnd*			m_wndMusicDiscography;
	CMusicPlayListWnd*	m_wndMusicPlayList;
	CMusicCategoryWnd*	m_wndMusicCategory;
	CMusicSearchWnd*	m_wndMusicSearch;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMusicContainerWnd)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMusicContainerWnd();

	// Generated message map functions
	//{{AFX_MSG(CMusicContainerWnd)
	afx_msg void OnSelChange();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MUSICCONTAINERWND_H__A22EC19F_D0D5_4BFB_9734_6E212F28CCC9__INCLUDED_)
