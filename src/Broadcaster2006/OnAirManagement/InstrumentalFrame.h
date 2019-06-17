#if !defined(AFX_INSTRUMENTALFRAME_H__5F9470AC_E4C2_458C_82FF_E88F9B3F67B4__INCLUDED_)
#define AFX_INSTRUMENTALFRAME_H__5F9470AC_E4C2_458C_82FF_E88F9B3F67B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InstrumentalFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInstrumentalFrame frame

class CInstrumentalFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CInstrumentalFrame)
protected:
	CInstrumentalFrame();           // protected constructor used by dynamic creation

// Attributes
public:
	CSplitterWnd	m_wndSplitter;
	CToolBarCtrl	m_wndToolBar;
	CReBar			m_wndReBar;

// Operations
public:
	void OnCut();
	void OnPFL();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInstrumentalFrame)
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CInstrumentalFrame();

	// Generated message map functions
	//{{AFX_MSG(CInstrumentalFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INSTRUMENTALFRAME_H__5F9470AC_E4C2_458C_82FF_E88F9B3F67B4__INCLUDED_)
