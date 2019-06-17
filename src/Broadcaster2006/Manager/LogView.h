#if !defined(AFX_LOGVIEW_H__A05638A6_79B3_40FF_8D19_ABC452D11965__INCLUDED_)
#define AFX_LOGVIEW_H__A05638A6_79B3_40FF_8D19_ABC452D11965__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LogView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLogView html view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include <afxhtml.h>

class CLogView : public CHtmlView
{
protected:
	CLogView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CLogView)

// html Data
public:
	//{{AFX_DATA(CLogView)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLogView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CLogView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CLogView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGVIEW_H__A05638A6_79B3_40FF_8D19_ABC452D11965__INCLUDED_)
