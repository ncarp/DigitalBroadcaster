#if !defined(AFX_PRODUCERWND_H__5CE98FF1_BFE7_4847_AF3A_7CE3FCF8C547__INCLUDED_)
#define AFX_PRODUCERWND_H__5CE98FF1_BFE7_4847_AF3A_7CE3FCF8C547__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProducerWnd.h : header file
//

#include "SoundRecorderSelector.h"
#include "ProducerMusicMain.h"
#include "ProducerScheduler.h"

/////////////////////////////////////////////////////////////////////////////
// CProducerWnd frame

class CProducerWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CProducerWnd)
public:
	CProducerWnd();           // protected constructor used by dynamic creation

// Attributes
public:
	CComboBoxEx	*m_ctrlSelection;
	CSoundRecorderSelector* m_wndSoundRecorder;
	CProducerMusicMain*		m_wndMusic;
	CProducerScheduler*		m_wndScheduler;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProducerWnd)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CProducerWnd();

	// Generated message map functions
	//{{AFX_MSG(CProducerWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnSelChange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRODUCERWND_H__5CE98FF1_BFE7_4847_AF3A_7CE3FCF8C547__INCLUDED_)
