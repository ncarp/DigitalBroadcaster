// OnAir.h : main header file for the ONAIR application
//

#if !defined(AFX_ONAIR_H__048660BF_F7AB_4F88_B869_3C549BDD20DB__INCLUDED_)
#define AFX_ONAIR_H__048660BF_F7AB_4F88_B869_3C549BDD20DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include <lmcons.h>
#include <mmsystem.h>
#include <dsound.h>
#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// COnAirApp:
// See OnAir.cpp for the implementation of this class
//

class COnAirApp : public CWinApp
{
protected:
	static UINT RemoteControlMainThread(LPVOID);
	static UINT RemoteControlCommunicationThread(LPVOID);
public:
	void GetComputerNameAndID();
	void InitGlobalBitmaps();
	void InitializeGDIplus();
	LPDIRECTSOUND InitializeDirectSound( LPGUID lpGuid );
	BOOL ReadConfig();
	static BOOL CALLBACK DSEnumCallback(LPGUID lpGuid, LPCSTR lpcstrDescription, LPCSTR lpcstrModule, LPVOID lpContext);
	static BOOL	CALLBACK DSCEnumCallback(LPGUID lpGuid, LPCSTR lpcstrDescription, LPCSTR lpcstrModule, LPVOID lpContext);
	LPDIRECTSOUNDCAPTURE InitializeDirectSoundCapture( LPGUID lpGuid );

	COnAirApp();
	~COnAirApp();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COnAirApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(COnAirApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ONAIR_H__048660BF_F7AB_4F88_B869_3C549BDD20DB__INCLUDED_)
