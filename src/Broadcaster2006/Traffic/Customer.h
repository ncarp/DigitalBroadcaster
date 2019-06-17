#if !defined(AFX_CUSTOMER_H__48199492_8FBA_4E4B_977F_E950E6667525__INCLUDED_)
#define AFX_CUSTOMER_H__48199492_8FBA_4E4B_977F_E950E6667525__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Customer.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCustomer dialog

class CCustomer : public CDialog
{
// Construction
public:
	CCustomer(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCustomer)
	enum { IDD = IDD_CUSTOMER };
	CComboBox	m_cSales;
	CComboBox	m_cBusiness;
	CComboBox	m_cAgency;
	CString	m_strAdress;
	CString	m_strAgency;
	CString	m_strBusiness;
	CString	m_strContact;
	CString	m_stremail;
	CString	m_strFax;
	CString	m_strFN;
	CString	m_strName;
	CString	m_strOBS;
	CString	m_strPhone;
	CString	m_strSales;
	CString	m_strZIP;
	CString	m_strWWW;
	//}}AFX_DATAcMap[0].oldColor = Color(255, 212,208,200); 

	long	m_CustomerID;
	long	m_BusinessID;
	long	m_AgencyID;
	long	m_SalesID;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void	FillBusinessList();
	void	FillAgencyList();
	void	FillSalesmanList();

	// Generated message map functions
	//{{AFX_MSG(CCustomer)
	afx_msg void OnKillfocusCustomerBusiness();
	afx_msg void OnSelchangeCustomerBusiness();
	afx_msg void OnKillfocusCustomerAgency();
	afx_msg void OnSelchangeCustomerAgency();
	afx_msg void OnKillfocusCustomerSales();
	afx_msg void OnSelchangeCustomerSales();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CString m_strNumber;
	CString m_strName2;
	CString m_strCelPhone;
	CString m_strNC2;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMER_H__48199492_8FBA_4E4B_977F_E950E6667525__INCLUDED_)
