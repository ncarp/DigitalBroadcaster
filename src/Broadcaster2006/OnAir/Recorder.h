#if !defined(AFX_RECORDER_H__1702CB34_44D8_40E0_B81D_8908558599E8__INCLUDED_)
#define AFX_RECORDER_H__1702CB34_44D8_40E0_B81D_8908558599E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Recorder.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRecorder window

#include "PlayerButton.h"
#include "TimerDefinition.h"
#include "..\common\include\AudioStream.h"

class CRecorder : public CStatic
{
// Construction
public:
	CRecorder();

// Attributes
public:
	CTimerDefinition *m_pTimer;

	CButton			*m_pFindPlay,
					*m_pSoundCheck,
					*m_pLoopCheck;
	CPlayerButton	*m_pPlay,
					*m_pStop,
					*m_pPause,
					*m_pRec;
	CSliderCtrl		*m_pSlider;
	CAudioStream	*m_pSound;
	CStatic			*m_pStart,
					*m_pFadeIn,
					*m_pIntro,
					*m_pFadeOut,
					*m_pMix,
					*m_pEnd,
					*m_pLoopA,
					*m_pLoopB;
	BOOL			m_bCheckSound,
					m_bCheckLoop,
					m_bCanRec;
	WORD			m_wMode;
	CString			m_strFileName;

// Operations
public:
	LRESULT OnUpdateTimers(WPARAM,LPARAM);
	LRESULT	OnGoTo(WPARAM,LPARAM);

	void SetFile(CString strFile);
	void KillFile();
	void OnResetStart();
	void OnResetFadeIn();
	void OnResetIntro();
	void OnResetFadeOut();
	void OnResetMix();
	void OnResetEnd();
	void OnResetLoopA();
	void OnResetLoopB();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRecorder)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRecorder();
	void	OnRec();
	void	OnPlay();
	void	OnStop();
	void	OnPause();
	void	OnFindPlay();
	void	OnCheckSound();
	void	OnCheckLoop();

	// Generated message map functions
protected:
	//{{AFX_MSG(CRecorder)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECORDER_H__1702CB34_44D8_40E0_B81D_8908558599E8__INCLUDED_)
