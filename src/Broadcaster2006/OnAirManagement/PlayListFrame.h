#if !defined(AFX_PLAYLISTFRAME_H__D06B646B_ECF8_41DA_8F22_9B459DC28BC5__INCLUDED_)
#define AFX_PLAYLISTFRAME_H__D06B646B_ECF8_41DA_8F22_9B459DC28BC5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PlayListFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPlayListFrame frame

class CPlayListFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CPlayListFrame)
protected:
	CPlayListFrame();           // protected constructor used by dynamic creation

// Attributes
	CSplitterWnd	m_wndSplitter;
	CToolBarCtrl	m_wndToolBar;
	CReBar			m_wndReBar;
	CStatusBar		m_wndStatusBar;
// Operations
public:
	void	OnNew();
	void	OnEdit();
	void	OnCut();
	void	OnPFL();
	void	OnInfo();
	void	OnStat();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlayListFrame)
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPlayListFrame();

	// Generated message map functions
	//{{AFX_MSG(CPlayListFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYLISTFRAME_H__D06B646B_ECF8_41DA_8F22_9B459DC28BC5__INCLUDED_)
