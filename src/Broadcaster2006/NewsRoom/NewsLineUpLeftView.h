#if !defined(AFX_NEWSLINEUPLEFTVIEW_H__AA460D31_0664_46C3_98A7_BD842D51565B__INCLUDED_)
#define AFX_NEWSLINEUPLEFTVIEW_H__AA460D31_0664_46C3_98A7_BD842D51565B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewsLineUpLeftView.h : header file
//
#include "..\include\DigitalLeftView.h"

/////////////////////////////////////////////////////////////////////////////
// CNewsLineUpLeftView view

class CNewsLineUpLeftView : public CDigitalLeftView
{
protected:
	CNewsLineUpLeftView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CNewsLineUpLeftView)

// Attributes
public:
	CString	m_strConnect,
			m_strRadio,
			m_strDB;
// Operations
public:
			void	OnNew();
			void	OnCut();
	virtual	void	OnDoubleClick();
	virtual void	OnSelChange();
	static	UINT	RefreshList(LPVOID lp);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewsLineUpLeftView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CNewsLineUpLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CNewsLineUpLeftView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWSLINEUPLEFTVIEW_H__AA460D31_0664_46C3_98A7_BD842D51565B__INCLUDED_)
