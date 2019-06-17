#if !defined(AFX_RECORDINGSFRAME_H__0BD6D3CA_1BA6_4002_9F59_4B0D9DA04269__INCLUDED_)
#define AFX_RECORDINGSFRAME_H__0BD6D3CA_1BA6_4002_9F59_4B0D9DA04269__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RecordingsFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRecordingsFrame frame

class CRecordingsFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CRecordingsFrame)
protected:
	CRecordingsFrame();           // protected constructor used by dynamic creation

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
	void	OnPFL();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRecordingsFrame)
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CRecordingsFrame();

	// Generated message map functions
	//{{AFX_MSG(CRecordingsFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECORDINGSFRAME_H__0BD6D3CA_1BA6_4002_9F59_4B0D9DA04269__INCLUDED_)
