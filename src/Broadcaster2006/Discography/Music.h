#if !defined(AFX_MUSIC_H__D3E1E305_E4AF_44E9_B2AC_92269189B686__INCLUDED_)
#define AFX_MUSIC_H__D3E1E305_E4AF_44E9_B2AC_92269189B686__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Music.h : header file
//
#include "..\OnAir\Recorder.h"
/////////////////////////////////////////////////////////////////////////////
// CMusic dialog

class CMusic : public CDialog
{
// Construction
public:
	CMusic(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMusic();

	CRecorder	*m_pTimers;
	int			m_nPos;
	BOOL		m_bIsNew;
	CString		m_strFileName,
				m_strPath,
				m_strFileType;
	long		m_SongID,
				m_ArtistID,
				m_CategoryID,
				m_ExpressionID,
				m_CDID,
				m_LabelID,
				m_PathID,
				m_Start,
				m_Intro,
				m_FadeIn,
				m_FadeOut,
				m_Mix,
				m_End,
				m_LoopA,
				m_LoopB;

// Dialog Data
	//{{AFX_DATA(CMusic)
	enum { IDD = IDD_MUSIC };
	CComboBox	m_cLabel;
	CComboBox	m_cCD;
	CEdit	m_cRythmV;
	CSliderCtrl	m_cRythm;
	CComboBox	m_cExpression;
	CComboBox	m_cType;
	CEdit	m_cTitle;
	CComboBox	m_cArtist;
	CButton	m_cCancel;
	CButton	m_cOK;
	CString	m_strArtist;
	CString	m_strTitle;
	CString	m_strType;
	CString	m_strExpression;
	int		m_Rythm;
	CString	m_strCD;
	CString	m_strComposer;
	COleDateTime	m_dDate;
	CString	m_strLabel;
	CString	m_strLirycs;
	CString	m_strMusicians;
	CString	m_strProducer;
	CString	m_strRemarcks;
	CString	m_strStudio;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMusic)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMusic)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnKillfocusType();
	afx_msg void OnSelchangeType();
	afx_msg void OnKillfocusExpression();
	afx_msg void OnSelchangeExpression();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnKillfocusCd();
	afx_msg void OnSelchangeCd();
	afx_msg void OnKillfocusLabel();
	afx_msg void OnSelchangeLabel();
	virtual void OnOK();
	afx_msg void OnSelchangeArtist();
	afx_msg void OnKillfocusArtist();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MUSIC_H__D3E1E305_E4AF_44E9_B2AC_92269189B686__INCLUDED_)
