#if !defined(AFX_TIMERDEFINITION_H__2D99F98A_C862_4615_8212_EF0D4479D2DE__INCLUDED_)
#define AFX_TIMERDEFINITION_H__2D99F98A_C862_4615_8212_EF0D4479D2DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TimerDefinition.h : header file
//
#include <gdiplus.h>
using namespace Gdiplus;
/////////////////////////////////////////////////////////////////////////////
// CTimerDefinition window

#define MN_START	1
#define MN_FADEIN	2
#define MN_INTRO	3
#define MN_FADEOUT	4
#define MN_MIX		5
#define MN_END		6
#define MN_LOOPA	7
#define MN_LOOPB	8

#define TIMERF_SETINICIO	0x0001
#define TIMERF_SETFADEIN	0x0002
#define TIMERF_SETINTRO		0x0004
#define TIMERF_SETFADEOUT	0x0008
#define TIMERF_SETMIX		0x0010
#define TIMERF_SETFIM		0x0020
#define TIMERF_SETLOOPA		0x0040
#define TIMERF_SETLOOPB		0x0080

class CTimerDefinition : public CStatic
{
// Construction
public:
	CTimerDefinition();

// Attributes
public:
	CRect	m_rect,
			m_rectPos;
	long	m_Start,
			m_FadeIn,
			m_Intro,
			m_FadeOut,
			m_Mix,
			m_End,
			m_LoopA,
			m_LoopB;
	int		m_TimerF[10];
	long	m_RightPos,
			m_PlayPos,
			m_LastClickPos;

	float	m_xres;
	DWORD	m_dwFlags;
	CMenu	*m_Menu;

protected:
	Bitmap	*m_bmSpectrum,
			*m_bmTimers,
			*m_bmCrono;
	RectF	rectf;
	HCURSOR	CursorArrow,
			CursorSize;
	UINT	m_ItemDrag;

// Operations
public:
	void SetSpectrum(Bitmap *b);
	void SetViewPoint(long pos);
	void PaintTimerBM();
	void PaintAll();
	void PaintCrono();
	void SetFlags(DWORD f);
	void OnSetStart();
	void OnSetFadeIn();
	void OnSetIntro();
	void OnSetFadeOut();
	void OnSetMix();
	void OnSetEnd();
	void OnSetLoopA();
	void OnSetLoopB();
	void DeleteBM();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTimerDefinition)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTimerDefinition();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTimerDefinition)
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIMERDEFINITION_H__2D99F98A_C862_4615_8212_EF0D4479D2DE__INCLUDED_)
