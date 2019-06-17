#if !defined(AFX_RSVIEWSPOTSLIST_H__FBC1F32C_1DEA_4A4F_915E_CA3C243F40A8__INCLUDED_)
#define AFX_RSVIEWSPOTSLIST_H__FBC1F32C_1DEA_4A4F_915E_CA3C243F40A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSViewSpotsList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSViewSpotsList recordset

class CRSViewSpotsList : public CRecordset
{
public:
	CRSViewSpotsList(CString str);
	DECLARE_DYNAMIC(CRSViewSpotsList)

// Field/Param Data
	//{{AFX_FIELD(CRSViewSpotsList, CRecordset)
	long	m_ID;
	CString	m_Name;
	long	m_CustomerID;
	long	m_AgencyID;
	CString	m_CustomerName;
	CString	m_AgencyName;
	long	m_SalespersonID;
	CString	m_SalespersonName;
	//}}AFX_FIELD

	CString m_strConnect;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSViewSpotsList)
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

#endif // !defined(AFX_RSVIEWSPOTSLIST_H__FBC1F32C_1DEA_4A4F_915E_CA3C243F40A8__INCLUDED_)
