#pragma once
#include "afxcmn.h"


// CExpressions dialog

class CExpressions : public CDialog
{
	DECLARE_DYNAMIC(CExpressions)

public:
	CExpressions(CWnd* pParent = NULL);   // standard constructor
	virtual ~CExpressions();

// Dialog Data
	enum { IDD = IDD_EXPRESSIONS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_cList;
	afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
};
