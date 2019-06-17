#if !defined(AFX_MAINCLOCKWND_H__2AAE5710_6227_44CE_B784_F09B0BAFDCCB__INCLUDED_)
#define AFX_MAINCLOCKWND_H__2AAE5710_6227_44CE_B784_F09B0BAFDCCB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainClockWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMainClockWnd window

class CMainClockWnd : public CStatic
{
// Construction
public:
	CMainClockWnd();

// Attributes
public:
	
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainClockWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	Bitmap *m_bmBack;
	CString m_strPreviousDate;
	virtual ~CMainClockWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMainClockWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSysColorChange();
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINCLOCKWND_H__2AAE5710_6227_44CE_B784_F09B0BAFDCCB__INCLUDED_)
