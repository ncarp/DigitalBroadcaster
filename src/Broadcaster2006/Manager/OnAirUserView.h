#if !defined(AFX_ONAIRUSERVIEW_H__B3288310_0B12_470B_BD2E_39FA0AAD0521__INCLUDED_)
#define AFX_ONAIRUSERVIEW_H__B3288310_0B12_470B_BD2E_39FA0AAD0521__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OnAirUserView.h : header file
//

#include "..\include\DigitalLeftView.h"
/////////////////////////////////////////////////////////////////////////////
// COnAirUserView view

class COnAirUserView : public CDigitalLeftView
{
protected:
	COnAirUserView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(COnAirUserView)

// Attributes
public:

// Operations
public:
	void OnNew();
	void OnDoubleClick();
	void OnCut();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COnAirUserView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~COnAirUserView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(COnAirUserView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ONAIRUSERVIEW_H__B3288310_0B12_470B_BD2E_39FA0AAD0521__INCLUDED_)
