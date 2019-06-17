#if !defined(AFX_TIMEVIEW_H__31EDF30F_4EB6_4245_A715_2D87CC768310__INCLUDED_)
#define AFX_TIMEVIEW_H__31EDF30F_4EB6_4245_A715_2D87CC768310__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TimeView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTimeView view

class CTimeView : public CListView
{
protected:
	CTimeView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CTimeView)

// Attributes
public:

// Operations
public:
	void OnNew();
	void OnCut();
	void RefreshList();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTimeView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CTimeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
public:
	//{{AFX_MSG(CTimeView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIMEVIEW_H__31EDF30F_4EB6_4245_A715_2D87CC768310__INCLUDED_)
