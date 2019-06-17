#if !defined(AFX_BLOCKSLEFT_H__7442A189_5F96_4039_A9E9_EE07DB863B87__INCLUDED_)
#define AFX_BLOCKSLEFT_H__7442A189_5F96_4039_A9E9_EE07DB863B87__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BlocksLeft.h : header file
//
#include "..\include\DigitalLeftView.h"
/////////////////////////////////////////////////////////////////////////////
// CBlocksLeft view

class CBlocksLeft : public CDigitalLeftView
{
protected:
	CBlocksLeft();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CBlocksLeft)

// Attributes
public:
	CString		m_strRadio,
				m_strConnect,
				m_strDB;
	long		m_lRadioID;
// Operations
public:
	static	UINT	RefreshList(LPVOID lp);
	virtual	void	OnDoubleClick();
	virtual void	OnSelChange();
			void	OnCut();
			void	OnNew();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBlocksLeft)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CBlocksLeft();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CBlocksLeft)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BLOCKSLEFT_H__7442A189_5F96_4039_A9E9_EE07DB863B87__INCLUDED_)
