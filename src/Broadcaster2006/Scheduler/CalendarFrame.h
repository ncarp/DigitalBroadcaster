#if !defined(AFX_CALENDARFRAME_H__AACC0AEA_BE5A_46D8_B1A4_F9771CA39545__INCLUDED_)
#define AFX_CALENDARFRAME_H__AACC0AEA_BE5A_46D8_B1A4_F9771CA39545__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CalendarFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCalendarFrame frame

class CCalendarFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CCalendarFrame)
protected:
	CCalendarFrame();           // protected constructor used by dynamic creation

// Attributes
public:
	CSplitterWnd	m_wndSplitter;
	CToolBarCtrl	m_wndToolBar;
	CReBar			m_wndReBar;

// Operations
public:
	void	OnNew();
	void	OnEditHeadline();
	void	OnEditSchedule();
	void	OnCut();
	void	OnPFL();
	void	OnInfo();
	void	OnStatistics();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalendarFrame)
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CCalendarFrame();

	// Generated message map functions
	//{{AFX_MSG(CCalendarFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALENDARFRAME_H__AACC0AEA_BE5A_46D8_B1A4_F9771CA39545__INCLUDED_)
