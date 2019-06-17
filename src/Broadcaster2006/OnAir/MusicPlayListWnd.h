#if !defined(AFX_MUSICPLAYLISTWND_H__42FDCD22_E344_4212_90B5_44071888C7CA__INCLUDED_)
#define AFX_MUSICPLAYLISTWND_H__42FDCD22_E344_4212_90B5_44071888C7CA__INCLUDED_

#include "OnAirListBox.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MusicPlayListWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMusicPlayListWnd frame

class CMusicPlayListWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CMusicPlayListWnd)

public:
	CMusicPlayListWnd();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
	void OnInfo();
	void OnPFL();
	void OnRefresh();
	CComboBoxEx*	m_pSelection;
	CReBar*			m_pRebar;
	COnAirListBox*	m_pList;
	CHeaderCtrl*	m_pHeader;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMusicPlayListWnd)
	//}}AFX_VIRTUAL

// Implementation
protected:
	static UINT ThreadRefreshList(LPVOID lpv);
	virtual ~CMusicPlayListWnd();

	// Generated message map functions
	//{{AFX_MSG(CMusicPlayListWnd)
	afx_msg void OnSelChange();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MUSICPLAYLISTWND_H__42FDCD22_E344_4212_90B5_44071888C7CA__INCLUDED_)
