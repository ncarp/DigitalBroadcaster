#if !defined(AFX_AIREDLISTBOX_H__BD048784_72EC_4AC0_843A_A7DA24CC89AB__INCLUDED_)
#define AFX_AIREDLISTBOX_H__BD048784_72EC_4AC0_843A_A7DA24CC89AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AiredListBox.h : header file
//
#include "LineUpListBox.h"

/////////////////////////////////////////////////////////////////////////////
// CAiredListBox window

class CAiredListBox : public CLineUpListBox
{
// Construction
public:
	CAiredListBox();

// Attributes
public:
	BOOL m_bIsRefreshing;

// Operations
public:
	LRESULT OnDrop(WPARAM,LPARAM);
	LRESULT OnCanDrop(WPARAM,LPARAM);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAiredListBox)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAiredListBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CAiredListBox)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AIREDLISTBOX_H__BD048784_72EC_4AC0_843A_A7DA24CC89AB__INCLUDED_)
