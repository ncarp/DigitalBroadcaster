#if !defined(AFX_TIMESPANDEFINITION_H__4A40AD46_A7A1_4253_AF9D_F53880C68854__INCLUDED_)
#define AFX_TIMESPANDEFINITION_H__4A40AD46_A7A1_4253_AF9D_F53880C68854__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TimeSpanDefinition.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTimeSpanDefinition dialog

class CTimeSpanDefinition : public CDialog
{
// Construction
public:
	CTimeSpanDefinition(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTimeSpanDefinition)
	enum { IDD = IDD_RMONAIR };
	COleDateTime	m_EndingDate;
	CString	m_Name;
	COleDateTime	m_StartingDate;
	CString	m_Type;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTimeSpanDefinition)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTimeSpanDefinition)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIMESPANDEFINITION_H__4A40AD46_A7A1_4253_AF9D_F53880C68854__INCLUDED_)
