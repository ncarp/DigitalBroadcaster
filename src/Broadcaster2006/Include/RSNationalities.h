#if !defined(AFX_RSNATIONALITIES_H__A9F8FD1C_145B_4966_94E2_CB5A6CF9AC0F__INCLUDED_)
#define AFX_RSNATIONALITIES_H__A9F8FD1C_145B_4966_94E2_CB5A6CF9AC0F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSNationalities.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSNationalities recordset

class CRSNationalities : public CRecordset
{
public:
	CRSNationalities(CString str);
	DECLARE_DYNAMIC(CRSNationalities)

// Field/Param Data
	//{{AFX_FIELD(CRSNationalities, CRecordset)
	long	m_ID;
	CString	m_Nationality;
	long	m_ZoneID;
	long	m_Activ;
	//}}AFX_FIELD

	CString strConnect;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSNationalities)
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

#endif // !defined(AFX_RSNATIONALITIES_H__A9F8FD1C_145B_4966_94E2_CB5A6CF9AC0F__INCLUDED_)
