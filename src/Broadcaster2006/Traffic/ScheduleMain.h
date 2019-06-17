#if !defined(AFX_SCHEDULEMAIN_H__EC5F2C00_11CC_43CC_AA59_0ED6FFBD6D04__INCLUDED_)
#define AFX_SCHEDULEMAIN_H__EC5F2C00_11CC_43CC_AA59_0ED6FFBD6D04__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScheduleMain.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CScheduleMain dialog

class CScheduleMain : public CPropertyPage
{
	DECLARE_DYNCREATE(CScheduleMain)

// Construction
public:
	CScheduleMain();
	~CScheduleMain();

// Dialog Data
	//{{AFX_DATA(CScheduleMain)
	enum { IDD = IDD_SCHEDULE_MAIN };
	CDateTimeCtrl	m_cStartingHour;
	CDateTimeCtrl	m_cStartingDate;
	CComboBox	m_cRadioStation;
	CEdit	m_cNumber;
	CDateTimeCtrl	m_cFinalHour;
	CDateTimeCtrl	m_cEndingDate;
	CComboBox	m_cCustomer;
	COleDateTime	m_dEndingDate;
	COleDateTime	m_dFinalHour;
	int		m_iNumber;
	COleDateTime	m_dStartingDate;
	float	m_fValue;
	COleDateTime	m_dStartingHour;
	//}}AFX_DATA
	
	CString m_strCustomer,
			m_strStation;
	long	m_lCustomerID,
			m_lStationID,
			m_lScheduleID;
	BOOL	m_bIsNew,
			m_bByNumber,
			m_bTotalValue;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CScheduleMain)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	void	CheckData();

protected:
	// Generated message map functions
	//{{AFX_MSG(CScheduleMain)
	virtual BOOL OnInitDialog();
	afx_msg void OnKillfocusCustomer();
	afx_msg void OnKillfocusNotify(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSetfocusNotify(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBynumber();
	afx_msg void OnBydate();
	afx_msg void OnKillfocusRadiostation();
	afx_msg void OnCheckData();
	afx_msg void OnByinsert();
	afx_msg void OnBycontract();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CString m_strPI;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCHEDULEMAIN_H__EC5F2C00_11CC_43CC_AA59_0ED6FFBD6D04__INCLUDED_)
