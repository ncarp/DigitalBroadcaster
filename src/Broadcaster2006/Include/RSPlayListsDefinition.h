#if !defined(AFX_RSPLAYLISTSDEFINITION_H__7567BC81_46AC_41E1_84E0_93198CD608E2__INCLUDED_)
#define AFX_RSPLAYLISTSDEFINITION_H__7567BC81_46AC_41E1_84E0_93198CD608E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSPlayListsDefinition.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSPlayListsDefinition recordset

class CRSPlayListsDefinition : public CRecordset
{
public:
	CRSPlayListsDefinition(CString str);
	DECLARE_DYNAMIC(CRSPlayListsDefinition)

// Field/Param Data
	//{{AFX_FIELD(CRSPlayListsDefinition, CRecordset)
	long	m_ID;
	CString	m_Name;
	long	m_Activ;
	CString	m_DRM35;
	long	m_OnAir;
	//}}AFX_FIELD
	
	CString	m_strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSPlayListsDefinition)
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

#endif // !defined(AFX_RSPLAYLISTSDEFINITION_H__7567BC81_46AC_41E1_84E0_93198CD608E2__INCLUDED_)
