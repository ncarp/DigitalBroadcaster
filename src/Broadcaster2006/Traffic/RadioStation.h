#if !defined(AFX_RADIOSTATION_H__2FFB6E0D_872A_4D23_825F_8F133AB1F66E__INCLUDED_)
#define AFX_RADIOSTATION_H__2FFB6E0D_872A_4D23_825F_8F133AB1F66E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RadioStation.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRadioStation dialog

class CRadioStation : public CDialog
{
// Construction
public:
	CRadioStation(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRadioStation)
	enum { IDD = IDD_RADIOSTATION };
	CListBox	m_cRadios;
	//}}AFX_DATA

	CString	m_strConnect,
			m_strRadio,
			m_strDB;
	long	m_lRadioID;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRadioStation)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRadioStation)
	virtual void OnOK();
	afx_msg void OnDblclkList2();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RADIOSTATION_H__2FFB6E0D_872A_4D23_825F_8F133AB1F66E__INCLUDED_)
