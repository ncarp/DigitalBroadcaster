#if !defined(AFX_JINGLETEMPLATE_H__CD9D2E1A_6D42_4FF0_A7C4_5917266A6099__INCLUDED_)
#define AFX_JINGLETEMPLATE_H__CD9D2E1A_6D42_4FF0_A7C4_5917266A6099__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// JingleTemplate.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CJingleTemplate dialog

class CJingleTemplate : public CDialog
{
// Construction
public:
	CJingleTemplate(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CJingleTemplate)
	enum { IDD = IDD_JINGLETEMPLATE };
	CSliderCtrl	m_cMinRythm;
	CSliderCtrl	m_cMinLen;
	CSliderCtrl	m_cMaxRythm;
	CSliderCtrl	m_cMaxLen;
	CComboBox	m_cCategory;
	int		m_Category;
	int		m_MaxLen;
	CString	m_strMaxLenV;
	int		m_MaxRythm;
	CString	m_strMaxRythm;
	int		m_MinLen;
	CString	m_strMinLenV;
	int		m_MinRythm;
	CString	m_strName;
	CString	m_strMinRythmV;
	//}}AFX_DATA

	COleDateTime	m_Date;
	CString			m_strConnect,
					m_strSQL,
					m_strType;
	long			m_CategoryID,
					m_TemplateID;

	void	ComputeSQL();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJingleTemplate)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CJingleTemplate)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnTestCriteria();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JINGLETEMPLATE_H__CD9D2E1A_6D42_4FF0_A7C4_5917266A6099__INCLUDED_)
