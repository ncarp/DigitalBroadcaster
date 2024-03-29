#if !defined(AFX_CARTWALLLIST_H__FCDBD48B_86EB_48E6_99A3_FEAA1DB24267__INCLUDED_)
#define AFX_CARTWALLLIST_H__FCDBD48B_86EB_48E6_99A3_FEAA1DB24267__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CartwallList.h : header file
//
#include "Cart.h"

/////////////////////////////////////////////////////////////////////////////
// CCartwallList window

class CCartwallList : public CWnd
{
// Construction
public:
	CCartwallList();

// Attributes
public:
	CCart*	m_Carts[50];

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCartwallList)
	//}}AFX_VIRTUAL

// Implementation
public:
	long m_nPos;
	virtual ~CCartwallList();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCartwallList)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CARTWALLLIST_H__FCDBD48B_86EB_48E6_99A3_FEAA1DB24267__INCLUDED_)
