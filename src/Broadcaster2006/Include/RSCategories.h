#if !defined(AFX_RSCATEGORIES_H__5009B697_BC2E_4669_B34B_57EA35E845A4__INCLUDED_)
#define AFX_RSCATEGORIES_H__5009B697_BC2E_4669_B34B_57EA35E845A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSCategories.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSCategories recordset

class CRSCategories : public CRecordset
{
public:
	CRSCategories(CString str);
	DECLARE_DYNAMIC(CRSCategories)

// Field/Param Data
	//{{AFX_FIELD(CRSCategories, CRecordset)
	long	m_ID;
	CString	m_Name;
	long	m_Activ;
	//}}AFX_FIELD

	CString	m_strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSCategories)
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

#endif // !defined(AFX_RSCATEGORIES_H__5009B697_BC2E_4669_B34B_57EA35E845A4__INCLUDED_)
