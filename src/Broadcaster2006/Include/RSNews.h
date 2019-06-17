#if !defined(AFX_RSNEWS_H__35B3D613_9CFE_425A_A580_42E9779A83D0__INCLUDED_)
#define AFX_RSNEWS_H__35B3D613_9CFE_425A_A580_42E9779A83D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSNews.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSNews recordset

class CRSNews : public CRecordset
{
public:
	CRSNews(CString strConnect);
	DECLARE_DYNAMIC(CRSNews)

// Field/Param Data
	//{{AFX_FIELD(CRSNews, CRecordset)
	long	m_ID;
	CString	m_Name;
	long	m_TypeID;
	COleDateTime m_Date;
	long	m_Activ;
	CString	m_NewsText;
	CString	m_KeyWords;
	//}}AFX_FIELD

	CString strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSNews)
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

#endif // !defined(AFX_RSNEWS_H__35B3D613_9CFE_425A_A580_42E9779A83D0__INCLUDED_)
