#if !defined(AFX_RSSCHEDULESPOTS_H__DB688180_3236_4D3D_9639_0F0EB60FA332__INCLUDED_)
#define AFX_RSSCHEDULESPOTS_H__DB688180_3236_4D3D_9639_0F0EB60FA332__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSScheduleSpots.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSScheduleSpots recordset

class CRSScheduleSpots : public CRecordset
{
public:
	CRSScheduleSpots(CString str);
	DECLARE_DYNAMIC(CRSScheduleSpots)

// Field/Param Data
	//{{AFX_FIELD(CRSScheduleSpots, CRecordset)
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
	//}}AFX_FIELD
	
	CString strConnect;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSScheduleSpots)
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

#endif // !defined(AFX_RSSCHEDULESPOTS_H__DB688180_3236_4D3D_9639_0F0EB60FA332__INCLUDED_)
