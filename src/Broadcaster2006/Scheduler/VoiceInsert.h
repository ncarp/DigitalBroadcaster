#if !defined(AFX_VOICEINSERT_H__5C3A889A_8DDE_4DB1_9877_AA2ED002A053__INCLUDED_)
#define AFX_VOICEINSERT_H__5C3A889A_8DDE_4DB1_9877_AA2ED002A053__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VoiceInsert.h : header file
//

#include "..\OnAir\Recorder.h"

/////////////////////////////////////////////////////////////////////////////
// CVoiceInsert dialog

class CVoiceInsert : public CDialog
{
// Construction
public:
	CVoiceInsert(CWnd* pParent = NULL);   // standard constructor
	~CVoiceInsert();

// Dialog Data
	//{{AFX_DATA(CVoiceInsert)
	enum { IDD = IDD_VOICEINSERT };
	CComboBox	m_cFile;
	CComboBox	m_cUser;
	CComboBox	m_cPath;
	CString	m_strName;
	int		m_User;
	//}}AFX_DATA

	CRecorder	*m_pTimers;
	long		m_PathID,
				m_UserID,
				m_Start,
				m_End,
				m_ID;
	CString		m_strFileName,
				m_strPath,
				m_strConnect,
				m_strUser;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVoiceInsert)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void FillFileList();

	// Generated message map functions
	//{{AFX_MSG(CVoiceInsert)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnKillfocusFile();
	afx_msg void OnKillfocusPath();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	virtual void OnCancel();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VOICEINSERT_H__5C3A889A_8DDE_4DB1_9877_AA2ED002A053__INCLUDED_)
