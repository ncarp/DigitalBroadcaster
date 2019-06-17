#if !defined(AFX_SCHEDULELEFTVIEW_H__5A556D5D_B933_422B_9C2D_EC74DED38F3D__INCLUDED_)
#define AFX_SCHEDULELEFTVIEW_H__5A556D5D_B933_422B_9C2D_EC74DED38F3D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScheduleLeftView.h : header file
//

#include "..\include\DigitalLeftView.h"

/////////////////////////////////////////////////////////////////////////////
// CScheduleLeftView view

class CScheduleLeftView : public CDigitalLeftView
{
protected:
	CScheduleLeftView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CScheduleLeftView)

// Attributes
public:
	HTREEITEM	m_hTemplateMusic,
				m_hTemplateJingles;
// Operations
public:
	static	UINT	RefreshList( LPVOID lp );
	virtual void	OnExpanding( HTREEITEM hItem );
	virtual void	ExpandMusicTemplate( HTREEITEM hItem, long lID );
	virtual void	ExpandJingleTemplate( HTREEITEM hItem, long lID );
	virtual void	OnDoubleClick();
	virtual void	AddMusicTemplate( HTREEITEM hItem );
	virtual void	EditMusicTemplate( HTREEITEM hItem );
	virtual void	AddJingleTemplate( HTREEITEM hItem );
	virtual void	EditJingleTemplate( HTREEITEM hItem );
	virtual void	AddVoiceInsert( HTREEITEM hItem );
	virtual void	EditVoiceInsert( HTREEITEM hItem );
	virtual void	OnPFL();
	virtual void	OnCut();
	virtual void	OnRDoubleClick();
	virtual void	CScheduleLeftView::OnRButtonDblClk();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScheduleLeftView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CScheduleLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CScheduleLeftView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCHEDULELEFTVIEW_H__5A556D5D_B933_422B_9C2D_EC74DED38F3D__INCLUDED_)
