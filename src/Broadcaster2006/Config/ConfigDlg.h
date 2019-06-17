// ConfigDlg.h : header file
//

#include "afxwin.h"
#if !defined(AFX_CONFIGDLG_H__E47865AC_3A0D_410A_91D4_7F63BCF83729__INCLUDED_)
#define AFX_CONFIGDLG_H__E47865AC_3A0D_410A_91D4_7F63BCF83729__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg dialog
typedef struct {
	DWORD	dwMixerID;
	DWORD	dwLineID;
}typeMixerLine;

class CConfigDlg : public CPropertyPage
{
// Construction
public:
	static BOOL CALLBACK DSEnumCallback(LPGUID lpGuid,LPCSTR lpcstrDescription, LPCSTR lpcstrModule, LPVOID lpContext);
	static BOOL CALLBACK DSEnumCaptureCallback(LPGUID lpGuid,LPCSTR lpcstrDescription, LPCSTR lpcstrModule, LPVOID lpContext);
	static BOOL CALLBACK acmDriverEnumCallback(	HACMDRIVERID hadid, DWORD dwInstance, DWORD fdwSupport );
	static BOOL CALLBACK acmFormatEnumCallback( HACMDRIVERID hadid, LPACMFORMATDETAILS pafd, DWORD dwInstance, DWORD fdwSupport );


	CConfigDlg(CWnd* pParent = NULL);	// standard constructor

	CString			m_strWaveFormat,
					m_strWaveParam;
	LPWAVEFORMATEX	pwfx;

// Dialog Data
	//{{AFX_DATA(CConfigDlg)
	enum { IDD = IDD_CONFIG_DIALOG };
	CEdit	m_cInstV;
	CSliderCtrl	m_cInstr;
	CSliderCtrl	m_cDelay;
	CEdit	m_cDelayV;
	CSliderCtrl	m_cSlow;
	CSliderCtrl	m_cAvg;
	CEdit	m_cSlowAvgV;
	CSliderCtrl	m_cSlowAvg;
	CEdit	m_cSlowV;
	CEdit	m_cAvgV;
	CComboBox	m_cParam;
	CComboBox	m_cFormat;
	CSliderCtrl	m_ctrlOnIntro;
	CSliderCtrl	m_ctrlFadeToTake;
	CComboBox	m_Takes;
	CComboBox	m_Cartwall;
	CComboBox	m_Monicao;
	CComboBox	m_Musica;
	CString	m_strMusica;
	CString	m_strMonicao;
	CString	m_strCartwall;
	CString	m_strTakes;
	CString	m_strURL;
	int		m_iFateToTake;
	int		m_iOnIntro;
	CString	m_strTempDir;
	int		m_Valor2;
	int		m_Valor1;
	int		m_iAvg;
	int		m_iSlow;
	int		m_iSlowAvg;
	int		m_iDelay;
	int		m_iInstr;
	long	m_bMixer;
	long	m_lMixerID;
	long	m_lMixerLineID;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigDlg)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CConfigDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSelchangeFormat();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cMixer;
	CComboBox m_cMixerLine;
protected:
	bool AddMixers(void);
public:
	CString m_strMixer;
	afx_msg void OnCbnSelchangeAudiomusica();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGDLG_H__E47865AC_3A0D_410A_91D4_7F63BCF83729__INCLUDED_)
