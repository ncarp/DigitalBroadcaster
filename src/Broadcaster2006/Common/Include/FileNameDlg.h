#pragma once
#include "afxwin.h"


// CFileNameDlg dialog

class CFileNameDlg : public CDialog
{
	DECLARE_DYNAMIC(CFileNameDlg)

public:
	CFileNameDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFileNameDlg();

// Dialog Data
	enum { IDD = IDD_RENAMEFILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cFileName;
	CString m_strFileName;
	CString m_strPath;
	CString m_strType;
	virtual BOOL OnInitDialog();
};
