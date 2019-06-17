// Traffic.h : main header file for the TRAFFIC application
//

#if !defined(AFX_TRAFFIC_H__293ABE2B_A7E9_4F21_9FCF_7E03437D3D03__INCLUDED_)
#define AFX_TRAFFIC_H__293ABE2B_A7E9_4F21_9FCF_7E03437D3D03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include <mmsystem.h>
#include <dsound.h>

/////////////////////////////////////////////////////////////////////////////
// CTrafficApp:
// See Traffic.cpp for the implementation of this class
//

class CTrafficApp : public CWinApp
{
public:
	CTrafficApp();
	~CTrafficApp();

	CMultiDocTemplate	*m_pDocTrafficManagment,
						*m_pDocSponsors,
						*m_pDocRecordings;

	void LoadToolBarImageList();
	void LoadTreeImageList();
	void LoadConfig();
	void InitializeGDIPlus();
	LPDIRECTSOUND InitializeDirectSound( LPGUID lpGuid );
	static BOOL CALLBACK DSEnumCallback(LPGUID lpGuid, LPCSTR lpcstrDescription, LPCSTR lpcstrModule, LPVOID lpContext);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrafficApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CTrafficApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRAFFIC_H__293ABE2B_A7E9_4F21_9FCF_7E03437D3D03__INCLUDED_)
