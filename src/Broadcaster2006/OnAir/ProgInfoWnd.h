#if !defined(AFX_PROGINFOWND_H__4E474F0F_22DD_4623_B6D8_4827444AD33F__INCLUDED_)
#define AFX_PROGINFOWND_H__4E474F0F_22DD_4623_B6D8_4827444AD33F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProgInfoWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProgInfoWnd window

#include "OnAirDefines.h"

class CProgInfoWnd : public CStatic
{
// Construction
public:
	CProgInfoWnd();

// Attributes
public:
	Bitmap*		m_bmCrono;
	Bitmap*		m_bmBack;
	typeArchiveItem* m_pNextProg;
	DWORD64		m_qwStart,
				m_qwStartPlaying,
				m_qwMinLength,
				m_qwNextProg;
	CMenu		*m_Menu,
				*m_ContentMenu;
	CBitmap		*m_bmMusic,
				*m_bmSpot,
				*m_bmJingle,
				*m_bmVoice,
				*m_bmTime,
				*m_bmRM;
	int			m_nCount;
	CString		m_strOnAirConnect;

// Operations
public:
	void GetNextProg();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgInfoWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	void	OnRefresh();
	void	OnLineUp();
	void	OnSkip();

	virtual ~CProgInfoWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CProgInfoWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSysColorChange();
	afx_msg void OnPaint();
	afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGINFOWND_H__4E474F0F_22DD_4623_B6D8_4827444AD33F__INCLUDED_)
