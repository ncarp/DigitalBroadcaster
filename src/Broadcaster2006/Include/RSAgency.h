#if !defined(AFX_RSAGENCY_H__C5A3F009_34D6_42CE_9FD4_6E58FE2BF4DE__INCLUDED_)
#define AFX_RSAGENCY_H__C5A3F009_34D6_42CE_9FD4_6E58FE2BF4DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSAgency.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSAgency recordset

class CRSAgency : public CRecordset
{
public:
	CRSAgency(CString str);
	DECLARE_DYNAMIC(CRSAgency)

// Field/Param Data
	//{{AFX_FIELD(CRSAgency, CRecordset)
	long	m_ID;
	CString	m_Name;
	CString	m_Adress;
	CString	m_ZIP;
	CString	m_Telephone;
	CString	m_Fax;
	CString	m_eMail;
	CString	m_WWW;
	CString	m_Contact;
	CString	m_FID;
	long	m_Salesperson;
	CString	m_OBS;
	long	m_Activ;
	//}}AFX_FIELD

	CString strConnect;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSAgency)
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

#endif // !defined(AFX_RSAGENCY_H__C5A3F009_34D6_42CE_9FD4_6E58FE2BF4DE__INCLUDED_)
