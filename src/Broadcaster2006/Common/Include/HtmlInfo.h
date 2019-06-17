#if !defined(AFX_HTMLINFO_H__70A1A5B4_C274_41A5_8106_1DECDBD71A66__INCLUDED_)
#define AFX_HTMLINFO_H__70A1A5B4_C274_41A5_8106_1DECDBD71A66__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HtmlInfo.h : header file
//
#include "..\..\common\include\drmhtml.h"

/////////////////////////////////////////////////////////////////////////////
// CHtmlInfo frame

class CHtmlInfo : public CFrameWnd
{
	DECLARE_DYNCREATE(CHtmlInfo)
public:
	CHtmlInfo();           // protected constructor used by dynamic creation

// Attributes
public:
	CDRMHtml		*m_pView;
	WINDOWPLACEMENT m_Placement;
	BOOL			m_bHide;
	CDRMDropTarget	m_DropTarget;

// Operations
public:
	void	RestoreWindow();
	void	SetView( CString str );
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHtmlInfo)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CHtmlInfo();

public:
	// Generated message map functions
	//{{AFX_MSG(CHtmlInfo)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HTMLINFO_H__70A1A5B4_C274_41A5_8106_1DECDBD71A66__INCLUDED_)
