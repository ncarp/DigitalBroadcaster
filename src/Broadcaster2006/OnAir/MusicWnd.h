#if !defined(AFX_MUSICWND_H__1E96D495_A5C2_4FC5_9D58_B1C66DBA23C3__INCLUDED_)
#define AFX_MUSICWND_H__1E96D495_A5C2_4FC5_9D58_B1C66DBA23C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OnAirListBox.h"

// MusicWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMusicWnd frame

class CMusicWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CMusicWnd)
public:
	CMusicWnd();           // protected constructor used by dynamic creation

// Attributes

public:
	CHeaderCtrl		*m_pHeader;
	CReBar			*m_pRebar;
	COnAirListBox	*m_pList;

// Operations
public:
	void OnPFL(); 
	void OnInfo();
	static UINT ThreadRefreshList( LPVOID lpList);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMusicWnd)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMusicWnd();

	// Generated message map functions
	//{{AFX_MSG(CMusicWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnRefresh();
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MUSICWND_H__1E96D495_A5C2_4FC5_9D58_B1C66DBA23C3__INCLUDED_)
