#if !defined(AFX_RSVIEWSPOTPERIODONTRAFFIC_H__01BAC96A_184A_4A1C_99D2_538D1F45CDED__INCLUDED_)
#define AFX_RSVIEWSPOTPERIODONTRAFFIC_H__01BAC96A_184A_4A1C_99D2_538D1F45CDED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSViewSpotPeriodOnTraffic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSViewSpotPeriodOnTraffic recordset

class CRSViewSpotPeriodOnTraffic : public CRecordset
{
public:
	CRSViewSpotPeriodOnTraffic(CString str);
	DECLARE_DYNAMIC(CRSViewSpotPeriodOnTraffic)

// Field/Param Data
	//{{AFX_FIELD(CRSViewSpotPeriodOnTraffic, CRecordset)
	long	m_SpotID;
	COleDateTime	m_MaxDate;
	COleDateTime	m_MinDate;
	CString	m_SpotName;
	//}}AFX_FIELD
	CString m_strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSViewSpotPeriodOnTraffic)
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

#endif // !defined(AFX_RSVIEWSPOTPERIODONTRAFFIC_H__01BAC96A_184A_4A1C_99D2_538D1F45CDED__INCLUDED_)
