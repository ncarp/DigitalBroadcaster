#if !defined(AFX_PLAYLISTLEFTVIEW_H__A3D98004_D852_4997_8EA8_94E341B030D7__INCLUDED_)
#define AFX_PLAYLISTLEFTVIEW_H__A3D98004_D852_4997_8EA8_94E341B030D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PlayListLeftView.h : header file
//

#include "..\include\DigitalLeftView.h"
#include "PlayListRightView.h"

/////////////////////////////////////////////////////////////////////////////
// CPlayListLeftView view

class CPlayListLeftView : public CDigitalLeftView
{
protected:
	CPlayListLeftView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPlayListLeftView)

// Attributes
public:
	CString	m_strConnect,
			m_strRadio,
			m_strDB;
	long	m_lRadioID;
	CPlayListRightView *m_rightView;

// Operations
public:
	static	UINT	RefreshList( LPVOID lp);
	virtual void	OnSelChange();
	virtual void	OnNew();
	virtual void	OnDoubleClick();
	virtual void	OnCut();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlayListLeftView)
	public:
	virtual void OnInitialUpdate();
	virtual BOOL OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
	virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPlayListLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CPlayListLeftView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYLISTLEFTVIEW_H__A3D98004_D852_4997_8EA8_94E341B030D7__INCLUDED_)
