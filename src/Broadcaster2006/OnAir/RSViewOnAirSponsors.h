#if !defined(AFX_RSVIEWONAIRSPONSORS_H__951C4F92_ACCA_48A2_9556_2A338EC8AC6A__INCLUDED_)
#define AFX_RSVIEWONAIRSPONSORS_H__951C4F92_ACCA_48A2_9556_2A338EC8AC6A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSViewOnAirSponsors.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSViewOnAirSponsors recordset

class CRSViewOnAirSponsors : public CRecordset
{
public:
	CRSViewOnAirSponsors(CString str);
	DECLARE_DYNAMIC(CRSViewOnAirSponsors)

// Field/Param Data
	//{{AFX_FIELD(CRSViewOnAirSponsors, CRecordset)
	long	m_SpotID;
	CTime	m_StartingDate;
	CTime	m_EndingDate;
	CString	m_SpotName;
	CString	m_CustomerName;
	long	m_Length;
	//}}AFX_FIELD
	
	CString m_strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSViewOnAirSponsors)
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

#endif // !defined(AFX_RSVIEWONAIRSPONSORS_H__951C4F92_ACCA_48A2_9556_2A338EC8AC6A__INCLUDED_)
