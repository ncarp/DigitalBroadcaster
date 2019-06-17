#if !defined(AFX_SPONSORSWND_H__971CCB91_3ADB_480E_8958_3755A195A0A5__INCLUDED_)
#define AFX_SPONSORSWND_H__971CCB91_3ADB_480E_8958_3755A195A0A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SponsorsWnd.h : header file
//

#include "OnAirListBox.h"

/////////////////////////////////////////////////////////////////////////////
// CSponsorsWnd frame

class CSponsorsWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CSponsorsWnd)
public:
	CSponsorsWnd();           // protected constructor used by dynamic creation

// Attributes
public:
	CHeaderCtrl		*m_pHeader;
	CReBar			*m_pRebar;
	COnAirListBox	*m_pList;

// Operations
public:
	void	OnPFL();
protected:
	static UINT ThreadRefresh( LPVOID lpv);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSponsorsWnd)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSponsorsWnd();

	// Generated message map functions
	//{{AFX_MSG(CSponsorsWnd)
	afx_msg void OnRefresh();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPONSORSWND_H__971CCB91_3ADB_480E_8958_3755A195A0A5__INCLUDED_)
