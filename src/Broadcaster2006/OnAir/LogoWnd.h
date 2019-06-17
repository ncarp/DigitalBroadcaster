#if !defined(AFX_LOGOWND_H__B63D57DA_F08C_4A99_AFE7_62BB837DCDCB__INCLUDED_)
#define AFX_LOGOWND_H__B63D57DA_F08C_4A99_AFE7_62BB837DCDCB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LogoWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLogoWnd window

class CLogoWnd : public CStatic
{
// Construction
public:
	CLogoWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLogoWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	Bitmap *m_bmBack;
	Bitmap *m_bmTop;
	Bitmap *m_bmRadio;
	int		m_nStep;
	virtual ~CLogoWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CLogoWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysColorChange();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGOWND_H__B63D57DA_F08C_4A99_AFE7_62BB837DCDCB__INCLUDED_)
