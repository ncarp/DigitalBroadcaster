#if !defined(AFX_ONAIRTOOLBARCTRL_H__BA19479F_1A7A_4ED9_933A_5869B0E5B18F__INCLUDED_)
#define AFX_ONAIRTOOLBARCTRL_H__BA19479F_1A7A_4ED9_933A_5869B0E5B18F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OnAirToolBarCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COnAirToolBarCtrl window

class COnAirToolBarCtrl : public CToolBarCtrl
{
// Construction
public:
	COnAirToolBarCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COnAirToolBarCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COnAirToolBarCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(COnAirToolBarCtrl)
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ONAIRTOOLBARCTRL_H__BA19479F_1A7A_4ED9_933A_5869B0E5B18F__INCLUDED_)
