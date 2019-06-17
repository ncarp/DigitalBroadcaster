#if !defined(AFX_JINGLESONAIRLEFTVIEW_H__98A18D12_8C46_4BC4_BC15_B7858B458EC7__INCLUDED_)
#define AFX_JINGLESONAIRLEFTVIEW_H__98A18D12_8C46_4BC4_BC15_B7858B458EC7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// JinglesOnAirLeftView.h : header file
//
#include "..\include\DigitalLeftView.h"
/////////////////////////////////////////////////////////////////////////////
// CJinglesOnAirLeftView view

class CJinglesOnAirLeftView : public CDigitalLeftView
{
protected:
	CJinglesOnAirLeftView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CJinglesOnAirLeftView)

public:
	CString		m_strRadio,
				m_strConnect,
				m_strDB;
	long		m_lRadioID;

// Operations
public:
	static	UINT	RefreshList(LPVOID lp);
	virtual	void	OnDoubleClick();
	virtual void	OnSelChange();
			void	OnCut();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJinglesOnAirLeftView)
	public:
	virtual void OnInitialUpdate();
	virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual BOOL OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CJinglesOnAirLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CJinglesOnAirLeftView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JINGLESONAIRLEFTVIEW_H__98A18D12_8C46_4BC4_BC15_B7858B458EC7__INCLUDED_)
