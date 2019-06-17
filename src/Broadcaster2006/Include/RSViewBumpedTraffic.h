#if !defined(AFX_RSVIEWBUMPEDTRAFFIC_H__631A3E8F_9935_435D_8F9A_F21B61373C82__INCLUDED_)
#define AFX_RSVIEWBUMPEDTRAFFIC_H__631A3E8F_9935_435D_8F9A_F21B61373C82__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSViewBumpedTraffic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSViewBumpedTraffic recordset

class CRSViewBumpedTraffic : public CRecordset
{
public:
	CRSViewBumpedTraffic(CString str);
	DECLARE_DYNAMIC(CRSViewBumpedTraffic)

// Field/Param Data
	//{{AFX_FIELD(CRSViewBumpedTraffic, CRecordset)
	long	m_SpotID;
	CString	m_CustomerName;
	CString	m_Name;
	long	m_Length;
	TIMESTAMP_STRUCT	m_BlockDate;
	long	m_ID;
	long	m_Time;
	//}}AFX_FIELD

	CString strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSViewBumpedTraffic)
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

#endif // !defined(AFX_RSVIEWBUMPEDTRAFFIC_H__631A3E8F_9935_435D_8F9A_F21B61373C82__INCLUDED_)
