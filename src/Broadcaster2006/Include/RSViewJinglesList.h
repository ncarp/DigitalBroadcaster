#if !defined(AFX_RSVIEWJINGLESLIST_H__CB30EF6A_BFC3_4238_AFE1_765ABB843384__INCLUDED_)
#define AFX_RSVIEWJINGLESLIST_H__CB30EF6A_BFC3_4238_AFE1_765ABB843384__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSViewJinglesList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSViewJinglesList recordset

class CRSViewJinglesList : public CRecordset
{
public:
	CRSViewJinglesList(CString str);
	DECLARE_DYNAMIC(CRSViewJinglesList)

// Field/Param Data
	//{{AFX_FIELD(CRSViewJinglesList, CRecordset)
	long	m_ID;
	long	m_TypeID;
	CString	m_Name;
	CString	m_Type;
	//}}AFX_FIELD

	CString strConnect;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSViewJinglesList)
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

#endif // !defined(AFX_RSVIEWJINGLESLIST_H__CB30EF6A_BFC3_4238_AFE1_765ABB843384__INCLUDED_)
