#if !defined(AFX_COnAirHtml_H__FF7F940A_5530_44A0_A988_3BF20DB0EB11__INCLUDED_)
#define AFX_COnAirHtml_H__FF7F940A_5530_44A0_A988_3BF20DB0EB11__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// COnAirHtml.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COnAirHtml html view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include <afxhtml.h>

class COnAirHtml : public CHtmlView
{
public:
	COnAirHtml();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(COnAirHtml)

// html Data
public:
	//{{AFX_DATA(COnAirHtml)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COnAirHtml)
	public:
	virtual void OnNavigateComplete2(LPCTSTR strURL);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~COnAirHtml();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(COnAirHtml)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COnAirHtml_H__FF7F940A_5530_44A0_A988_3BF20DB0EB11__INCLUDED_)
