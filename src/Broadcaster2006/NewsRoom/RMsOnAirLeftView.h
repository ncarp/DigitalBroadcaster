#if !defined(AFX_RMSONAIRLEFTVIEW_H__479E2941_D988_4126_AE8E_5A1EF6E0AC1E__INCLUDED_)
#define AFX_RMSONAIRLEFTVIEW_H__479E2941_D988_4126_AE8E_5A1EF6E0AC1E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RMsOnAirLeftView.h : header file
//
#include "..\include\DigitalLeftView.h"

/////////////////////////////////////////////////////////////////////////////
// CRMsOnAirLeftView view

class CRMsOnAirLeftView : public CDigitalLeftView
{
protected:
	CRMsOnAirLeftView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CRMsOnAirLeftView)

// Attributes
public:
	CString		m_strRadio,
				m_strConnect,
				m_strDB;
// Operations
public:
	static	UINT	RefreshList(LPVOID lp);
	virtual	void	OnDoubleClick();
	virtual void	OnSelChange();
			void	OnCut();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRMsOnAirLeftView)
	public:
	virtual void OnInitialUpdate();
	virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual BOOL OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CRMsOnAirLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CRMsOnAirLeftView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RMSONAIRLEFTVIEW_H__479E2941_D988_4126_AE8E_5A1EF6E0AC1E__INCLUDED_)
