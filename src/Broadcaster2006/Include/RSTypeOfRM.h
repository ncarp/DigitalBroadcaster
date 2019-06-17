#if !defined(AFX_RSTYPEOFRM_H__F5BD3A34_8AE4_4314_8E07_993741EB86E2__INCLUDED_)
#define AFX_RSTYPEOFRM_H__F5BD3A34_8AE4_4314_8E07_993741EB86E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSTypeOfRM.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSTypeOfRM recordset

class CRSTypeOfRM : public CRecordset
{
public:
	CRSTypeOfRM(CString str);
	DECLARE_DYNAMIC(CRSTypeOfRM)

// Field/Param Data
	//{{AFX_FIELD(CRSTypeOfRM, CRecordset)
	long	m_ID;
	CString	m_Name;
	long	m_Activ;
	//}}AFX_FIELD

	CString strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSTypeOfRM)
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

#endif // !defined(AFX_RSTYPEOFRM_H__F5BD3A34_8AE4_4314_8E07_993741EB86E2__INCLUDED_)
