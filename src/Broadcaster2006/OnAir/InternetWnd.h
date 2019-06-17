#if !defined(AFX_INTERNETWND_H__17FB8050_2270_4C2C_B272_0CEDE2B4F0AE__INCLUDED_)
#define AFX_INTERNETWND_H__17FB8050_2270_4C2C_B272_0CEDE2B4F0AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InternetWnd.h : header file
//
#include "OnAirHtml.h"

/////////////////////////////////////////////////////////////////////////////
// CInternetWnd frame

class CInternetWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CInternetWnd)
public:
	CInternetWnd();           // protected constructor used by dynamic creation

// Attributes
public:
	CReBar			*m_pRebar;
	CToolBarCtrl	*m_pToolBar;
	CComboBoxEx		*m_pAdress;
	CStatusBar		*m_pStatus;
	COnAirHtml		*m_pHtml;
// Operations
public:
	void	OnBack();
	void	OnFoward();
	void	OnRefresh();
	void	OnStop();
	void	OnInfo();
	void	OnHelp();
	void	OnNewAddressEnter();
	LRESULT	OnNavigateComplete(WPARAM,LPARAM);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInternetWnd)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CInternetWnd();

	// Generated message map functions
	//{{AFX_MSG(CInternetWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTERNETWND_H__17FB8050_2270_4C2C_B272_0CEDE2B4F0AE__INCLUDED_)
