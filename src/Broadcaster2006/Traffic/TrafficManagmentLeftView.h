#if !defined(AFX_TRAFFICMANAGMENTLEFTVIEW_H__C72782DA_4F32_4CFB_A932_279740F0C762__INCLUDED_)
#define AFX_TRAFFICMANAGMENTLEFTVIEW_H__C72782DA_4F32_4CFB_A932_279740F0C762__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TrafficManagmentLeftView.h : header file
//
#include "..\include\DigitalLeftView.h"

/////////////////////////////////////////////////////////////////////////////
// CTrafficManagmentLeftView view

class CTrafficManagmentLeftView : public CDigitalLeftView
{
protected:
	CTrafficManagmentLeftView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CTrafficManagmentLeftView)

// Attributes
public:
	BOOL	m_bIsRefreshing;

// Operations
public:
	static	UINT	RefreshList(LPVOID lp);
			void	OnSelChange();	
			void	OnDoubleClick();
			void	EditCustomer();
			void	EditSchedule();
			void	NewSchedule();
			void	NewSpot();
			void	EditSpot();
			void	OnCut();
			void	CutSpot();
			void	CutCustomer();
			void	CutSchedule();
			void	PFL();
	virtual void	OnRDoubleClick();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrafficManagmentLeftView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CTrafficManagmentLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CTrafficManagmentLeftView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRAFFICMANAGMENTLEFTVIEW_H__C72782DA_4F32_4CFB_A932_279740F0C762__INCLUDED_)
