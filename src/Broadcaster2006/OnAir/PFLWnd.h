#if !defined(AFX_PFLWND_H__6B5F830F_79FC_446A_9A1B_E3B80C42FBCC__INCLUDED_)
#define AFX_PFLWND_H__6B5F830F_79FC_446A_9A1B_E3B80C42FBCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PFLWnd.h : header file
//
#include "PlayerButton.h"
#include "typeLineUpItem.h"
#include "OnAirDefines.h"

/////////////////////////////////////////////////////////////////////////////
// CPFLWnd frame

class CPFLWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CPFLWnd)
public:
	CPFLWnd();           // protected constructor used by dynamic creation

// Attributes
public:

protected:
	WINDOWPLACEMENT m_Placement;
	CSliderCtrl		*m_pSlider;
	CPlayerButton	*m_pPlay,
					*m_pStop;
	Bitmap			*m_bmName,
					*m_bmCrono;
	typeLineUpItem	*m_pItem;

// Operations
public:
	BOOL m_bHide,
		 m_bScrolling,
		 m_bAutoStart,
		 m_bTopMost;
	void RestoreWindow();
	void PaintCrono();
	float m_xres;
	Bitmap* CreateSpectrum();
	void OnStop();
	void OnPlay();
	void SetSound( typeArchiveItem* lpItem);
	void SetSound(WORD wType,long lID,CString str=g_strOnAirConnect);
	CRect m_rect;
	void DrawPlayer();
	void PaintBM();
	void CueSound();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPFLWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetSound(typeLineUpItem*);
	virtual ~CPFLWnd();

	// Generated message map functions
	//{{AFX_MSG(CPFLWnd)
	afx_msg void OnClose();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PFLWND_H__6B5F830F_79FC_446A_9A1B_E3B80C42FBCC__INCLUDED_)
