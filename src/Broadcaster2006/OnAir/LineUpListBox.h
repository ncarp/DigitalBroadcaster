#if !defined(AFX_LINEUPLISTBOX_H__8909E40A_EA30_4262_B91B_733D17CD9F68__INCLUDED_)
#define AFX_LINEUPLISTBOX_H__8909E40A_EA30_4262_B91B_733D17CD9F68__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LineUpListBox.h : header file
//
#include "OnAirDropTarget.h"

/////////////////////////////////////////////////////////////////////////////
// CLineUpListBox window

class CLineUpListBox : public CListBox
{
// Construction
public:
	CLineUpListBox();

// Attributes
public:
	COnAirDropTarget	m_DropTarget;
	COLORREF			m_Color;
	CBrush				m_Brush;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLineUpListBox)
	//}}AFX_VIRTUAL

// Implementation
public:
	CPoint m_ClickPoint;
	LRESULT OnDrop(WPARAM,LPARAM);
	LRESULT OnCanDrop(WPARAM,LPARAM);
	virtual ~CLineUpListBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CLineUpListBox)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void DeleteItem(LPDELETEITEMSTRUCT lpDeleteItemStruct);
	afx_msg void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnDblclk();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSelchange();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LINEUPLISTBOX_H__8909E40A_EA30_4262_B91B_733D17CD9F68__INCLUDED_)
