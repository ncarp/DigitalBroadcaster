#if !defined(AFX_GENERICINFOWND_H__B35ADEBA_1B55_410B_A952_726B51485A68__INCLUDED_)
#define AFX_GENERICINFOWND_H__B35ADEBA_1B55_410B_A952_726B51485A68__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GenericInfoWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGenericInfoWnd window

class CGenericInfoWnd : public CStatic
{
// Construction
public:
	CGenericInfoWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGenericInfoWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	int		m_LineUpX,
			m_TrackX;
	Bitmap	*m_bmBack,
			*m_bmCrono;
	virtual ~CGenericInfoWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGenericInfoWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSysColorChange();
	afx_msg void OnPaint();
	afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GENERICINFOWND_H__B35ADEBA_1B55_410B_A952_726B51485A68__INCLUDED_)
