#if !defined(AFX_PRODUCERMUSICMAIN_H__FA9A81A4_2F71_4140_B447_580F7A0395CE__INCLUDED_)
#define AFX_PRODUCERMUSICMAIN_H__FA9A81A4_2F71_4140_B447_580F7A0395CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProducerMusicMain.h : header file
//

#include "OnAirListBox.h"
#include "ProducerMusicEditing.h"

/////////////////////////////////////////////////////////////////////////////
// CProducerMusicMain frame

class CProducerMusicMain : public CFrameWnd
{
	DECLARE_DYNCREATE(CProducerMusicMain)

public:
	CProducerMusicMain();           // protected constructor used by dynamic creation

// Attributes
public:

protected:
	CHeaderCtrl		*m_pHeader;
	CReBar			*m_pRebar;
	COnAirListBox	*m_pList;
	CToolBarCtrl	*m_pToolBar;
	CComboBoxEx		*m_ctrlSelection;
	CProducerMusicEditing	*m_pEdit;

// Operations
public:
	long m_PathID;
	CString m_strPath;
	void RefreshFileList();
	void RefreshPathList();
	void OnDiscard();
	void OnSave();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProducerMusicMain)
	//}}AFX_VIRTUAL

// Implementation
protected:
	static UINT RefreshThread( LPVOID p);
	virtual ~CProducerMusicMain();

	// User Messages
	LRESULT	OnDblClk(WPARAM,LPARAM);

	// Generated message map functions
	//{{AFX_MSG(CProducerMusicMain)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnSelChange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRODUCERMUSICMAIN_H__FA9A81A4_2F71_4140_B447_580F7A0395CE__INCLUDED_)
