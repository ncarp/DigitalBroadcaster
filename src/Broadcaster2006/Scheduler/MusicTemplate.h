#if !defined(AFX_MUSICTEMPLATE_H__5002188E_1F48_4DED_9995_EE78ED98254F__INCLUDED_)
#define AFX_MUSICTEMPLATE_H__5002188E_1F48_4DED_9995_EE78ED98254F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MusicTemplate.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMusicTemplate dialog

class CMusicTemplate : public CDialog
{
// Construction
public:
	CMusicTemplate(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMusicTemplate)
	enum { IDD = IDD_MUSICTEMPLATE };
	CSliderCtrl	m_cRandom;
	CSliderCtrl	m_cMinRythm;
	CSliderCtrl	m_cMinLen;
	CSliderCtrl	m_cMaxRythm;
	CSliderCtrl	m_cMaxLen;
	CComboBox	m_cPlayList;
	CComboBox	m_cExpression;
	CComboBox	m_cCategories;
	int		m_MaxLen;
	CString	m_strMaxLen;
	int		m_MaxRythm;
	CString	m_strMAxRythm;
	int		m_MinLen;
	CString	m_strMinLen;
	int		m_MinRythm;
	CString	m_strMinRythm;
	CString	m_strName;
	int		m_Category;
	int		m_Expression;
	int		m_List;
	int		m_nArtistQuarantine;
	int		m_nRandom;
	int		m_nSongQuarantine;
	//}}AFX_DATA

	CString m_strConnect;
	CString m_strSQL;
	long	m_CategoryID,
			m_ExpressionID,
			m_PlayListID,
			m_TemplateID;
	CString m_strExpression,
			m_strPlayList,
			m_strCategory;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMusicTemplate)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void ComputeSQL();

	// Generated message map functions
	//{{AFX_MSG(CMusicTemplate)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnTestCriteria();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MUSICTEMPLATE_H__5002188E_1F48_4DED_9995_EE78ED98254F__INCLUDED_)
