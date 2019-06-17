#if !defined(AFX_JINGLES_H__D7DE997C_1360_4C67_98F1_5BADC1701050__INCLUDED_)
#define AFX_JINGLES_H__D7DE997C_1360_4C67_98F1_5BADC1701050__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Jingles.h : header file
//

#include "..\OnAir\Recorder.h"

/////////////////////////////////////////////////////////////////////////////
// CJingles dialog

class CJingles : public CDialog
{
// Construction
public:
	CJingles(CWnd* pParent = NULL);   // standard constructor
	~CJingles();

// Dialog Data
	//{{AFX_DATA(CJingles)
	enum { IDD = IDD_JINGLE };
	CEdit	m_cRythmV;
	CSliderCtrl	m_cRythm;
	CComboBox	m_cType;
	CComboBox	m_cPath;
	CComboBox	m_cFile;
	CString	m_Name;
	int		m_Rythm;
	CString	m_RythmV;
	CString	m_Type;
	//}}AFX_DATA

	CRecorder	*m_pTimers;
	long		m_PathID,
				m_TypeID,
				m_Start,
				m_Intro,
				m_LoopA,
				m_LoopB,
				m_Mix,
				m_End;
	CString		m_Path,
				m_FileName;
	BOOL		m_IsNew;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJingles)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CJingles)
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKillfocusPath();
	afx_msg void OnSelchangePath();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnKillfocusFile();
	afx_msg void OnKillfocusType();
	afx_msg void OnSelchangeType();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JINGLES_H__D7DE997C_1360_4C67_98F1_5BADC1701050__INCLUDED_)
