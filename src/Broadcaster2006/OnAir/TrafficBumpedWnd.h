#if !defined(AFX_TRAFFICBUMPEDWND_H__570412D5_B6B2_4639_B90B_2FBFE9ED347B__INCLUDED_)
#define AFX_TRAFFICBUMPEDWND_H__570412D5_B6B2_4639_B90B_2FBFE9ED347B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TrafficBumpedWnd.h : header file
//
#include "OnAirListBox.h"

/////////////////////////////////////////////////////////////////////////////
// CTrafficBumpedWnd frame

class CTrafficBumpedWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CTrafficBumpedWnd)
public:
	CTrafficBumpedWnd();           // protected constructor used by dynamic creation

// Attributes
public:
	CHeaderCtrl		*m_pHeader;
	CReBar			*m_pRebar;
	COnAirListBox	*m_pList;

// Operations
public:
	void OnRefresh();
	void OnPFL();
	static UINT OnRefreshThread( LPVOID );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrafficBumpedWnd)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CTrafficBumpedWnd();

	// Generated message map functions
	//{{AFX_MSG(CTrafficBumpedWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRAFFICBUMPEDWND_H__570412D5_B6B2_4639_B90B_2FBFE9ED347B__INCLUDED_)
