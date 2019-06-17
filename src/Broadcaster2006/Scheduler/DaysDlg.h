#if !defined(AFX_DAYSDLG_H__B736B47E_9461_46C4_BC3F_C269A0C49487__INCLUDED_)
#define AFX_DAYSDLG_H__B736B47E_9461_46C4_BC3F_C269A0C49487__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DaysDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDaysDlg dialog

class CDaysDlg : public CDialog
{
// Construction
public:
	CDaysDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDaysDlg)
	enum { IDD = IDD_NUMBEROFDAYS };
	int		m_nDays;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDaysDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDaysDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DAYSDLG_H__B736B47E_9461_46C4_BC3F_C269A0C49487__INCLUDED_)
