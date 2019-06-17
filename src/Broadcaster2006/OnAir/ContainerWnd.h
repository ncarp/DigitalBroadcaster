#if !defined(AFX_CONTAINERWND_H__300053C6_D70A_4028_989D_846C89029A36__INCLUDED_)
#define AFX_CONTAINERWND_H__300053C6_D70A_4028_989D_846C89029A36__INCLUDED_

#include "MusicContainerWnd.h"
#include "JinglesWnd.h"
#include "ProducerWnd.h"
#include "ComercialWnd.h"
#include "VoiceInsertWnd.h"
#include "InternetWnd.h"
#include "RMsWnd.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ContainerWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CContainerWnd window

class CContainerWnd : public CStatic
{
// Construction
public:
	CContainerWnd();

// Attributes
public:
	CComboBoxEx			*m_ctrlSelection;
	CMusicContainerWnd	*m_wndMusic;
	CJinglesWnd			*m_wndJingles;
	CProducerWnd		*m_wndProducer;
	CComercialWnd		*m_wndComercial;
	CVoiceInsertWnd		*m_wndVoiceInsert;
	CRMsWnd				*m_wndRMs;
	CInternetWnd		*m_wndInternet;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CContainerWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CContainerWnd();

	// Generated message map functions
public:
	//{{AFX_MSG(CContainerWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSelChange();
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONTAINERWND_H__300053C6_D70A_4028_989D_846C89029A36__INCLUDED_)
