// LeftView.h : interface of the CLeftView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LEFTVIEW_H__FC00955E_517F_4A8F_AE17_E3FDF8200873__INCLUDED_)
#define AFX_LEFTVIEW_H__FC00955E_517F_4A8F_AE17_E3FDF8200873__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\include\DigitalLeftView.h"

class CDiscographyDoc;

class CLeftView : public CDigitalLeftView
{
protected: // create from serialization only
	CLeftView();
	DECLARE_DYNCREATE(CLeftView)

// Attributes
public:
	CDiscographyDoc* GetDocument();

// Operations
public:
	static UINT RefreshList( LPVOID lp );
	void	OnNew();
	void	OnDoubleClick();
	void	OnRDoubleClick();
	void	OnPFL();
	void	OnEditArtist( HTREEITEM hArtist );
	void	OnEditSong( HTREEITEM hSong );
	void	OnCut();
	void	OnSelChange();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLeftView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLeftView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in LeftView.cpp
inline CDiscographyDoc* CLeftView::GetDocument()
   { return (CDiscographyDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEFTVIEW_H__FC00955E_517F_4A8F_AE17_E3FDF8200873__INCLUDED_)
