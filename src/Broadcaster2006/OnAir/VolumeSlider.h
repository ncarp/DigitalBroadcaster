#if !defined(AFX_VOLUMESLIDER_H__EED23096_4DF0_4096_A3AC_708D6996979D__INCLUDED_)
#define AFX_VOLUMESLIDER_H__EED23096_4DF0_4096_A3AC_708D6996979D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VolumeSlider.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVolumeSlider window

class CVolumeSlider : public CStatic
{
// Construction
public:
	CVolumeSlider();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVolumeSlider)
	//}}AFX_VIRTUAL

// Implementation
public:
	long m_lCurVolume;
	void SetVolume( long V);
	int m_nPrevPos;
	CRect m_rect;
	Bitmap* m_bmBack;
	Bitmap*	m_bmThumb;
	BOOL m_bDragging;
	virtual ~CVolumeSlider();

	// Generated message map functions
protected:
	//{{AFX_MSG(CVolumeSlider)
	afx_msg void OnPaint();
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VOLUMESLIDER_H__EED23096_4DF0_4096_A3AC_708D6996979D__INCLUDED_)
