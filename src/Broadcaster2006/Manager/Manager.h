// Manager.h : main header file for the MANAGER application
//

#if !defined(AFX_MANAGER_H__4ADC11E9_25B0_42FA_85DC_05DA273DD9B6__INCLUDED_)
#define AFX_MANAGER_H__4ADC11E9_25B0_42FA_85DC_05DA273DD9B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CManagerApp:
// See Manager.cpp for the implementation of this class
//

class CManagerApp : public CWinApp
{
public:
	CMultiDocTemplate	*pDocOnAirUser,
						*pDocHD,
						*pDocTime,
						*pDocLog,
						*pDocUser;
	
public:
	void LoadConfig();
	CManagerApp();

	void LoadToolBarImageList();
	void LoadTreeImageList();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CManagerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CManagerApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MANAGER_H__4ADC11E9_25B0_42FA_85DC_05DA273DD9B6__INCLUDED_)
