#if !defined(AFX_ONAIRPLAYERWND_H__733A104F_979C_4219_9BAA_B146BA4A47E4__INCLUDED_)
#define AFX_ONAIRPLAYERWND_H__733A104F_979C_4219_9BAA_B146BA4A47E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OnAirPlayerWnd.h : header file
//
#include "VolumeSlider.h"
#include "PlayerOptionsWnd.h"
#include "PlayerButton.h"
#include "OnAirDropTarget.h"
#include "typeLineUpItem.h"

/////////////////////////////////////////////////////////////////////////////
	// COnAirPlayerWnd window

class COnAirPlayerWnd : public CStatic
{
// Construction
public:
	COnAirPlayerWnd();

// Attributes
public:
	CPlayerOptionsWnd	*m_pOptions;
	CVolumeSlider		*m_pVolume;
	CPlayerButton		*m_pCue,
						*m_pUnCue,
						*m_pStop,
						*m_pMix,
						*m_pPlay;
	Bitmap				*m_bmName;
	Bitmap				*m_bmCrono;
	WORD				m_wPlayerState;
	WORD				m_wPlayerPos;
	typeLineUpItem		*m_lpItem;
	float				m_xres;
	CRect				m_rect;
	LPDIRECTSOUND		m_pDS_Main;

protected:
	COnAirDropTarget	m_DropTarget;
// Operations
public:
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COnAirPlayerWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	void ResetMixAndIntro();
	DWORD64 GetTimeToMix();
	void UpdateButtons();
	LRESULT OnCanDrop(WPARAM,LPARAM);
	LRESULT OnDrop(WPARAM,LPARAM);
	LRESULT OnVolumeChange(WPARAM,LPARAM);
	LRESULT OnSetPause(WPARAM,LPARAM);
	LRESULT OnSetLoop(WPARAM,LPARAM);
	void OnUnCue();
	LRESULT	OnOptions(WPARAM,LPARAM);
	Bitmap * CreateSpectrum();
	void DrawPlayer();
	void PaintCrono();
	void PaintBM();
	void CmCue();
	void CmStop();
	void CmPlay();
	void CmMix();
	void OnSwitchPause();
	void OnSwitchLoop();
	virtual ~COnAirPlayerWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(COnAirPlayerWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ONAIRPLAYERWND_H__733A104F_979C_4219_9BAA_B146BA4A47E4__INCLUDED_)
