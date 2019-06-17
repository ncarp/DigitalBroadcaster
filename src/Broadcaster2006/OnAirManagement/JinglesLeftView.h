#if !defined(AFX_JINGLESLEFTVIEW_H__357CCA1F_FA1A_4409_B25E_67D3D76A28D1__INCLUDED_)
#define AFX_JINGLESLEFTVIEW_H__357CCA1F_FA1A_4409_B25E_67D3D76A28D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// JinglesLeftView.h : header file
//
#include "..\include\DigitalLeftView.h"
/////////////////////////////////////////////////////////////////////////////
// CJinglesLeftView view

class CJinglesLeftView : public CDigitalLeftView
{
protected:
	CJinglesLeftView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CJinglesLeftView)

// Attributes
public:
	
// Operations
public:
	static	UINT	RefreshList( LPVOID lp);
	virtual void	OnCut();
	virtual	void	OnPFL();
	virtual void	OnSelChange();
	virtual void	OnNew();
	virtual void	OnDoubleClick();
	virtual void	OnRDoubleClick();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJinglesLeftView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CJinglesLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CJinglesLeftView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JINGLESLEFTVIEW_H__357CCA1F_FA1A_4409_B25E_67D3D76A28D1__INCLUDED_)
