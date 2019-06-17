#if !defined(AFX_RSVIEWNEWSLIST_H__B567D91E_72DD_4150_8D7D_87E43692C05C__INCLUDED_)
#define AFX_RSVIEWNEWSLIST_H__B567D91E_72DD_4150_8D7D_87E43692C05C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSViewNewsList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSViewNewsList recordset

class CRSViewNewsList : public CRecordset
{
public:
	CRSViewNewsList(CString str);
	DECLARE_DYNAMIC(CRSViewNewsList)

// Field/Param Data
	//{{AFX_FIELD(CRSViewNewsList, CRecordset)
	long	m_ID;
	CString	m_Name;
	CString	m_TypeID;
	CString	m_Type;
	//}}AFX_FIELD

	CString strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSViewNewsList)
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

#endif // !defined(AFX_RSVIEWNEWSLIST_H__B567D91E_72DD_4150_8D7D_87E43692C05C__INCLUDED_)
