#if !defined(AFX_RSVIEWNEWS_H__36D658D8_60EA_400E_BA3F_6A3AD4F40E4F__INCLUDED_)
#define AFX_RSVIEWNEWS_H__36D658D8_60EA_400E_BA3F_6A3AD4F40E4F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSViewNews.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSViewNews recordset

class CRSViewNews : public CRecordset
{
public:
	CRSViewNews(CString str);
	DECLARE_DYNAMIC(CRSViewNews)

// Field/Param Data
	//{{AFX_FIELD(CRSViewNews, CRecordset)
	long	m_ID;
	CString	m_Name;
	long	m_TypeID;
	COleDateTime	m_Date;
	long	m_Activ;
	CString	m_NewsText;
	CString	m_Type;
	CString	m_KeyWords;
	//}}AFX_FIELD

	CString strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSViewNews)
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

#endif // !defined(AFX_RSVIEWNEWS_H__36D658D8_60EA_400E_BA3F_6A3AD4F40E4F__INCLUDED_)
