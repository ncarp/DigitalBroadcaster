#if !defined(AFX_PLAYLISTRIGHTVIEW_H__97761AF8_18CE_4576_8A9D_9029947F0268__INCLUDED_)
#define AFX_PLAYLISTRIGHTVIEW_H__97761AF8_18CE_4576_8A9D_9029947F0268__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PlayListRightView.h : header file
//

#include "..\include\DigitalLeftView.h"

/////////////////////////////////////////////////////////////////////////////
// CPlayListRightView view

class CPlayListRightView : public CDigitalLeftView
{
protected:
	CPlayListRightView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPlayListRightView)

// Attributes
public:
	CString			m_strConnect,
					m_strDB;
	BOOL			m_IsRefreshing;
	long			m_PlayList,
					m_lRadioID;
	CStatusBar		*m_wndStatusBar;
	
// Operations
public:
	virtual void OnDragMove();
	void	OnRDoubleClick();
	void	OnDoubleClick();
	void	OnSelChange();
	void	OnPFL();
	void	SetPlayList(WORD wType,long lID);
	void	OnCut();
	void	OnInfo();
	static UINT FillWithNotListed( LPVOID );
	static UINT FillWithPlayList( LPVOID );
	static UINT FillWithAll( LPVOID );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlayListRightView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPlayListRightView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CPlayListRightView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYLISTRIGHTVIEW_H__97761AF8_18CE_4576_8A9D_9029947F0268__INCLUDED_)
