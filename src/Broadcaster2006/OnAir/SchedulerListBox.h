#if !defined(AFX_SCHEDULERLISTBOX_H__03D6246E_53F2_4D60_834D_1CCC0A2C2454__INCLUDED_)
#define AFX_SCHEDULERLISTBOX_H__03D6246E_53F2_4D60_834D_1CCC0A2C2454__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SchedulerListBox.h : header file
//
#include "LineUpListBox.h"
/////////////////////////////////////////////////////////////////////////////
// CSchedulerListBox window

class CSchedulerListBox : public CLineUpListBox
{
// Construction
public:
	CSchedulerListBox();

// Attributes
public:

// Operations
public:
	LRESULT	OnDrop(WPARAM,LPARAM);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSchedulerListBox)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSchedulerListBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSchedulerListBox)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCHEDULERLISTBOX_H__03D6246E_53F2_4D60_834D_1CCC0A2C2454__INCLUDED_)
