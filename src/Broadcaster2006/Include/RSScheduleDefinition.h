#if !defined(AFX_RSSCHEDULEDEFINITION_H__BB372C64_F5F7_47A1_80DE_4639611D43FE__INCLUDED_)
#define AFX_RSSCHEDULEDEFINITION_H__BB372C64_F5F7_47A1_80DE_4639611D43FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSScheduleDefinition.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSScheduleDefinition recordset

class CRSScheduleDefinition : public CRecordset
{
public:
	CRSScheduleDefinition(CString str);
	DECLARE_DYNAMIC(CRSScheduleDefinition)

// Field/Param Data
	//{{AFX_FIELD(CRSScheduleDefinition, CRecordset)
	long	m_ID;
	COleDateTime	m_StartingDate;
	COleDateTime	m_EndingDate;
	long	m_Insertions;
	float	m_Value;
	long	m_Type;
	long	m_Suspend;
	CString	m_DRM35;
	long	m_StationID;
	long	m_CustomerID;
	long	m_TypeOfValue;
	//}}AFX_FIELD

	CString strConnect;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSScheduleDefinition)
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

#endif // !defined(AFX_RSSCHEDULEDEFINITION_H__BB372C64_F5F7_47A1_80DE_4639611D43FE__INCLUDED_)
