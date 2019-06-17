#if !defined(AFX_MUSICINFO_H__78C06594_A1EA_4562_978D_C721E54CB76E__INCLUDED_)
#define AFX_MUSICINFO_H__78C06594_A1EA_4562_978D_C721E54CB76E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MusicInfo.h : header file
//
#include "OnAirHtml.h"

/////////////////////////////////////////////////////////////////////////////
// CMusicInfo frame

class CMusicInfo : public CFrameWnd
{
	DECLARE_DYNCREATE(CMusicInfo)
public:
	CMusicInfo();           // protected constructor used by dynamic creation

// Attributes
public:
	WINDOWPLACEMENT m_Placement;
	BOOL			m_bHide;
	COnAirHtml		*m_pView;
// Operations
public:
	void			RestoreWindow();
	void			SetView( CString str );
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMusicInfo)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMusicInfo();

	// Generated message map functions
	//{{AFX_MSG(CMusicInfo)
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnClose();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MUSICINFO_H__78C06594_A1EA_4562_978D_C721E54CB76E__INCLUDED_)
