#if !defined(AFX_LINEUPNAME_H__63E63510_4AF4_4128_8E5F_CBF03F7F89EC__INCLUDED_)
#define AFX_LINEUPNAME_H__63E63510_4AF4_4128_8E5F_CBF03F7F89EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LineUpName.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLineUpName dialog

class CLineUpName : public CDialog
{
// Construction
public:
	CLineUpName(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLineUpName)
	enum { IDD = IDD_NEWCARTWALL };
	CString	m_Name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLineUpName)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLineUpName)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LINEUPNAME_H__63E63510_4AF4_4128_8E5F_CBF03F7F89EC__INCLUDED_)
