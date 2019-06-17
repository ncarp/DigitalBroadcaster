#if !defined(AFX_RSVIEWTRAFFICSCHEDULESPOTS_H__D8F2CC1B_9FCD_4D9E_9361_3207485EEA73__INCLUDED_)
#define AFX_RSVIEWTRAFFICSCHEDULESPOTS_H__D8F2CC1B_9FCD_4D9E_9361_3207485EEA73__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSViewTrafficScheduleSpots.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSViewTrafficScheduleSpots recordset

class CRSViewTrafficScheduleSpots : public CRecordset
{
public:
	CRSViewTrafficScheduleSpots(CString str);
	DECLARE_DYNAMIC(CRSViewTrafficScheduleSpots)

// Field/Param Data
	//{{AFX_FIELD(CRSViewTrafficScheduleSpots, CRecordset)
	long	m_ScheduleID;
	long	m_Position;
	long	m_SpotID;
	COleDateTime	m_StartingDate;
	COleDateTime	m_EndingDate;
	long	m_Sun;
	long	m_Mon;
	long	m_Tue;
	long	m_Wed;
	long	m_Thu;
	long	m_Fri;
	long	m_Sat;
	CString	m_Name;
	//}}AFX_FIELD

	CString m_strConnect;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSViewTrafficScheduleSpots)
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

#endif // !defined(AFX_RSVIEWTRAFFICSCHEDULESPOTS_H__D8F2CC1B_9FCD_4D9E_9361_3207485EEA73__INCLUDED_)
