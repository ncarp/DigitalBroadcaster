#if !defined(AFX_RSTRAFFICSCHEDULEDEFINITION_H__03BD41A8_D785_40D8_BA6E_C32F599769B9__INCLUDED_)
#define AFX_RSTRAFFICSCHEDULEDEFINITION_H__03BD41A8_D785_40D8_BA6E_C32F599769B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSTrafficScheduleDefinition.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSTrafficScheduleDefinition recordset

class CRSTrafficScheduleDefinition : public CRecordset
{
public:
	CRSTrafficScheduleDefinition(CString str);
	DECLARE_DYNAMIC(CRSTrafficScheduleDefinition)

// Field/Param Data
	//{{AFX_FIELD(CRSTrafficScheduleDefinition, CRecordset)
	long	m_ID;
	TIMESTAMP_STRUCT	m_StartingDate;
	TIMESTAMP_STRUCT	m_EndingDate;
	long	m_Insertions;
	CString	m_Value;
	long	m_Type;
	long	m_Suspend;
	CString	m_DRM35;
	long	m_StationID;
	long	m_CustomerID;
	long	m_TypeOfValue;
	//}}AFX_FIELD

	CString m_strConnect;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSTrafficScheduleDefinition)
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

#endif // !defined(AFX_RSTRAFFICSCHEDULEDEFINITION_H__03BD41A8_D785_40D8_BA6E_C32F599769B9__INCLUDED_)
