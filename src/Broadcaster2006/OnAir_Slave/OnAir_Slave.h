// OnAir_Slave.h : main header file for the ONAIR_SLAVE application
//

#if !defined(AFX_ONAIR_SLAVE_H__DA025B3F_8140_43FC_8580_B0A64FD177A3__INCLUDED_)
#define AFX_ONAIR_SLAVE_H__DA025B3F_8140_43FC_8580_B0A64FD177A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include <stdio.h>

/////////////////////////////////////////////////////////////////////////////
// COnAir_SlaveApp:
// See OnAir_Slave.cpp for the implementation of this class
//

class COnAir_SlaveApp : public CWinApp
{
public:
	void GetComputerNameAndID();
	void InitGlobalBitmaps();
	void InitializeGDIplus();
	LPDIRECTSOUND InitializeDirectSound( LPGUID lpGuid );
	BOOL ReadConfig();

	static UINT ControlThread(LPVOID);
	static UINT CommunicationThread(LPVOID);

	static BOOL CALLBACK DSEnumCallback(LPGUID lpGuid, LPCSTR lpcstrDescription, LPCSTR lpcstrModule, LPVOID lpContext);
	static BOOL	CALLBACK DSCEnumCallback(LPGUID lpGuid, LPCSTR lpcstrDescription, LPCSTR lpcstrModule, LPVOID lpContext);
	LPDIRECTSOUNDCAPTURE InitializeDirectSoundCapture( LPGUID lpGuid );

	COnAir_SlaveApp();
	~COnAir_SlaveApp();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COnAir_SlaveApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

public:
	//{{AFX_MSG(COnAir_SlaveApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ONAIR_SLAVE_H__DA025B3F_8140_43FC_8580_B0A64FD177A3__INCLUDED_)
