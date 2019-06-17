#if !defined(AFX_CART_H__EB996D90_DC26_4A57_8FD3_D6960CDE95CB__INCLUDED_)
#define AFX_CART_H__EB996D90_DC26_4A57_8FD3_D6960CDE95CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Cart.h : header file
//

#include "typeLineUpItem.h"
#include "OnAirDropTarget.h"
#include "PlayerButton.h"

/////////////////////////////////////////////////////////////////////////////
// CCart window

class CCart : public CStatic
{
// Construction
public:
	CCart();

// Attributes
public:
	typeLineUpItem		*m_pItem;
protected:
	COnAirDropTarget	m_DropTarget;
	
	BOOL				m_bPlaying;
	Bitmap				*m_bmName;
	Bitmap				*m_bmCrono;
// Operations
public:
	CPlayerButton	*m_Cut;
	void			OnCut();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCart)
	//}}AFX_VIRTUAL

// Implementation
public:
	void Load( WORD Type,long ID);
	CRect m_rect;
	void DrawCart();
	void Stop();
	void Play();
	WORD m_wState;
	void PaintCrono();
	void PaintBM();
	float m_xres;
	LRESULT OnDrop(WPARAM,LPARAM);
	LRESULT OnDropQuery(WPARAM,LPARAM);
	WORD m_wCartNumber;
	virtual ~CCart();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCart)
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CART_H__EB996D90_DC26_4A57_8FD3_D6960CDE95CB__INCLUDED_)
