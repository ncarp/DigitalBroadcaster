#if !defined(AFX_RMLINEUPLEFTVIEW_H__E92D17E8_3052_4A9F_99C5_48F6A397BB6E__INCLUDED_)
#define AFX_RMLINEUPLEFTVIEW_H__E92D17E8_3052_4A9F_99C5_48F6A397BB6E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RMLineUpLeftView.h : header file
//

#include "..\include\DigitalLeftView.h"
#include "RMLineUpRightView.h"

/////////////////////////////////////////////////////////////////////////////
// CRMLineUpLeftView view

class CRMLineUpLeftView : public CDigitalLeftView
{
protected:
	CRMLineUpLeftView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CRMLineUpLeftView)

// Attributes
public:
	CString	m_strConnect,
			m_strRadio,
			m_strDB;
	CRMLineUpRightView *m_pViewCart;
// Operations
public:
	static	UINT	RefreshList(LPVOID);
	virtual void	OnSelChange();
	virtual void	OnDoubleClick();
	virtual void	OnCut();
	virtual void	OnNew();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRMLineUpLeftView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CRMLineUpLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CRMLineUpLeftView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RMLINEUPLEFTVIEW_H__E92D17E8_3052_4A9F_99C5_48F6A397BB6E__INCLUDED_)
