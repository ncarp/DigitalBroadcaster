#if !defined(AFX_RSVIEWSPONSORS_H__87834F37_638F_405E_85F7_9DA30637C6D0__INCLUDED_)
#define AFX_RSVIEWSPONSORS_H__87834F37_638F_405E_85F7_9DA30637C6D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSViewSponsors.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSViewSponsors recordset

class CRSViewSponsors : public CRecordset
{
public:
	CRSViewSponsors(CString str);
	DECLARE_DYNAMIC(CRSViewSponsors)

// Field/Param Data
	//{{AFX_FIELD(CRSViewSponsors, CRecordset)
	long	m_SpotID;
	COleDateTime	m_StartingDate;
	COleDateTime	m_EndingDate;
	CString	m_SpotName;
	CString	m_CustomerName;
	long	m_ID;
	long	m_CustomerID;
	//}}AFX_FIELD

	CString strConnect;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSViewSponsors)
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

#endif // !defined(AFX_RSVIEWSPONSORS_H__87834F37_638F_405E_85F7_9DA30637C6D0__INCLUDED_)
