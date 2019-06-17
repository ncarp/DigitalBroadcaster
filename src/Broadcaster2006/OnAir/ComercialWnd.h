#if !defined(AFX_COMERCIALWND_H__3541B0E8_5822_4E87_9D9F_740DF0F21F84__INCLUDED_)
#define AFX_COMERCIALWND_H__3541B0E8_5822_4E87_9D9F_740DF0F21F84__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ComercialWnd.h : header file
//
#include "SponsorsWnd.h"
#include "BlocksWnd.h"
#include "TrafficBumpedWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CComercialWnd window

class CComercialWnd : public CFrameWnd
{
// Construction
public:
	CComercialWnd();

// Attributes
public:
	CComboBoxEx*	m_ctrlSelection;
	CSponsorsWnd*	m_wndSponsors;
	CBlocksWnd*		m_wndBlocks;
	CTrafficBumpedWnd* m_wndBumped;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComercialWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	
	virtual ~CComercialWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CComercialWnd)
	afx_msg void OnSelChange();
	afx_msg void OnPaint();
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

#endif // !defined(AFX_COMERCIALWND_H__3541B0E8_5822_4E87_9D9F_740DF0F21F84__INCLUDED_)
