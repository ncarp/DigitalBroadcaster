#if !defined(AFX_SCHEDULE_H__BAA355B1_168E_4C4F_9DB8_777BA9FF89FA__INCLUDED_)
#define AFX_SCHEDULE_H__BAA355B1_168E_4C4F_9DB8_777BA9FF89FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Schedule.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Schedule dialog

class Schedule : public CDialog
{
// Construction
public:
	Schedule(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Schedule)
	enum { IDD = IDD_SCHEDULE };
	COleDateTime	m_EndingDate;
	COleDateTime	m_Length;
	CString	m_Name;
	int		m_Precision;
	COleDateTime	m_StartingTime;
	//}}AFX_DATA

	int m_Year,
		m_Month,
		m_Day;

	void ComputeEndingTime();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Schedule)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Schedule)
	afx_msg void OnDatetimechangeStartingtime(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusStartingtime(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDatetimechangeLength(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusLength(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCHEDULE_H__BAA355B1_168E_4C4F_9DB8_777BA9FF89FA__INCLUDED_)
