#if !defined(AFX_INSTRUMENTALLEFTVIEW_H__757A5D97_84D4_4AA4_BDA0_9760BFEC8BFE__INCLUDED_)
#define AFX_INSTRUMENTALLEFTVIEW_H__757A5D97_84D4_4AA4_BDA0_9760BFEC8BFE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InstrumentalLeftView.h : header file
//

#include "..\include\digitalleftview.h"

/////////////////////////////////////////////////////////////////////////////
// CInstrumentalLeftView view

class CInstrumentalLeftView : public CDigitalLeftView
{
protected:
	CInstrumentalLeftView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CInstrumentalLeftView)

// Attributes
public:
	CString		m_strConnect;
	long int	m_lRadioID;
	HTREEITEM	m_hMusic,
				m_hJingles;
// Operations
public:
	virtual void OnSelChange();
	virtual void OnRDoubleClick();
			void OnCut();
			void OnPFL();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInstrumentalLeftView)
	public:
	virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual BOOL OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CInstrumentalLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CInstrumentalLeftView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INSTRUMENTALLEFTVIEW_H__757A5D97_84D4_4AA4_BDA0_9760BFEC8BFE__INCLUDED_)
