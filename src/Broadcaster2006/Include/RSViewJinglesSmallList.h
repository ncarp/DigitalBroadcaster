#if !defined(AFX_RSVIEWJINGLESSMALLLIST_H__D9602DB7_0B0D_438B_8486_25F1ED9B8938__INCLUDED_)
#define AFX_RSVIEWJINGLESSMALLLIST_H__D9602DB7_0B0D_438B_8486_25F1ED9B8938__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSViewJinglesSmallList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSViewJinglesSmallList recordset

class CRSViewJinglesSmallList : public CRecordset
{
public:
	CRSViewJinglesSmallList(CString str);
	DECLARE_DYNAMIC(CRSViewJinglesSmallList)

// Field/Param Data
	//{{AFX_FIELD(CRSViewJinglesSmallList, CRecordset)
	long	m_ID;
	CString	m_Jingle;
	//}}AFX_FIELD

	CString m_strConnect;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSViewJinglesSmallList)
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

#endif // !defined(AFX_RSVIEWJINGLESSMALLLIST_H__D9602DB7_0B0D_438B_8486_25F1ED9B8938__INCLUDED_)
