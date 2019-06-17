#if !defined(AFX_RSEXPRESSIONS_H__540D8490_8A70_4D94_8BCF_59164EF42D8B__INCLUDED_)
#define AFX_RSEXPRESSIONS_H__540D8490_8A70_4D94_8BCF_59164EF42D8B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSExpressions.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSExpressions recordset

class CRSExpressions : public CRecordset
{
public:
	CRSExpressions(CString str);
	DECLARE_DYNAMIC(CRSExpressions)

// Field/Param Data
	//{{AFX_FIELD(CRSExpressions, CRecordset)
	long	m_ID;
	CString	m_Name;
	long	m_Activ;
	CString	m_DRM35;
	//}}AFX_FIELD

	CString m_strConnect;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSExpressions)
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

#endif // !defined(AFX_RSEXPRESSIONS_H__540D8490_8A70_4D94_8BCF_59164EF42D8B__INCLUDED_)
