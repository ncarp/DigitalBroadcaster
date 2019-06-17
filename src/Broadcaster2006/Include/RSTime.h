#if !defined(AFX_RSTIME_H__AF78FB6E_F911_4CCC_8CC9_96D8D26436D4__INCLUDED_)
#define AFX_RSTIME_H__AF78FB6E_F911_4CCC_8CC9_96D8D26436D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSTime.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSTime recordset

class CRSTime : public CRecordset
{
public:
	CRSTime(CString str);
	DECLARE_DYNAMIC(CRSTime)

// Field/Param Data
	//{{AFX_FIELD(CRSTime, CRecordset)
	long	m_ID;
	CString	m_Name;
	long	m_PathID;
	CString	m_FolderName;
	//}}AFX_FIELD

	CString strConnect;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSTime)
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

#endif // !defined(AFX_RSTIME_H__AF78FB6E_F911_4CCC_8CC9_96D8D26436D4__INCLUDED_)
