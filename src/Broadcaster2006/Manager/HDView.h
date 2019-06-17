#if !defined(AFX_HDVIEW_H__A304F61B_F724_4A4B_826B_018D9708BC14__INCLUDED_)
#define AFX_HDVIEW_H__A304F61B_F724_4A4B_826B_018D9708BC14__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HDView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHDView view

class CHDView : public CListView
{
protected:
	CHDView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CHDView)

// Attributes
public:

// Operations
public:
	void AddFolder();
	void Refresh();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHDView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CHDView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
public:
	//{{AFX_MSG(CHDView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HDVIEW_H__A304F61B_F724_4A4B_826B_018D9708BC14__INCLUDED_)
