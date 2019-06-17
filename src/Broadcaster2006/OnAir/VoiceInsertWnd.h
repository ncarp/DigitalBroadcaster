#if !defined(AFX_VOICEINSERTWND_H__9DD67551_A0EA_4B08_B88A_A61BB93846D5__INCLUDED_)
#define AFX_VOICEINSERTWND_H__9DD67551_A0EA_4B08_B88A_A61BB93846D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VoiceInsertWnd.h : header file
//

#include "OnAirListBox.h"
#include "VoiceInsertRecorder.h"

/////////////////////////////////////////////////////////////////////////////
// CVoiceInsertWnd frame

class CVoiceInsertWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CVoiceInsertWnd)
public:
	CVoiceInsertWnd();           // protected constructor used by dynamic creation

// Attributes
public:

protected:
	CHeaderCtrl		*m_pHeader;
	CReBar			*m_pRebar;
	COnAirListBox	*m_pList;
	CToolBarCtrl	*m_pToolBar;
	CVoiceInsertRecorder *m_pRecorder;

// Operations
public:
	static UINT RefreshThread(LPVOID lpv);
	void OnDiscard();
	void OnSave();
	void OnVoiceInsert();
	void OnRefresh();
	void OnPFL();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVoiceInsertWnd)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CVoiceInsertWnd();

	// Generated message map functions
	//{{AFX_MSG(CVoiceInsertWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VOICEINSERTWND_H__9DD67551_A0EA_4B08_B88A_A61BB93846D5__INCLUDED_)
