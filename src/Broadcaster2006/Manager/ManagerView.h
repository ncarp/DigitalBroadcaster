// ManagerView.h : interface of the CManagerView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MANAGERVIEW_H__37894BF8_7013_4EC1_9F3A_38D4C5E2F3FA__INCLUDED_)
#define AFX_MANAGERVIEW_H__37894BF8_7013_4EC1_9F3A_38D4C5E2F3FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CManagerView : public CListView
{
protected: // create from serialization only
	CManagerView();
	DECLARE_DYNCREATE(CManagerView)

// Attributes
public:
	CManagerDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CManagerView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CManagerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CManagerView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ManagerView.cpp
inline CManagerDoc* CManagerView::GetDocument()
   { return (CManagerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MANAGERVIEW_H__37894BF8_7013_4EC1_9F3A_38D4C5E2F3FA__INCLUDED_)
