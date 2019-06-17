#pragma once
#include "afxcmn.h"


// CNationalitiesMain dialog

class CNationalitiesMain : public CDialog
{
	DECLARE_DYNAMIC(CNationalitiesMain)

public:
	CNationalitiesMain(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNationalitiesMain();

// Dialog Data
	enum { IDD = IDD_NATIONALITIES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CListCtrl m_cList;
	virtual BOOL OnInitDialog();
	afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);
};
