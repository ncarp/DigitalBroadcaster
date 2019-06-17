// Conversao.h : main header file for the CONVERSAO application
//

#if !defined(AFX_CONVERSAO_H__023C764F_F518_4664_BA16_6368E068715B__INCLUDED_)
#define AFX_CONVERSAO_H__023C764F_F518_4664_BA16_6368E068715B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CConversaoApp:
// See Conversao.cpp for the implementation of this class
//

class CConversaoApp : public CWinApp
{
public:
	CConversaoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConversaoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CConversaoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONVERSAO_H__023C764F_F518_4664_BA16_6368E068715B__INCLUDED_)
