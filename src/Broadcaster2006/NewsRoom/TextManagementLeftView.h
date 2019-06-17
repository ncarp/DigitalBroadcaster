#if !defined(AFX_TEXTMANAGEMENTLEFTVIEW_H__08A632B5_B5B2_4CC8_9A84_3C660D82D5C0__INCLUDED_)
#define AFX_TEXTMANAGEMENTLEFTVIEW_H__08A632B5_B5B2_4CC8_9A84_3C660D82D5C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TextManagementLeftView.h : header file
//

#include "..\include\DigitalLeftView.h"

/////////////////////////////////////////////////////////////////////////////
// CTextManagementLeftView view

class CTextManagementLeftView : public CDigitalLeftView
{
protected:
	CTextManagementLeftView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CTextManagementLeftView)

// Attributes
public:
	static	UINT	RefreshList(LPVOID lp);
	virtual void	OnNew();
	virtual void	OnDoubleClick();
	virtual void	OnCut();
	virtual void	OnSelChange();
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTextManagementLeftView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CTextManagementLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CTextManagementLeftView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEXTMANAGEMENTLEFTVIEW_H__08A632B5_B5B2_4CC8_9A84_3C660D82D5C0__INCLUDED_)
