#if !defined(AFX_RSTYPEOFJINGLE_H__A22184CC_6D1F_4E4E_80B4_A5400E8DFC79__INCLUDED_)
#define AFX_RSTYPEOFJINGLE_H__A22184CC_6D1F_4E4E_80B4_A5400E8DFC79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSTypeOfJingle.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSTypeOfJingle recordset

class CRSTypeOfJingle : public CRecordset
{
public:
	CRSTypeOfJingle(CString str);
	DECLARE_DYNAMIC(CRSTypeOfJingle)

// Field/Param Data
	//{{AFX_FIELD(CRSTypeOfJingle, CRecordset)
	long	m_ID;
	CString	m_Name;
	long	m_Activ;
	CString	m_DRM35;
	//}}AFX_FIELD

	CString strConnect;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSTypeOfJingle)
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

#endif // !defined(AFX_RSTYPEOFJINGLE_H__A22184CC_6D1F_4E4E_80B4_A5400E8DFC79__INCLUDED_)
