#if !defined(AFX_SPONSOR_H__46EE4559_B1B8_4FDE_A4AB_6C23E3382344__INCLUDED_)
#define AFX_SPONSOR_H__46EE4559_B1B8_4FDE_A4AB_6C23E3382344__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Sponsor.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSponsor dialog

class CSponsor : public CDialog
{
// Construction
public:
	CSponsor(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSponsor)
	enum { IDD = IDD_SPONSOR };
	CString	m_CustomerName;
	COleDateTime	m_dEndingDate;
	COleDateTime	m_dStartingDate;
	CString	m_SpotName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSponsor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSponsor)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPONSOR_H__46EE4559_B1B8_4FDE_A4AB_6C23E3382344__INCLUDED_)
