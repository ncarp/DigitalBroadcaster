#if !defined(AFX_RMSMANAGEMENTLEFTVIEW_H__F5CA440C_BD37_4496_8099_6E9E1E76B787__INCLUDED_)
#define AFX_RMSMANAGEMENTLEFTVIEW_H__F5CA440C_BD37_4496_8099_6E9E1E76B787__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RMsManagementLeftView.h : header file
//

#include "..\include\DigitalLeftView.h"

/////////////////////////////////////////////////////////////////////////////
// CRMsManagementLeftView view

class CRMsManagementLeftView : public CDigitalLeftView
{
protected:
	CRMsManagementLeftView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CRMsManagementLeftView)

// Attributes
public:

// Operations
public:
			void	OnNew();
			void	OnPFL();
	virtual void	OnDoubleClick();
	virtual void	OnSelChange();
	virtual void	OnCut();
	static	UINT	RefreshList(LPVOID lp);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRMsManagementLeftView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CRMsManagementLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CRMsManagementLeftView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RMSMANAGEMENTLEFTVIEW_H__F5CA440C_BD37_4496_8099_6E9E1E76B787__INCLUDED_)
