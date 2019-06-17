#if !defined(AFX_RSNEWSLINEUPDEFINITION_H__8675983B_F1AD_49A2_B211_14B6D3090516__INCLUDED_)
#define AFX_RSNEWSLINEUPDEFINITION_H__8675983B_F1AD_49A2_B211_14B6D3090516__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSNewsLineUpDefinition.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSNewsLineUpDefinition recordset

class CRSNewsLineUpDefinition : public CRecordset
{
public:
	CRSNewsLineUpDefinition(CString str);
	DECLARE_DYNAMIC(CRSNewsLineUpDefinition)

// Field/Param Data
	//{{AFX_FIELD(CRSNewsLineUpDefinition, CRecordset)
	long	m_ID;
	CString	m_Name;
	//}}AFX_FIELD

	CString strConnect;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSNewsLineUpDefinition)
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

#endif // !defined(AFX_RSNEWSLINEUPDEFINITION_H__8675983B_F1AD_49A2_B211_14B6D3090516__INCLUDED_)
