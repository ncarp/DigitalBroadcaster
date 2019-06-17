#if !defined(AFX_BLOCKSWND_H__5E7B8506_755B_4BB1_84C6_FC467ABADF81__INCLUDED_)
#define AFX_BLOCKSWND_H__5E7B8506_755B_4BB1_84C6_FC467ABADF81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BlocksWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBlocksWnd frame
#include "OnAirListBox.h"

class CBlocksWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CBlocksWnd)
public:
	CBlocksWnd();           // protected constructor used by dynamic creation

// Attributes
public:
	CHeaderCtrl		*m_pHeader;
	CReBar			*m_pRebar;
	COnAirListBox	*m_pList;

// Operations
public:
	void OnRefresh();
	static UINT OnRefreshThread(LPVOID T);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBlocksWnd)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CBlocksWnd();
	
	// Generated message map functions
	//{{AFX_MSG(CBlocksWnd)
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

#endif // !defined(AFX_BLOCKSWND_H__5E7B8506_755B_4BB1_84C6_FC467ABADF81__INCLUDED_)
