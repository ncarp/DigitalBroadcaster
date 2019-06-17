#if !defined(AFX_PLAYERBUTTON_H__6C0899AC_3512_41D5_BC93_1BE84DA977DD__INCLUDED_)
#define AFX_PLAYERBUTTON_H__6C0899AC_3512_41D5_BC93_1BE84DA977DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PlayerButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPlayerButton window

class CPlayerButton : public CButton
{
// Construction
public:
	CPlayerButton();

// Attributes
public:
	CImageList* m_pImages;
	int			m_nImages;
	CSize		m_bmSize;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlayerButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	void PaintBM();
	BOOL m_bLight;
	void SetImageList(int cx,int cy,int start,int end);
	void AddImage(int ID,COLORREF cr=RGB(212,208,200));
	
	virtual ~CPlayerButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPlayerButton)
	afx_msg void OnPaint();
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYERBUTTON_H__6C0899AC_3512_41D5_BC93_1BE84DA977DD__INCLUDED_)
