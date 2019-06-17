#if !defined(AFX_PRODUCERSCHEDULER_H__2950492E_1375_45F1_9FDC_E3C2B04C6513__INCLUDED_)
#define AFX_PRODUCERSCHEDULER_H__2950492E_1375_45F1_9FDC_E3C2B04C6513__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProducerScheduler.h : header file
//
#include "OnAirDefines.h"
#include "typeLineUpItem.h"
#include "OnAirListBox.h"
#include "SchedulerListBox.h"

/////////////////////////////////////////////////////////////////////////////
// CProducerScheduler frame

class CProducerScheduler : public CFrameWnd
{
	DECLARE_DYNCREATE(CProducerScheduler)

public:
	CProducerScheduler();           // protected constructor used by dynamic creation

// Attributes
public:
	CDateTimeCtrl	*m_pDate;
	CHeaderCtrl		*m_pHeader;
	CReBar			*m_pRebar;
	CToolBarCtrl	*m_pToolBar;
	COnAirListBox	*m_pList;
	CSchedulerListBox *m_pSchedule;
	long			m_ScheduleID;
	typeLineUpItem	*m_Blocks[100];
	int				m_nBlocks;
	COleDateTime	m_StartingTime;
	COleDateTime	m_EndingTime;
	DWORD64			m_qwStart;
	int				m_Year,m_Month,m_Day;
protected:
	CString			m_strPrevDate;

// Operations
public:
	void OnChangeDate();
	void OnRefresh();
	void OnNew();
	void OnEdit();
	void OnEditSchedule();
	void GetScheduleBlocks();
	void InsertBlocks();
	void RemoveBlocks();
	void SaveLineUp();
	void OnExit();
	void OnLock();
	void OnRemove();
	void OnPFL();

	static UINT SetSchedule(LPVOID lp);
	LRESULT OnDrop( WPARAM,LPARAM );
	LRESULT OnScheduleDoubleClick(WPARAM,LPARAM);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProducerScheduler)
	protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CProducerScheduler();

	// Generated message map functions
	//{{AFX_MSG(CProducerScheduler)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRODUCERSCHEDULER_H__2950492E_1375_45F1_9FDC_E3C2B04C6513__INCLUDED_)
