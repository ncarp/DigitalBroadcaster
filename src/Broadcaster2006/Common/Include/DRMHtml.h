#if !defined(AFX_DRMHTML_H__BA3060D5_3DE6_4860_BE6A_FC4F9D2B8C95__INCLUDED_)
#define AFX_DRMHTML_H__BA3060D5_3DE6_4860_BE6A_FC4F9D2B8C95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DRMHtml.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDRMHtml html view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include <afxhtml.h>

#include "..\..\common\include\drmdroptarget.h"

class CDRMHtml : public CHtmlView
{
public:
	CDRMHtml();           // protected constructor used by dynamic creation
protected:
	DECLARE_DYNCREATE(CDRMHtml)

// html Data
public:
	//{{AFX_DATA(CDRMHtml)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	CDRMDropTarget	m_DropTarget;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDRMHtml)
	public:
	virtual void OnNavigateComplete2(LPCTSTR strURL);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CDRMHtml();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CDRMHtml)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRMHTML_H__BA3060D5_3DE6_4860_BE6A_FC4F9D2B8C95__INCLUDED_)
