#if !defined(AFX_RSCARTWALLDEFINITION_H__6FC89FBA_940F_4F8D_A614_490388240C4B__INCLUDED_)
#define AFX_RSCARTWALLDEFINITION_H__6FC89FBA_940F_4F8D_A614_490388240C4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSCartwallDefinition.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSCartwallDefinition recordset

class CRSCartwallDefinition : public CRecordset
{
public:
	CRSCartwallDefinition(CString str);
	DECLARE_DYNAMIC(CRSCartwallDefinition)

// Field/Param Data
	//{{AFX_FIELD(CRSCartwallDefinition, CRecordset)
	long	m_ID;
	CString	m_Name;
	long	m_UserID;
	long	m_Info;
	//}}AFX_FIELD

	CString strConnect;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSCartwallDefinition)
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

#endif // !defined(AFX_RSCARTWALLDEFINITION_H__6FC89FBA_940F_4F8D_A614_490388240C4B__INCLUDED_)
