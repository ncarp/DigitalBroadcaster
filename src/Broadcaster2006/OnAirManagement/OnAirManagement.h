// OnAirManagement.h : main header file for the ONAIRMANAGEMENT application
//

#if !defined(AFX_ONAIRMANAGEMENT_H__2C447DAE_8A3E_4527_A3C2_232BBE39FA06__INCLUDED_)
#define AFX_ONAIRMANAGEMENT_H__2C447DAE_8A3E_4527_A3C2_232BBE39FA06__INCLUDED_

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
// COnAirManagementApp:
// See OnAirManagement.cpp for the implementation of this class
//

class COnAirManagementApp : public CWinApp
{
public:
	COnAirManagementApp();

	CMultiDocTemplate	*m_pDocJingles,
						*m_pDocJinglesOnAir,
						*m_pDocBlocks,
						*m_pDocPlayLists,
						*m_pDocRecordings,
						*m_pDocInstrumental;
	

			void	LoadTreeImageList();
			void	LoadToolBarImageList();
			void	LoadConfig();
			void	InitializeGDIPlus();
	LPDIRECTSOUND	InitializeDirectSound( LPGUID lpGuid );
	static	BOOL	CALLBACK DSEnumCallback(LPGUID lpGuid, LPCSTR lpcstrDescription, LPCSTR lpcstrModule, LPVOID lpContext);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COnAirManagementApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(COnAirManagementApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ONAIRMANAGEMENT_H__2C447DAE_8A3E_4527_A3C2_232BBE39FA06__INCLUDED_)
