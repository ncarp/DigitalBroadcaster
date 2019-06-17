#if !defined(AFX_VOICEINSERTRECORDER_H__6F9C9DF4_5D9B_4151_A912_442081C45060__INCLUDED_)
#define AFX_VOICEINSERTRECORDER_H__6F9C9DF4_5D9B_4151_A912_442081C45060__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VoiceInsertRecorder.h : header file
//
#include "Recorder.h"
/////////////////////////////////////////////////////////////////////////////
// CVoiceInsertRecorder window

class CVoiceInsertRecorder : public CWnd
{
// Construction
public:
	CVoiceInsertRecorder();
	
// Attributes
public:
	CEdit		*m_pName,
				*m_pUser;
	CComboBox	*m_pPath,
				*m_pFile;
	CRecorder	*m_pRecorder;
	long		m_PathID;
	CString		m_strFileName,
				m_strPath;
// Operations
public:
	void		OnPathKillFocus();
	void		OnPathSelChange();
	void		OnFileKillFocus();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVoiceInsertRecorder)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CVoiceInsertRecorder();

	// Generated message map functions
protected:
	//{{AFX_MSG(CVoiceInsertRecorder)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VOICEINSERTRECORDER_H__6F9C9DF4_5D9B_4151_A912_442081C45060__INCLUDED_)
