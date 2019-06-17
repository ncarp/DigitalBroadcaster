// Discography.h : main header file for the DISCOGRAPHY application
//

#if !defined(AFX_DISCOGRAPHY_H__8A43CDBE_B7BB_4792_8D00_E72F0D68074D__INCLUDED_)
#define AFX_DISCOGRAPHY_H__8A43CDBE_B7BB_4792_8D00_E72F0D68074D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include <mmsystem.h>
#include <dsound.h>

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDiscographyApp:
// See Discography.cpp for the implementation of this class
//

class CDiscographyApp : public CWinApp
{
public:
	
			void	LoadTreeImageList();
			void	LoadToolBarImageList();
			void	InitializeGDIPlus();
			void	LoadConfig();
	LPDIRECTSOUND	InitializeDirectSound( LPGUID lpGuid );
	static	BOOL	CALLBACK DSEnumCallback(LPGUID lpGuid, LPCSTR lpcstrDescription, LPCSTR lpcstrModule, LPVOID lpContext);

	CDiscographyApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDiscographyApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CDiscographyApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DISCOGRAPHY_H__8A43CDBE_B7BB_4792_8D00_E72F0D68074D__INCLUDED_)
