#if !defined(AFX_RSCUSTOMERSLIST_H__8BEC2A2B_C638_4F3D_BF13_937C842DC45E__INCLUDED_)
#define AFX_RSCUSTOMERSLIST_H__8BEC2A2B_C638_4F3D_BF13_937C842DC45E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSCustomersList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSCustomersList recordset

class CRSCustomersList : public CRecordset
{
public:
	CRSCustomersList(CString str);
	DECLARE_DYNAMIC(CRSCustomersList)

// Field/Param Data
	//{{AFX_FIELD(CRSCustomersList, CRecordset)
	long	m_ID;
	CString	m_Name;
	//}}AFX_FIELD

	CString m_strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSCustomersList)
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

#endif // !defined(AFX_RSCUSTOMERSLIST_H__8BEC2A2B_C638_4F3D_BF13_937C842DC45E__INCLUDED_)
