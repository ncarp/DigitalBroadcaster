// Scheduler.h : main header file for the SCHEDULER application
//

#if !defined(AFX_SCHEDULER_H__107A80D9_0F7D_47BA_87D1_A6518AC6D56F__INCLUDED_)
#define AFX_SCHEDULER_H__107A80D9_0F7D_47BA_87D1_A6518AC6D56F__INCLUDED_

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
// CSchedulerApp:
// See Scheduler.cpp for the implementation of this class
//

class CSchedulerApp : public CWinApp
{
public:
	CSchedulerApp();

	CMultiDocTemplate	*m_pDocSchedule,
						*m_pDocCalendar;

			void	LoadTreeImageList();
			void	LoadToolBarImageList();
			void	LoadConfig();
			void	InitializeGDIPlus();
	LPDIRECTSOUND	InitializeDirectSound( LPGUID lpGuid );
	LPDIRECTSOUNDCAPTURE InitializeDirectSoundCapture( LPGUID lpGuid );
	static	BOOL	CALLBACK DSEnumCallback(LPGUID lpGuid, LPCSTR lpcstrDescription, LPCSTR lpcstrModule, LPVOID lpContext);
	static	BOOL	CALLBACK DSCEnumCallback(LPGUID lpGuid, LPCSTR lpcstrDescription, LPCSTR lpcstrModule, LPVOID lpContext);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSchedulerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CSchedulerApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCHEDULER_H__107A80D9_0F7D_47BA_87D1_A6518AC6D56F__INCLUDED_)
