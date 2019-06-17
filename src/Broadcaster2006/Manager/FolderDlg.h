#pragma once


// CFolderDlg

class CFolderDlg : public CFileDialog
{
	DECLARE_DYNAMIC(CFolderDlg)

public:
	CFolderDlg(BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL);
	virtual ~CFolderDlg();

protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnFileNameOK();
	virtual void OnOK();
};


