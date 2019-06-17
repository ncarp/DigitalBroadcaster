#if !defined(AFX_SCHEDULESPOTS_H__7C24BCE6_7412_4C62_B30A_44CB7B2F8F35__INCLUDED_)
#define AFX_SCHEDULESPOTS_H__7C24BCE6_7412_4C62_B30A_44CB7B2F8F35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScheduleSpots.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CScheduleSpots dialog
typedef struct
{
	long ID;
	COleDateTime StartingDate;
	COleDateTime EndingDate;
	BOOL Days[7];
} typeSpotDetail;

class CScheduleSpots : public CPropertyPage
{
	DECLARE_DYNCREATE(CScheduleSpots)

// Construction
public:
	CScheduleSpots();
	~CScheduleSpots();

// Dialog Data
	//{{AFX_DATA(CScheduleSpots)
	enum { IDD = IDD_SCHEDULE_SPOTS };
	CListCtrl	m_cSpots;
	CListCtrl	m_cSelected;
	//}}AFX_DATA

public:
	void CheckData();
	BOOL			m_bIsNew;
	long			m_lCustomerID,
					m_lScheduleID;
	COleDateTime	m_dStartingDate,
					m_dEndingDate;
	int				m_nSpots;
	typeSpotDetail	*m_Spots[100];

	void FillSpotsList();
// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CScheduleSpots)
	public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CScheduleSpots)
	afx_msg void OnRemove();
	afx_msg void OnMoveUp();
	afx_msg void OnMoveDown();
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkSpots(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkSelected(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCHEDULESPOTS_H__7C24BCE6_7412_4C62_B30A_44CB7B2F8F35__INCLUDED_)
