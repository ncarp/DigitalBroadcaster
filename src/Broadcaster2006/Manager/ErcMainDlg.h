#pragma once
#include "afxwin.h"


// CErcMainDlg dialog

class CErcMainDlg : public CDialog
{
	DECLARE_DYNAMIC(CErcMainDlg)

public:
	CErcMainDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CErcMainDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_ERC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	CComboBox m_cStation;
	afx_msg void OnBnClickedChoosefolder();
	virtual BOOL OnInitDialog();
	CString m_strFolder;
	CEdit m_cFolder;
protected:
	virtual void OnOK();
public:
	int m_nRadio;
	COleDateTime m_DateStart;
	COleDateTime m_DateFinish;
};
