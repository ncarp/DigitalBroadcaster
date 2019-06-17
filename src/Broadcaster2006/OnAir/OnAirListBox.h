#if !defined(AFX_ONAIRLISTBOX_H__CEC93F95_C0A8_4350_9E6E_A5CCE39D1932__INCLUDED_)
#define AFX_ONAIRLISTBOX_H__CEC93F95_C0A8_4350_9E6E_A5CCE39D1932__INCLUDED_

#include "OnAirDropTarget.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OnAirListBox.h : header file
//

#include "OnAirDropTarget.h"

/////////////////////////////////////////////////////////////////////////////
// COnAirListBox window

class COnAirListBox : public CListBox
{
// Construction
public:
	COnAirListBox();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COnAirListBox)
	//}}AFX_VIRTUAL

// Implementation
public:
	COnAirDropTarget m_DropTarget;
	int m_iX1,
		m_iX2;
	BOOL m_bIsRefreshing;
	CBrush m_Brush;
	COLORREF m_color;
	CHeaderCtrl *m_pHeader;

	virtual ~COnAirListBox();
	virtual int OnToolHitTest( CPoint point, TOOLINFO* pTI ) const;
	virtual void SetBackColor( COLORREF colorref );
	// Generated message map functions
protected:
	//{{AFX_MSG(COnAirListBox)
	afx_msg void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void DeleteItem(LPDELETEITEMSTRUCT lpDeleteItemStruct);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDblclk();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	int m_iTickCount;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ONAIRLISTBOX_H__CEC93F95_C0A8_4350_9E6E_A5CCE39D1932__INCLUDED_)
