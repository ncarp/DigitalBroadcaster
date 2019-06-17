#if !defined(AFX_USERDLG_H__154D1E49_B773_4A2F_86EE_EBFE0A3893FC__INCLUDED_)
#define AFX_USERDLG_H__154D1E49_B773_4A2F_86EE_EBFE0A3893FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UserDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUserDlg dialog

class CUserDlg : public CDialog
{
// Construction
public:
	CUserDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUserDlg)
	enum { IDD = IDD_SYSTEMUSER };
	CButton	m_cInstrumentals;
	CButton	m_cTextOnAir;
	CButton	m_cTextAdd;
	CButton	m_cTextLineup;
	CButton	m_cTextEdit;
	CButton	m_cTextCut;
	CButton	m_cRmsOnAir;
	CButton	m_cRmsLineup;
	CButton	m_cRmsEdit;
	CButton	m_cRmsCut;
	CButton	m_cRmsAdd;
	CButton	m_cScheduleAuto;
	CButton	m_cVoiceEdit;
	CButton	m_cVoiceCut;
	CButton	m_cVoiceAdd;
	CButton	m_cLineupEdit;
	CButton	m_cLineupCut;
	CButton	m_cLineupAdd;
	CButton	m_cScheduleEdit;
	CButton	m_cCriteriaEdit;
	CButton	m_cCriteriaCut;
	CButton	m_cCriteriaAdd;
	CButton	m_cTrafficView;
	CButton	m_cTrafficEdit;
	CButton	m_cTrafficCut;
	CButton	m_cTrafficAdd;
	CButton	m_cSponsors;
	CButton	m_cSpotsCut;
	CButton	m_cSpotsEdit;
	CButton	m_cSpotsAdd;
	CButton	m_cPlayListEditContents;
	CButton	m_cPlayListEdit;
	CButton	m_cPlayListCut;
	CButton	m_cPlayListAdd;
	CButton	m_cBlocksEdit;
	CButton	m_cBlocksCut;
	CButton	m_cBlocksAdd;
	CButton	m_cJinglesEdit;
	CButton	m_cJinglesNew;
	CButton	m_cJinglesOnAir;
	CButton	m_cJinglesCut;
	CButton	m_cDiscography;
	CButton	m_cNewMusic;
	CButton	m_cEditMusic;
	CButton	m_cDeleteMusic;
	BOOL	m_bDeleteMusic;
	BOOL	m_bDiscography;
	BOOL	m_bEditMusic;
	BOOL	m_bNewMusic;
	CString	m_strName;
	BOOL	m_bJinglesCut;
	BOOL	m_bJinglesOnAir;
	BOOL	m_bJinglesNew;
	BOOL	m_bJinglesEdit;
	BOOL	m_bOnAirManagement;
	BOOL	m_bBlocksAdd;
	BOOL	m_bBlocksCut;
	BOOL	m_bBlocksEdit;
	BOOL	m_bPlayListAdd;
	BOOL	m_bPlayListCut;
	BOOL	m_bPlayListEditContents;
	BOOL	m_bPlayListEdit;
	BOOL	m_bTraffic;
	BOOL	m_bSpotsAdd;
	BOOL	m_bSpotsEdit;
	BOOL	m_bSpotsCut;
	BOOL	m_bSponsors;
	BOOL	m_bTrafficAdd;
	BOOL	m_bTrafficCut;
	BOOL	m_bTrafficEdit;
	BOOL	m_bTrafficView;
	BOOL	m_bCriteriaAdd;
	BOOL	m_bCriteriaCut;
	BOOL	m_bCriteriaEdit;
	BOOL	m_bScheduleAuto;
	BOOL	m_bScheduleEdit;
	BOOL	m_bLineupAdd;
	BOOL	m_bLineupCut;
	BOOL	m_bLineupEdit;
	BOOL	m_bScheduler;
	BOOL	m_bVoiceAdd;
	BOOL	m_bVoiceCut;
	BOOL	m_bVoiceEdit;
	BOOL	m_bNewsRoom;
	BOOL	m_bRmsAdd;
	BOOL	m_bRmsCut;
	BOOL	m_bRmsLineup;
	BOOL	m_bRmsOnAir;
	BOOL	m_bTextCut;
	BOOL	m_bTextEdit;
	BOOL	m_bTextLineup;
	BOOL	m_bTextAdd;
	BOOL	m_bTextOnAir;
	BOOL	m_bRmsEdit;
	BOOL	m_bManagerLog;
	BOOL	m_bManagerFolder;
	BOOL	m_bManagerTime;
	BOOL	m_bManagerUser;
	BOOL	m_bInstrumentals;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUserDlg)
	afx_msg void OnDiscography();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnOnairmanagment();
	afx_msg void OnTraffic();
	afx_msg void OnScheduler();
	afx_msg void OnNewsroom();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERDLG_H__154D1E49_B773_4A2F_86EE_EBFE0A3893FC__INCLUDED_)
