#if !defined(AFX_SPOT_H__3224B68C_38C7_4382_AC72_11162A13C58A__INCLUDED_)
#define AFX_SPOT_H__3224B68C_38C7_4382_AC72_11162A13C58A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Spot.h : header file
//

#include "..\OnAir\Recorder.h"
#include "Teste.h"
/////////////////////////////////////////////////////////////////////////////
// CSpot dialog

class CSpot : public CDialog
{
// Construction
public:
	CSpot(CWnd* pParent = NULL);   // standard constructor
	
	CRecorder *m_pTimers;

	long	m_PathID,
			m_CustomerID,
			m_AgencyID,
			m_BusinessID,
			m_VoiceID,
			m_Start,
			m_Mix,
			m_End;
	CString	m_FileName,
			m_Path;
	BOOL	m_IsNew;

// Dialog Data
	//{{AFX_DATA(CSpot)
	enum { IDD = IDD_SPOT };
	CComboBox	m_cVoice;
	CComboBox	m_cCustomer;
	CComboBox	m_cBusiness;
	CComboBox	m_cAgency;
	CComboBox	m_cFile;
	CComboBox	m_cPath;
	CString	m_Name;
	CString	m_OBS;
	CString	m_Agency;
	CString	m_Business;
	CString	m_Customer;
	CString	m_Voice;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpot)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void FillCustomersList();
	void FillBusinessList();
	void FillVoicesList();
	void FillFileList();
	void FillAgencyList();
	
	// Generated message map functions
	//{{AFX_MSG(CSpot)
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSelchangeCustomer();
	afx_msg void OnKillfocusCustomer();
	afx_msg void OnSelchangeBusiness();
	afx_msg void OnKillfocusBusiness();
	afx_msg void OnKillfocusAgency();
	afx_msg void OnSelchangeAgency();
	afx_msg void OnKillfocusVoice();
	afx_msg void OnSelchangeVoice();
	afx_msg void OnKillfocusPath();
	afx_msg void OnSelchangePath();
	afx_msg void OnKillfocusFilename();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	int m_nStandardLength;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPOT_H__3224B68C_38C7_4382_AC72_11162A13C58A__INCLUDED_)
