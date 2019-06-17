#if !defined(AFX_TESTE_H__864E4A0A_F20E_4D05_AE66_E8837580BDDE__INCLUDED_)
#define AFX_TESTE_H__864E4A0A_F20E_4D05_AE66_E8837580BDDE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Teste.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Teste form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class Teste : public CFormView
{
protected:
	Teste();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(Teste)

// Form Data
public:
	//{{AFX_DATA(Teste)
	enum { IDD = IDD_DIALOG1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Teste)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~Teste();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(Teste)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTE_H__864E4A0A_F20E_4D05_AE66_E8837580BDDE__INCLUDED_)
