#if !defined(AFX_SCHEDULEBLOCKS_H__51E17AD3_8DF7_4BE7_B2F1_777B94B6C228__INCLUDED_)
#define AFX_SCHEDULEBLOCKS_H__51E17AD3_8DF7_4BE7_B2F1_777B94B6C228__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScheduleBlocks.h : header file
//

typedef struct {
	long			ID,
					Position;
	BOOL			Days[7];
	COleDateTime	StartingDate,
					EndingDate;
	COleDateTimeSpan TimeOffset;
} typeBlockDetail;

/////////////////////////////////////////////////////////////////////////////
// CScheduleBlocks dialog

class CScheduleBlocks : public CPropertyPage
{
	DECLARE_DYNCREATE(CScheduleBlocks)

public:
	typeBlockDetail *m_blocks[200];
	BOOL			m_bIsNew,
					m_bIsWorking;
	long			m_nBlocks,
					m_lScheduleID,
					m_lStationID;
	CString			m_strConnect;
	COleDateTime	m_dInicialDate,
					m_dEndingDate;

	
// Construction
public:
	CScheduleBlocks();
	~CScheduleBlocks();

	static	UINT FillBlocksList(LPVOID lp);
	void	CheckData();
	
// Dialog Data
	//{{AFX_DATA(CScheduleBlocks)
	enum { IDD = IDD_SCHEDULE_BLOCKS };
	CListCtrl	m_cSelected;
	CListCtrl	m_cBlocks;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CScheduleBlocks)
	public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	virtual BOOL OnWizardFinish();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CScheduleBlocks)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkBlocks(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRemove();
	afx_msg void OnDblclkSelected(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCHEDULEBLOCKS_H__51E17AD3_8DF7_4BE7_B2F1_777B94B6C228__INCLUDED_)
