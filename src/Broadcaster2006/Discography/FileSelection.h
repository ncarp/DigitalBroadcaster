#include "afxwin.h"
#if !defined(AFX_FILESELECTION_H__29EA031E_4756_4C58_8043_1BCF96EC838C__INCLUDED_)
#define AFX_FILESELECTION_H__29EA031E_4756_4C58_8043_1BCF96EC838C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileSelection.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFileSelection dialog

class CFileSelection : public CDialog
{
// Construction
public:
	CFileSelection(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFileSelection)
	enum { IDD = IDD_FILESELECTION };
	CButton	m_cUnedit;
	CListBox	m_List;
	CButton	m_OK;
	CProgressCtrl	m_Progress;
	CComboBox	m_Path;
	CString	m_cList;
	BOOL	m_Unedit;
	//}}AFX_DATA

	CString m_strPath,
			m_strFileName;
	long	m_PathID;
	BOOL	m_bWorking,
			m_bStop;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileSelection)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	UINT RefreshFileList( LPVOID lp);

	// Generated message map functions
	//{{AFX_MSG(CFileSelection)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangePath();
	afx_msg void OnSelchangeFileList();
	virtual void OnOK();
	virtual void OnCancel();
	virtual void SetFileDetails();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CButton m_cRename;
	CButton m_cDelete;
	CEdit m_cDetails;
	CString m_strDetails;
	afx_msg void OnBnClickedRename();
	afx_msg void OnBnClickedDelete();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILESELECTION_H__29EA031E_4756_4C58_8043_1BCF96EC838C__INCLUDED_)
