#if !defined(AFX_BLOCKDETAIL_H__EDB76FE4_A60C_4C78_A2ED_9B693A41B3F1__INCLUDED_)
#define AFX_BLOCKDETAIL_H__EDB76FE4_A60C_4C78_A2ED_9B693A41B3F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BlockDetail.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBlockDetail dialog

class CBlockDetail : public CDialog
{
// Construction
public:
	CBlockDetail(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBlockDetail)
	enum { IDD = IDD_BLOCKDETAIL };
	COleDateTime	m_EndingDate;
	BOOL	m_Fri;
	BOOL	m_Mon;
	CString	m_Name;
	BOOL	m_Sat;
	COleDateTime	m_StartingDate;
	BOOL	m_Sun;
	BOOL	m_Thu;
	BOOL	m_Tue;
	BOOL	m_Wed;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBlockDetail)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBlockDetail)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BLOCKDETAIL_H__EDB76FE4_A60C_4C78_A2ED_9B693A41B3F1__INCLUDED_)
