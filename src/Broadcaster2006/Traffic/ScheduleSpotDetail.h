#if !defined(AFX_SCHEDULESPOTDETAIL_H__E93A045F_CE6D_433C_8148_A023438CA048__INCLUDED_)
#define AFX_SCHEDULESPOTDETAIL_H__E93A045F_CE6D_433C_8148_A023438CA048__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScheduleSpotDetail.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CScheduleSpotDetail dialog

class CScheduleSpotDetail : public CDialog
{
// Construction
public:
	CScheduleSpotDetail(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CScheduleSpotDetail)
	enum { IDD = IDD_SCHEDULE_SPOTS_DETAIL };
	CDateTimeCtrl	m_cStartingDate;
	CDateTimeCtrl	m_cEndingDate;
	CString	m_strName;
	BOOL	m_bSat;
	COleDateTime	m_dEndingDate;
	BOOL	m_bFri;
	BOOL	m_bMon;
	COleDateTime	m_dStartingDate;
	BOOL	m_bSun;
	BOOL	m_bThu;
	BOOL	m_bTue;
	BOOL	m_bWed;
	//}}AFX_DATA

	COleDateTime	m_dStartingLimit,
					m_dEndingLimit;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScheduleSpotDetail)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CScheduleSpotDetail)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCHEDULESPOTDETAIL_H__E93A045F_CE6D_433C_8148_A023438CA048__INCLUDED_)
