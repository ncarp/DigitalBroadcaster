// NewsRoom.h : main header file for the NEWSROOM application
//

#if !defined(AFX_NEWSROOM_H__35EBB667_64D4_4342_BC5B_EC63DA957C59__INCLUDED_)
#define AFX_NEWSROOM_H__35EBB667_64D4_4342_BC5B_EC63DA957C59__INCLUDED_

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
// CNewsRoomApp:
// See NewsRoom.cpp for the implementation of this class
//

class CNewsRoomApp : public CWinApp
{
public:
	CMultiDocTemplate	*m_pDocRMsManagement,
						*m_pDocRMsOnAir,
						*m_pDocRMsLineUp,
						*m_pDocTextManagement,
						*m_pDocTextOnAir,
						*m_pDocTextLineUp;
public:
	CNewsRoomApp();

	void LoadToolBarImageList();
	void LoadTreeImageList();
	void LoadConfig();
	void InitializeGDIPlus();
	LPDIRECTSOUND			InitializeDirectSound( LPGUID lpGuid );
	LPDIRECTSOUNDCAPTURE	InitializeDirectSoundCapture( LPGUID lpGuid );
	static BOOL CALLBACK	DSEnumCallback(LPGUID lpGuid, LPCSTR lpcstrDescription, LPCSTR lpcstrModule, LPVOID lpContext);
	static BOOL	CALLBACK	DSCaptureEnumCallback(LPGUID lpGuid, LPCSTR lpcstrDescription, LPCSTR lpcstrModule, LPVOID lpContext);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewsRoomApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CNewsRoomApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWSROOM_H__35EBB667_64D4_4342_BC5B_EC63DA957C59__INCLUDED_)
