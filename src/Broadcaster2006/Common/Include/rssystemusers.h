#if !defined(AFX_RSSYSTEMUSERS_H__E4BC1718_7FFF_4723_8295_A886CC404AAE__INCLUDED_)
#define AFX_RSSYSTEMUSERS_H__E4BC1718_7FFF_4723_8295_A886CC404AAE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// rssystemusers.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSSystemUsers recordset

class CRSSystemUsers : public CRecordset
{
public:
	CRSSystemUsers(CString str="Broadcaster");
	DECLARE_DYNAMIC(CRSSystemUsers)

// Field/Param Data
	//{{AFX_FIELD(CRSSystemUsers, CRecordset)
	long	m_Id;
	CString	m_Name;
	CByteArray	m_Permission;
	//}}AFX_FIELD
	CString m_strConnect;
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSSystemUsers)
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

#endif // !defined(AFX_RSSYSTEMUSERS_H__E4BC1718_7FFF_4723_8295_A886CC404AAE__INCLUDED_)
