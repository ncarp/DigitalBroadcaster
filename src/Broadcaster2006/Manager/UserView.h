#if !defined(AFX_USERVIEW_H__1732FACB_0696_435F_AA85_15CC4634C061__INCLUDED_)
#define AFX_USERVIEW_H__1732FACB_0696_435F_AA85_15CC4634C061__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UserView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUserView view

class CUserView : public CListView
{
protected:
	CUserView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CUserView)

// Attributes
public:

// Operations
public:
	void OnAddUser();
	void OnCutUser();
	void RefreshList();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CUserView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
public:
	//{{AFX_MSG(CUserView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERVIEW_H__1732FACB_0696_435F_AA85_15CC4634C061__INCLUDED_)
