#pragma once
#include "afxwin.h"


// CSplitterConfigDlg dialog

typedef struct {
	DWORD	dwMixerID;
	DWORD	dwLineID;
}typeMixerLine;

class CSplitterConfigDlg : public CDialog
{
	DECLARE_DYNAMIC(CSplitterConfigDlg)

public:
	
	CSplitterConfigDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSplitterConfigDlg();

// Dialog Data
	enum { IDD = IDD_CONFIG };
	typeMixerLine	m_Mixer;
	CString			m_strAudioOut,
					m_strConnect,
					m_strRadioName;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	static	BOOL CALLBACK DSEnumCallback(LPGUID lpGuid, LPCSTR lpcstrDescription, LPCSTR lpcstrModule, LPVOID lpContext);
			void GetLineIns();
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox m_cRadio;
	CComboBox m_cAudio;
	CComboBox m_cLine;
	afx_msg void OnBnClickedOk();
	BOOL m_bLine;
};
