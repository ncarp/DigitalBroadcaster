#if !defined(AFX_RSRECORDLABEL_H__BC19DDE3_8CDE_4441_951F_6871EAB8AA47__INCLUDED_)
#define AFX_RSRECORDLABEL_H__BC19DDE3_8CDE_4441_951F_6871EAB8AA47__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSRecordLabel.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSRecordLabel recordset

class CRSRecordLabel : public CRecordset
{
public:
	CRSRecordLabel(CString str);
	DECLARE_DYNAMIC(CRSRecordLabel)

// Field/Param Data
	//{{AFX_FIELD(CRSRecordLabel, CRecordset)
	long	m_ID;
	CString	m_Name;
	CString	m_Adress;
	long	m_Activ;
	long	m_ParentCompany;
	//}}AFX_FIELD

	CString strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSRecordLabel)
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

#endif // !defined(AFX_RSRECORDLABEL_H__BC19DDE3_8CDE_4441_951F_6871EAB8AA47__INCLUDED_)
