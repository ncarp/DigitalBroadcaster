#if !defined(AFX_STATUSWND_H__24FD676C_08F0_4FF1_A699_3A516F01C39A__INCLUDED_)
#define AFX_STATUSWND_H__24FD676C_08F0_4FF1_A699_3A516F01C39A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StatusWnd.h : header file
//
#include <gdiplus.h>
using namespace Gdiplus;

/////////////////////////////////////////////////////////////////////////////
// CStatusWnd window

class CStatusWnd : public CStatic
{
// Construction
public:
	CStatusWnd();

// Attributes
public:
	Bitmap*	m_bmBack;
	Bitmap*	m_bmSelected;
	Bitmap* m_bmHot;
	Bitmap*	m_bmAutomatic;
	Bitmap*	m_bmLive;
	Bitmap* m_bmManual;

	int		m_nRed;
	BOOL	m_bDesc;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStatusWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	WORD m_wHot;
	WORD m_wSelected;
	void CreateSelectedBitmap();
	CRect	m_rect,
			m_rectAuto,
			m_rectLive,
			m_rectManual;
	void CreateHotBitmap();
	void CreateBitmap();
	virtual ~CStatusWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CStatusWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATUSWND_H__24FD676C_08F0_4FF1_A699_3A516F01C39A__INCLUDED_)
