#if !defined(AFX_RMS_H__65F3CDEA_B0E9_4EF3_98C9_1034B428D7F7__INCLUDED_)
#define AFX_RMS_H__65F3CDEA_B0E9_4EF3_98C9_1034B428D7F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RMs.h : header file
//

#include "..\OnAir\Recorder.h"

///////////////////////////////////////////////////////////////////////
// CRMs dialog

class CRMs : public CDialog
{
// Construction
public:
	CRMs(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRMs();
// Dialog Data
	//{{AFX_DATA(CRMs)
	enum { IDD = IDD_RMS };
	CComboBox	m_cType;
	CComboBox	m_cPath;
	CComboBox	m_cFileName;
	CString	m_KeyWords;
	COleDateTime	m_Date;
	CString	m_Name;
	CString	m_Type;
	CString	m_Obs;
	//}}AFX_DATA

	CRecorder	*m_pTimers;
	CString		m_Path,
				m_FileName;
	long		m_PathID,
				m_TypeID,
				m_Start,m_Mix,m_End;
	BOOL		m_IsNew;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRMs)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	

	// Generated message map functions
	//{{AFX_MSG(CRMs)
	afx_msg void OnSelchangeRmType();
	afx_msg void OnKillfocusRmType();
	afx_msg void OnKillfocusRmPath();
	afx_msg void OnKillfocusRmFilename();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RMS_H__65F3CDEA_B0E9_4EF3_98C9_1034B428D7F7__INCLUDED_)
