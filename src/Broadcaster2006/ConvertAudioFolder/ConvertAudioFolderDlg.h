// ConvertAudioFolderDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CConvertAudioFolderDlg dialog
class CConvertAudioFolderDlg : public CDialog
{
// Construction
public:
	CConvertAudioFolderDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CONVERTAUDIOFOLDER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	BOOL ConvertAudioFile(CString strOrigin, CString strDestination);
	CString m_strBitrate;
	BOOL m_bDelete;
	BOOL m_bOverwrite;
	BOOL m_bLowercase;
	CProgressCtrl m_cProgress;
	CEdit m_cSource;
	CString m_strSource;
	afx_msg void OnBnClickedOk();
	CEdit m_cDestination;
	CString m_strDestination;
	CStatic m_cFileName;
	CString FileName2LowerCase(CString str);
	CStatic m_cCodec;
	CStatic m_cSampleRate;
	CStatic m_cBitRate;
};
