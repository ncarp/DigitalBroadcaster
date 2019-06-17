#if !defined(AFX_RSBUSINESS_H__021F63F7_F19E_4809_8620_8B0201C11C1B__INCLUDED_)
#define AFX_RSBUSINESS_H__021F63F7_F19E_4809_8620_8B0201C11C1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSBusiness.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSBusiness recordset

class CRSBusiness : public CRecordset
{
public:
	CRSBusiness(CString str);
	DECLARE_DYNAMIC(CRSBusiness)

// Field/Param Data
	//{{AFX_FIELD(CRSBusiness, CRecordset)
	long	m_ID;
	CString	m_Name;
	long	m_Activ;
	//}}AFX_FIELD

	CString strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSBusiness)
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

#endif // !defined(AFX_RSBUSINESS_H__021F63F7_F19E_4809_8620_8B0201C11C1B__INCLUDED_)
