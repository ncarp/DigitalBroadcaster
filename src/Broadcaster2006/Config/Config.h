// Config.h : main header file for the CONFIG application
//

#if !defined(AFX_CONFIG_H__AF1118EB_E9F4_42D1_A791_F7F0FC85F7FC__INCLUDED_)
#define AFX_CONFIG_H__AF1118EB_E9F4_42D1_A791_F7F0FC85F7FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CConfigApp:
// See Config.cpp for the implementation of this class
//

class CConfigApp : public CWinApp
{
public:
	CConfigApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CConfigApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIG_H__AF1118EB_E9F4_42D1_A791_F7F0FC85F7FC__INCLUDED_)
