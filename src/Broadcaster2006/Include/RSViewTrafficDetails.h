#if !defined(AFX_RSVIEWTRAFFICDETAILS_H__A5443B90_E290_470C_B5DA_854EB4D4C329__INCLUDED_)
#define AFX_RSVIEWTRAFFICDETAILS_H__A5443B90_E290_470C_B5DA_854EB4D4C329__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSViewTrafficDetails.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSViewTrafficDetails recordset

class CRSViewTrafficDetails : public CRecordset
{
public:
	CRSViewTrafficDetails(CString str);
	DECLARE_DYNAMIC(CRSViewTrafficDetails)

// Field/Param Data
	//{{AFX_FIELD(CRSViewTrafficDetails, CRecordset)
	long	m_ID;
	long	m_BlockID;
	CString	m_BlockName;
	long	m_BlockTime;
	COleDateTime	m_BlockDate;
	long	m_SpotID;
	CString	m_SpotName;
	long	m_TypeOfBusinessID;
	long	m_SpotLength;
	long	m_Position;
	long	m_Aired;
	CString	m_Business;
	CString	m_CustomerName;
	long	m_ScheduleID;
	//}}AFX_FIELD

	CString m_strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSViewTrafficDetails)
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

#endif // !defined(AFX_RSVIEWTRAFFICDETAILS_H__A5443B90_E290_470C_B5DA_854EB4D4C329__INCLUDED_)
