#if !defined(AFX_AIREDWND_H__E372F17E_9089_4536_B680_3109AE69491C__INCLUDED_)
#define AFX_AIREDWND_H__E372F17E_9089_4536_B680_3109AE69491C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AiredWnd.h : header file
//
#include "AiredListBox.h"
#include "logger.h"

/////////////////////////////////////////////////////////////////////////////
// CAiredWnd frame

class CAiredWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CAiredWnd)
public:
	CAiredWnd();           // protected constructor used by dynamic creation

// Attributes
public:
	CHeaderCtrl		*m_pHeader;
	CReBar			*m_pRebar;
	CAiredListBox	*m_pList;

// Operations
public:
	void LogItem( typeLogItem *lpItem );
	void OnRefresh();
	static UINT RefreshList( LPVOID lp);
protected:
	static UINT LogItemThread( LPVOID lpItem );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAiredWnd)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CAiredWnd();

	// Generated message map functions
	//{{AFX_MSG(CAiredWnd)
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

#endif // !defined(AFX_AIREDWND_H__E372F17E_9089_4536_B680_3109AE69491C__INCLUDED_)
