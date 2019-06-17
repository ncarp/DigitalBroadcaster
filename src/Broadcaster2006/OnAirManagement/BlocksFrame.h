#if !defined(AFX_BLOCKSFRAME_H__2D5885F3_CC2F_48B5_A91A_EC2998995218__INCLUDED_)
#define AFX_BLOCKSFRAME_H__2D5885F3_CC2F_48B5_A91A_EC2998995218__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BlocksFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBlocksFrame frame

class CBlocksFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CBlocksFrame)
protected:
	CBlocksFrame();           // protected constructor used by dynamic creation

// Attributes
public:
	CSplitterWnd	m_wndSplitter;
	CToolBarCtrl	m_wndToolBar;
	CReBar			m_wndReBar;

// Operations
public:
	void	OnNew();
	void	OnEdit();
	void	OnCut();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBlocksFrame)
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CBlocksFrame();

	// Generated message map functions
	//{{AFX_MSG(CBlocksFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BLOCKSFRAME_H__2D5885F3_CC2F_48B5_A91A_EC2998995218__INCLUDED_)
