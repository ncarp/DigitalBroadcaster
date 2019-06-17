#if !defined(AFX_DIGITALLEFTVIEW_H__D9767650_3B1B_4000_9F86_D3CA86E5B860__INCLUDED_)
#define AFX_DIGITALLEFTVIEW_H__D9767650_3B1B_4000_9F86_D3CA86E5B860__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DigitalLeftView.h : header file
//
#include "..\OnAir\OnAirDefines.h"

/////////////////////////////////////////////////////////////////////////////
// CDigitalLeftView view

class CDigitalLeftView : public CTreeView
{
protected:
	CDigitalLeftView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDigitalLeftView)

// Attributes
public:
	COleDropTarget	m_DropTarget;
	typeTreeDrag	*m_lpDragItem;
	CPoint			m_OldPoint;
// Operations
public:
	virtual void DeleteAllChildItems( HTREEITEM hItem );
	virtual void SetView(CString strURL);
	virtual void OnSelChange();
	virtual void OnDoubleClick();
	virtual void OnRDoubleClick();
	virtual void DrawDragItem(char *,CPoint point);
	virtual void OnDragMove() {};
	virtual void OnExpanding(HTREEITEM hItem) {};
	virtual HTREEITEM FindString(CString str);
	virtual HTREEITEM FindChildString( HTREEITEM hParent,CString str);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDigitalLeftView)
	public:
	virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual void OnDragLeave();
	virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual BOOL OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CDigitalLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CDigitalLeftView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIGITALLEFTVIEW_H__D9767650_3B1B_4000_9F86_D3CA86E5B860__INCLUDED_)
