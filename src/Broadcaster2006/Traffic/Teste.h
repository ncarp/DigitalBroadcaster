#if !defined(AFX_TESTE_H__D139D752_062B_4ED5_80C3_7E47CED35C28__INCLUDED_)
#define AFX_TESTE_H__D139D752_062B_4ED5_80C3_7E47CED35C28__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Teste.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTeste window

class CTeste : public CStatic
{
// Construction
public:
	CTeste();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTeste)
	public:
	
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTeste();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTeste)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTE_H__D139D752_062B_4ED5_80C3_7E47CED35C28__INCLUDED_)
