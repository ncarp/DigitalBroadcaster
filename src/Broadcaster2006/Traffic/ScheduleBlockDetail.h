#if !defined(AFX_SCHEDULEBLOCKDETAIL_H__2C188C96_DA8F_4BDE_9C6D_3FB99EB8768C__INCLUDED_)
#define AFX_SCHEDULEBLOCKDETAIL_H__2C188C96_DA8F_4BDE_9C6D_3FB99EB8768C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScheduleBlockDetail.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CScheduleBlockDetail dialog

class CScheduleBlockDetail : public CDialog
{
// Construction
public:
	CScheduleBlockDetail(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CScheduleBlockDetail)
	enum { IDD = IDD_SCHEDULE_CLOCKS_DETAIL };
	CButton	m_cWed;
	CButton	m_cTue;
	CButton	m_cThu;
	CButton	m_cSun;
	CButton	m_cSat;
	CButton	m_cMon;
	CButton	m_cFri;
	CDateTimeCtrl	m_cEndingDate;
	CTreeCtrl	m_cTree;
	COleDateTime	m_dEndingDate;
	BOOL	m_bFri;
	BOOL	m_bMon;
	CString	m_strName;
	BOOL	m_bSat;
	COleDateTime	m_dStartingDate;
	BOOL	m_bSun;
	BOOL	m_bThu;
	BOOL	m_bTue;
	BOOL	m_bWed;
	//}}AFX_DATA

	long			m_lBlockID,
					m_lPosition;
	COleDateTime	m_dDate;
	COleDateTimeSpan m_TimeOffset;
	CString			m_strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScheduleBlockDetail)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void GetBlock();
	// Generated message map functions
	//{{AFX_MSG(CScheduleBlockDetail)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDatetimechangeStartingdate(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDatetimechangeEndingdate(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusStartingdate(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusEndingdate(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCHEDULEBLOCKDETAIL_H__2C188C96_DA8F_4BDE_9C6D_3FB99EB8768C__INCLUDED_)
