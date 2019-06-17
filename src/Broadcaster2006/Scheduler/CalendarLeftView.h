#if !defined(AFX_CALENDARLEFTVIEW_H__2B997E10_DDFE_4EA2_8F87_9493050082DB__INCLUDED_)
#define AFX_CALENDARLEFTVIEW_H__2B997E10_DDFE_4EA2_8F87_9493050082DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CalendarLeftView.h : header file
//
#include "..\include\DigitalLeftView.h"
#include "CalendarRightView.h"

/////////////////////////////////////////////////////////////////////////////
// CCalendarLeftView view

class CCalendarLeftView : public CDigitalLeftView
{
protected:
	CCalendarLeftView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CCalendarLeftView)

// Attributes
public:
	CString	m_strConnect,
			m_strRadio,
			m_strDB;
	long	m_lRadioID;
	CCalendarRightView *m_pRightView;

// Operations
public:
	virtual void OnInfo();
	virtual void OnExpanding( HTREEITEM hItem );
	virtual void OnSelChange();
	virtual void OnNew();
	virtual void OnEditHeadline();
	virtual void OnEditSchedule();
	virtual void OnCut();
	virtual void OnDoubleClick();
	virtual void CopySchedule( HTREEITEM hItem );
	virtual void CopyDay( typeCopySchedule *lpData );
	virtual BOOL CheckForConflict(COleDateTime Start,COleDateTime End);
	static UINT CopyDayThread(LPVOID lp);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalendarLeftView)
	public:
	virtual void OnInitialUpdate();
	virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual void OnDragLeave();
	virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual BOOL OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CCalendarLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CCalendarLeftView)
	afx_msg void OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult);
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALENDARLEFTVIEW_H__2B997E10_DDFE_4EA2_8F87_9493050082DB__INCLUDED_)
