#if !defined(AFX_SPONSORSLEFTVIEW_H__D415ACC2_C2C2_49E1_9172_092DED8D3E01__INCLUDED_)
#define AFX_SPONSORSLEFTVIEW_H__D415ACC2_C2C2_49E1_9172_092DED8D3E01__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SponsorsLeftView.h : header file
//
#include "..\include\DigitalLeftView.h"

/////////////////////////////////////////////////////////////////////////////
// CSponsorsLeftView view

class CSponsorsLeftView : public CDigitalLeftView
{
protected:
	CSponsorsLeftView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CSponsorsLeftView)

// Attributes
public:
	CString		m_strConnect,
				m_strRadio,
				m_strDB;
	BOOL		m_bIsRefreshing;
	long		m_lRadioID;
// Operations
public:
	virtual void	OnDoubleClick();
	virtual void	OnSelChange();
	static UINT		RefreshList(LPVOID lp);
			void	CutSponsor();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSponsorsLeftView)
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
	virtual ~CSponsorsLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CSponsorsLeftView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPONSORSLEFTVIEW_H__D415ACC2_C2C2_49E1_9172_092DED8D3E01__INCLUDED_)
