// BroadcasterMusic.h : main header file for the BroadcasterMusic application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CBroadcasterMusicApp:
// See BroadcasterMusic.cpp for the implementation of this class
//

class CBroadcasterMusicApp : public CWinApp
{
public:
	CBroadcasterMusicApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CBroadcasterMusicApp theApp;