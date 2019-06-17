#if !defined(AFX_TEXTONAIRFRAME_H__B424A064_1869_491F_A171_C82DFA4BD0DE__INCLUDED_)
#define AFX_TEXTONAIRFRAME_H__B424A064_1869_491F_A171_C82DFA4BD0DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TextOnAirFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTextOnAirFrame frame

class CTextOnAirFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CTextOnAirFrame)
protected:
	CTextOnAirFrame();           // protected constructor used by dynamic creation

// Attributes
public:
	CSplitterWnd	m_wndSplitter;
	CToolBarCtrl	m_wndToolBar;
	CReBar			m_wndReBar;

// Operations
public:
	void	OnCut();
	void	OnEdit();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTextOnAirFrame)
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CTextOnAirFrame();

	// Generated message map functions
	//{{AFX_MSG(CTextOnAirFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEXTONAIRFRAME_H__B424A064_1869_491F_A171_C82DFA4BD0DE__INCLUDED_)
