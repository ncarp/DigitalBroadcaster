#if !defined(AFX_RSVIEWTRAFFICSCHEDULE_H__C41218F3_04CB_4CFB_AC57_F1A92BD53AD3__INCLUDED_)
#define AFX_RSVIEWTRAFFICSCHEDULE_H__C41218F3_04CB_4CFB_AC57_F1A92BD53AD3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSViewTrafficSchedule.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSViewTrafficSchedule recordset

class CRSViewTrafficSchedule : public CRecordset
{
public:
	CRSViewTrafficSchedule(CString str);
	DECLARE_DYNAMIC(CRSViewTrafficSchedule)

// Field/Param Data
	//{{AFX_FIELD(CRSViewTrafficSchedule, CRecordset)
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
	CString	m_RadioName;
	CString	m_DSN;
	CString	m_DB;
	CString	m_CustomerName;
	long	m_TypeOfValue;
	//}}AFX_FIELD

	CString strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSViewTrafficSchedule)
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

#endif // !defined(AFX_RSVIEWTRAFFICSCHEDULE_H__C41218F3_04CB_4CFB_AC57_F1A92BD53AD3__INCLUDED_)
