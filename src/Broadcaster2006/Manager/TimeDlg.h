#if !defined(AFX_TIMEDLG_H__6A4716D0_208F_462A_83A5_CDEBC39573FC__INCLUDED_)
#define AFX_TIMEDLG_H__6A4716D0_208F_462A_83A5_CDEBC39573FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TimeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTimeDlg dialog

class CTimeDlg : public CDialog
{
// Construction
public:
	CTimeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTimeDlg)
	enum { IDD = IDD_TIME };
	CComboBox	m_ctrlPath;
	CComboBox	m_ctrlFolder;
	int		m_nFolder;
	CString	m_strName;
	int		m_nPath;
	//}}AFX_DATA
	CString	m_strFolder,
			m_strPath;
	long int m_lPathID;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTimeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTimeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangePath();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIMEDLG_H__6A4716D0_208F_462A_83A5_CDEBC39573FC__INCLUDED_)
