// AudioCheckerDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "..\common\include\audiostream.h"

// CAudioCheckerDlg dialog
class CAudioCheckerDlg : public CDialog
{
// Construction
public:
	CAudioCheckerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_AUDIOCHECKER_DIALOG };

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
	CButton m_cMusic;
	BOOL m_bMusic;
	CButton m_cJingles;
	BOOL m_bJingles;
	BOOL m_bSpots;
	CButton m_cSpots;
	CProgressCtrl m_cProgressFile;
	CProgressCtrl m_cProgressTotal;
	CEdit m_cPath;
	CEdit m_cFile;
	CEdit m_cDatabase;
	long int m_lLastMusicID;
	long int m_lLastMusicIncomplete;
	CAudioStream *m_pSound;
	BOOL m_bChecking;
	long int m_lLastJingleID;
	long int m_lLastSpotID;
	long int m_lLastRMID;

protected:
	virtual void OnOK();
public:
	void CheckMusicFiles(void);
	LPDIRECTSOUND InitializeDirectSound(LPGUID lpguid);
protected:
	virtual void OnCancel();
public:
	CButton m_cOK;
	CButton m_cCancel;
	void CheckJingleFiles(void);
	void CheckSpotFiles(void);
	CButton m_cRMs;
	BOOL m_bRMs;
	void CheckRMFiles(void);
	BOOL m_bDecompress;
};
