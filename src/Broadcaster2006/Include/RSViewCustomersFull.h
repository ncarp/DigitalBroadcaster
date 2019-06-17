#if !defined(AFX_RSVIEWCUSTOMERSFULL_H__73AEC0A9_DFAB_4388_BD03_0F45430EE15F__INCLUDED_)
#define AFX_RSVIEWCUSTOMERSFULL_H__73AEC0A9_DFAB_4388_BD03_0F45430EE15F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSViewCustomersFull.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSViewCustomersFull recordset

class CRSViewCustomersFull : public CRecordset
{
public:
	CRSViewCustomersFull(CString str);
	DECLARE_DYNAMIC(CRSViewCustomersFull)

// Field/Param Data
	//{{AFX_FIELD(CRSViewCustomersFull, CRecordset)
	long	m_ID;
	CString	m_Name;
	CString	m_Adress;
	CString	m_ZIP;
	CString	m_Phone;
	CString	m_Fax;
	CString	m_eMail;
	CString	m_www;
	CString	m_Contact;
	CString	m_nc;
	long	m_AgencyID;
	long	m_BusinessTypeID;
	long	m_SalespersonID;
	CString	m_Obs;
	long	m_Activ;
	CString	m_Cli35;
	CString	m_Agency;
	CString	m_Business;
	CString	m_Salesperson;
	CString m_NC2;
	CString m_Name2;
	CString m_Number;
	CString m_CelPhone;
	//}}AFX_FIELD
	
	CString m_strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSViewCustomersFull)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RSVIEWCUSTOMERSFULL_H__73AEC0A9_DFAB_4388_BD03_0F45430EE15F__INCLUDED_)
