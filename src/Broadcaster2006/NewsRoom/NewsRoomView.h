// NewsRoomView.h : interface of the CNewsRoomView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_NEWSROOMVIEW_H__28983E54_9BC3_4A47_A12A_B49C99583A08__INCLUDED_)
#define AFX_NEWSROOMVIEW_H__28983E54_9BC3_4A47_A12A_B49C99583A08__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CNewsRoomView : public CListView
{
protected: // create from serialization only
	CNewsRoomView();
	DECLARE_DYNCREATE(CNewsRoomView)

// Attributes
public:
	CNewsRoomDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewsRoomView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CNewsRoomView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CNewsRoomView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in NewsRoomView.cpp
inline CNewsRoomDoc* CNewsRoomView::GetDocument()
   { return (CNewsRoomDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWSROOMVIEW_H__28983E54_9BC3_4A47_A12A_B49C99583A08__INCLUDED_)
