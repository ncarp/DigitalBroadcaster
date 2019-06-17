#if !defined(AFX_SOUNDRECORDERSELECTOR_H__14A92008_C20F_40FF_8B45_706DD7FA91B8__INCLUDED_)
#define AFX_SOUNDRECORDERSELECTOR_H__14A92008_C20F_40FF_8B45_706DD7FA91B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SoundRecorderSelector.h : header file
//

#include "OnAirListBox.h"
#include "SoundRecorderWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CSoundRecorderSelector frame

class CSoundRecorderSelector : public CFrameWnd
{
	DECLARE_DYNCREATE(CSoundRecorderSelector)
public:
	CSoundRecorderSelector();           // protected constructor used by dynamic creation

// Attributes
public:

protected:
	CHeaderCtrl		*m_pHeader;
	CReBar			*m_pRebar;
	COnAirListBox	*m_pList;
	CToolBarCtrl	*m_pToolBar;
	CSoundRecorderWnd *m_pWndRecord;

// Operations
public:
	void OnDiscard();
	void OnSave();

	static UINT ThreadRefresh(LPVOID);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSoundRecorderSelector)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSoundRecorderSelector();

	// Generated message map functions
	//{{AFX_MSG(CSoundRecorderSelector)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnRefresh();
	afx_msg void OnNewVersion();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOUNDRECORDERSELECTOR_H__14A92008_C20F_40FF_8B45_706DD7FA91B8__INCLUDED_)
