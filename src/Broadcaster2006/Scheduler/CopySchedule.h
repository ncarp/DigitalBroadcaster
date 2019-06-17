#if !defined(AFX_COPYSCHEDULE_H__30B3D2E5_E000_4E9D_9543_D32A0EE81BF8__INCLUDED_)
#define AFX_COPYSCHEDULE_H__30B3D2E5_E000_4E9D_9543_D32A0EE81BF8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CopySchedule.h : header file
//

typedef struct {
	CString strDBName,
			strDSN;
	long	lScheduleID;
}typeCopyScheduleRadio;

typedef struct {
	BOOL	bMusic,
			bNewMusic,
			bSameMusic,
			bJingles,
			bSameJingles,
			bNewJingles,
			bVoice,
			bNewVoice,
			bSameVoice,
			bOthers,
			bBlocked,
			bCopyAll;
	long	lScheduleID,
			lTemplateID,
			lRadioID;
	COleDateTime	dtStart;
	CWnd			*wndView;
	HTREEITEM		hItem;
	int		nRadios;
	typeCopyScheduleRadio tRadios[99];
} typeCopySchedule;

/////////////////////////////////////////////////////////////////////////////
// CCopySchedule dialog

class CCopySchedule : public CDialog
{
// Construction
public:
	typeCopySchedule m_Data;

	CCopySchedule(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCopySchedule)
	enum { IDD = IDD_COPYSCHEDULE };
	CButton	m_cNewVoice;
	CButton	m_cSameVoice;
	CButton	m_cNewJingles;
	CButton	m_cSameJingles;
	CButton	m_cSameMusic;
	CButton	m_cNewMusic;
	CButton m_cCopyAll;
	BOOL	m_bJingles;
	BOOL	m_bMusic;
	BOOL	m_bOther;
	BOOL	m_bVoice;
	BOOL	m_bCopyAll;
	//}}AFX_DATA

	int	m_Copy;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCopySchedule)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCopySchedule)
	virtual void OnOK();
	afx_msg void OnMusic();
	virtual BOOL OnInitDialog();
	afx_msg void OnNewmusic();
	afx_msg void OnSamemusic();
	afx_msg void OnJingles();
	afx_msg void OnVoice();
	afx_msg void OnNewjingle();
	afx_msg void OnSamejingle();
	afx_msg void OnNewvoice();
	afx_msg void OnSamevoice();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:

	BOOL m_bBlocked;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COPYSCHEDULE_H__30B3D2E5_E000_4E9D_9543_D32A0EE81BF8__INCLUDED_)
