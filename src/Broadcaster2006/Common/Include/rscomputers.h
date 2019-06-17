#if !defined(AFX_RSCOMPUTERS_H__8F4ECD64_FD9C_43BC_B704_9485AE2588CB__INCLUDED_)
#define AFX_RSCOMPUTERS_H__8F4ECD64_FD9C_43BC_B704_9485AE2588CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// rscomputers.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSComputers recordset

class CRSComputers : public CRecordset
{
public:
	CRSComputers(CString str="Broadcaster");
	DECLARE_DYNAMIC(CRSComputers)

// Field/Param Data
	//{{AFX_FIELD(CRSComputers, CRecordset)
	long	m_ID;
	CString	m_Name;
	//}}AFX_FIELD

	CString m_strConnect;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSComputers)
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

#endif // !defined(AFX_RSCOMPUTERS_H__8F4ECD64_FD9C_43BC_B704_9485AE2588CB__INCLUDED_)
