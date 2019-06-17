#if !defined(AFX_DOUBLESLIDER_H__CF566CDC_66CC_4F17_8A5C_9BD9954753F4__INCLUDED_)
#define AFX_DOUBLESLIDER_H__CF566CDC_66CC_4F17_8A5C_9BD9954753F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DoubleSlider.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDoubleSlider window

#define		UM_DOUBLECHANGE		WM_USER+1010

class CDoubleSlider : public CStatic
{
// Construction
public:
	CDoubleSlider();
	
// Attributes
public:
	int		m_RightPos,m_RightLimit;
	int		m_LeftPos,m_LeftLimit;
	float	m_fLeft,
			m_fRight;

protected:
	HCURSOR CursorArrow;
	HCURSOR CursorSize;
	BOOL	bLeftDrag;
	BOOL	bRightDrag;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDoubleSlider)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDoubleSlider();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDoubleSlider)
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOUBLESLIDER_H__CF566CDC_66CC_4F17_8A5C_9BD9954753F4__INCLUDED_)
