// SchedulerView.h : interface of the CSchedulerView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCHEDULERVIEW_H__E1F14540_FB7D_4505_87F6_94DE734FBF73__INCLUDED_)
#define AFX_SCHEDULERVIEW_H__E1F14540_FB7D_4505_87F6_94DE734FBF73__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSchedulerView : public CListView
{
protected: // create from serialization only
	CSchedulerView();
	DECLARE_DYNCREATE(CSchedulerView)

// Attributes
public:
	CSchedulerDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSchedulerView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSchedulerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSchedulerView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SchedulerView.cpp
inline CSchedulerDoc* CSchedulerView::GetDocument()
   { return (CSchedulerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCHEDULERVIEW_H__E1F14540_FB7D_4505_87F6_94DE734FBF73__INCLUDED_)
