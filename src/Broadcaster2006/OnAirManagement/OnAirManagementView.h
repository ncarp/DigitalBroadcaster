// OnAirManagementView.h : interface of the COnAirManagementView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ONAIRMANAGEMENTVIEW_H__5C27E29F_599C_44B1_926B_38837B8F7E0E__INCLUDED_)
#define AFX_ONAIRMANAGEMENTVIEW_H__5C27E29F_599C_44B1_926B_38837B8F7E0E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class COnAirManagementView : public CListView
{
protected: // create from serialization only
	COnAirManagementView();
	DECLARE_DYNCREATE(COnAirManagementView)

// Attributes
public:
	COnAirManagementDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COnAirManagementView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COnAirManagementView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COnAirManagementView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in OnAirManagementView.cpp
inline COnAirManagementDoc* COnAirManagementView::GetDocument()
   { return (COnAirManagementDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ONAIRMANAGEMENTVIEW_H__5C27E29F_599C_44B1_926B_38837B8F7E0E__INCLUDED_)
