// FolderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Manager.h"
#include "FolderDlg.h"


// CFolderDlg

IMPLEMENT_DYNAMIC(CFolderDlg, CFileDialog)

CFolderDlg::CFolderDlg(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
		DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd) :
		CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{

}

CFolderDlg::~CFolderDlg()
{
}


BEGIN_MESSAGE_MAP(CFolderDlg, CFileDialog)
END_MESSAGE_MAP()



// CFolderDlg message handlers



BOOL CFolderDlg::OnFileNameOK()
{
	// TODO: Add your specialized code here and/or call the base class

	return 0;
}

void CFolderDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::OnOK();
}
