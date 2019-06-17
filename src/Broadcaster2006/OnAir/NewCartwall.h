#if !defined(AFX_NEWCARTWALL_H__D43B5BBB_78EC_4558_93DA_62ABE3A203E8__INCLUDED_)
#define AFX_NEWCARTWALL_H__D43B5BBB_78EC_4558_93DA_62ABE3A203E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewCartwall.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewCartwall dialog

class CNewCartwall : public CDialog
{
// Construction
public:
	CNewCartwall(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNewCartwall)
	enum { IDD = IDD_NEWCARTWALL };
	CString	m_Name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewCartwall)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewCartwall)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWCARTWALL_H__D43B5BBB_78EC_4558_93DA_62ABE3A203E8__INCLUDED_)
