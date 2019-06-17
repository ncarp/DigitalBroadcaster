#if !defined(AFX_RMLINEUPRIGHTVIEW_H__D123C7DB_B633_4F59_9141_9001ABEC336D__INCLUDED_)
#define AFX_RMLINEUPRIGHTVIEW_H__D123C7DB_B633_4F59_9141_9001ABEC336D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RMLineUpRightView.h : header file
//

#include "..\include\DigitalLeftView.h"
/////////////////////////////////////////////////////////////////////////////
// CRMLineUpRightView view

class CRMLineUpRightView : public CDigitalLeftView
{
protected:
	CRMLineUpRightView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CRMLineUpRightView)

// Attributes
public:
	CString m_strConnect;
	long	m_ID;
// Operations
public:
	void	SetCartView(long ID);
	virtual void OnDoubleClick();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRMLineUpRightView)
	public:
	virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual BOOL OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CRMLineUpRightView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CRMLineUpRightView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RMLINEUPRIGHTVIEW_H__D123C7DB_B633_4F59_9141_9001ABEC336D__INCLUDED_)
