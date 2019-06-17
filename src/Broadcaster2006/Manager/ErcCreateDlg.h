#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CErcCreateDlg dialog

class CErcCreateDlg : public CDialog
{
	DECLARE_DYNAMIC(CErcCreateDlg)

public:
	CErcCreateDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CErcCreateDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_ERC_CREATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int	m_lRadioID;
	COleDateTime m_DateStart;
	COleDateTime m_DateFinish;
	CString m_strFolder;

	CListCtrl m_cList;
	virtual BOOL OnInitDialog();
	CButton m_cOK;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CString CleanString(CString);
};
