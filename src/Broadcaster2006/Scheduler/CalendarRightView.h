#if !defined(AFX_CALENDARRIGHTVIEW_H__9A18B65A_58B4_4300_8CF0_CAA86B1CD418__INCLUDED_)
#define AFX_CALENDARRIGHTVIEW_H__9A18B65A_58B4_4300_8CF0_CAA86B1CD418__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CalendarRightView.h : header file
//
#include "..\OnAir\OnAirDefines.h"
#include "CopySchedule.h"

/////////////////////////////////////////////////////////////////////////////
// CCalendarRightView view

typedef struct
{
	long			lTemplateID,
					lScheduleID;
	COleDateTime	Start;
	WORD			wMode;
	CWnd			*pView;
} typeCopyScheduleData;

class CCalendarRightView : public CListView
{
protected:
	CCalendarRightView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CCalendarRightView)

// Attributes
public:
	CString	m_strConnect,
			m_strDB;
	CPoint	m_OldPoint;
	int		m_Year,
			m_Month,
			m_Day;
	long	m_lRadioID;
	BOOL	m_bWorking;
	typeTreeDrag *m_lpDragItem;
// Operations
public:
	void OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult);
	void SetYear( int year );
	void SetMonth( int year,int month);
	void SetDay(int year,int month, int day);
	void SetSchedule( long lID );
	void OnPFL();
	void OnInfo();
	virtual void GenerateSchedule(typeCopySchedule *lpData);
	
	static UINT GenerateScheduleThread( LPVOID lp);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalendarRightView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CCalendarRightView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CCalendarRightView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRdblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALENDARRIGHTVIEW_H__9A18B65A_58B4_4300_8CF0_CAA86B1CD418__INCLUDED_)
