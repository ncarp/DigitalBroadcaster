// DiscographyView.h : interface of the CDiscographyView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DISCOGRAPHYVIEW_H__E83340F1_2B16_47F0_A209_C7C2D9813FCC__INCLUDED_)
#define AFX_DISCOGRAPHYVIEW_H__E83340F1_2B16_47F0_A209_C7C2D9813FCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDiscographyView : public CListView
{
protected: // create from serialization only
	CDiscographyView();
	DECLARE_DYNCREATE(CDiscographyView)

// Attributes
public:
	CDiscographyDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDiscographyView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDiscographyView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDiscographyView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DiscographyView.cpp
inline CDiscographyDoc* CDiscographyView::GetDocument()
   { return (CDiscographyDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DISCOGRAPHYVIEW_H__E83340F1_2B16_47F0_A209_C7C2D9813FCC__INCLUDED_)
