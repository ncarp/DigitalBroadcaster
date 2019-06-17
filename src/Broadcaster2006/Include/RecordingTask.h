#if !defined(AFX_RECORDINGTASK_H__C5687BC9_B080_47B9_8C15_FB58C0189B99__INCLUDED_)
#define AFX_RECORDINGTASK_H__C5687BC9_B080_47B9_8C15_FB58C0189B99__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RecordingTask.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRecordingTask dialog

class CRecordingTask : public CDialog
{
public:
	long	m_TalentID;
	CString	m_TalentName;

// Construction
public:
	CRecordingTask(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRecordingTask)
	enum { IDD = IDD_RECORDINGTASK };
	CComboBox	m_cTalent;
	int		m_Talent;
	CString	m_Task;
	COleDateTime	m_Deadline;
	CString	m_Name;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRecordingTask)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRecordingTask)
	afx_msg void OnKillfocusTalent();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECORDINGTASK_H__C5687BC9_B080_47B9_8C15_FB58C0189B99__INCLUDED_)
