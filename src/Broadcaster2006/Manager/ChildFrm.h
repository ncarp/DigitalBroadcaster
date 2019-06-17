// ChildFrm.h : interface of the CChildFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDFRM_H__1D0B02E0_145C_45CA_9D0B_D9DE8EDF2131__INCLUDED_)
#define AFX_CHILDFRM_H__1D0B02E0_145C_45CA_9D0B_D9DE8EDF2131__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CManagerView;

class CChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// Attributes
protected:
	CSplitterWnd m_wndSplitter;
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildFrame)
	public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CManagerView* GetRightPane();
// Generated message map functions
protected:
	//{{AFX_MSG(CChildFrame)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	afx_msg void OnUpdateViewStyles(CCmdUI* pCmdUI);
	afx_msg void OnViewStyle(UINT nCommandID);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDFRM_H__1D0B02E0_145C_45CA_9D0B_D9DE8EDF2131__INCLUDED_)
