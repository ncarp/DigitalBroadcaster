#if !defined(AFX_PLAYEROPTIONSWND_H__FBBFD794_FC22_4B75_A0AE_5DCDCB29419B__INCLUDED_)
#define AFX_PLAYEROPTIONSWND_H__FBBFD794_FC22_4B75_A0AE_5DCDCB29419B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PlayerOptionsWnd.h : header file
//

#include "PlayerButton.h"

/////////////////////////////////////////////////////////////////////////////
// CPlayerOptionsWnd window

class CPlayerOptionsWnd : public CStatic
{
// Construction
public:
	CPlayerOptionsWnd();

// Attributes
public:
	CPlayerButton	*m_pPause,
					*m_pLoop;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlayerOptionsWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	void Reset();
	void OnLoop();
	void OnPause();
	virtual ~CPlayerOptionsWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPlayerOptionsWnd)
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYEROPTIONSWND_H__FBBFD794_FC22_4B75_A0AE_5DCDCB29419B__INCLUDED_)
