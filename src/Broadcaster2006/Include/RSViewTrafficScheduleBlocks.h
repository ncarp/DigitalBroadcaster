#if !defined(AFX_RSVIEWTRAFFICSCHEDULEBLOCKS_H__A4DE1846_F1F3_4D42_8E0D_29295A4565A0__INCLUDED_)
#define AFX_RSVIEWTRAFFICSCHEDULEBLOCKS_H__A4DE1846_F1F3_4D42_8E0D_29295A4565A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSViewTrafficScheduleBlocks.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSViewTrafficScheduleBlocks recordset

class CRSViewTrafficScheduleBlocks : public CRecordset
{
public:
	CRSViewTrafficScheduleBlocks(CString str);
	DECLARE_DYNAMIC(CRSViewTrafficScheduleBlocks)

// Field/Param Data
	//{{AFX_FIELD(CRSViewTrafficScheduleBlocks, CRecordset)
	long	m_BlockID;
	long	m_Sun;
	long	m_Mon;
	long	m_Tue;
	long	m_Wed;
	long	m_Thu;
	long	m_Fri;
	long	m_Sat;
	long	m_Position;
	float	m_Value;
	long	m_ScheduleID;
	long	m_StationID;
	COleDateTime	m_StartingDate;
	COleDateTime	m_EndingDate;
	CString	m_Name;
	long	m_Time;
	//}}AFX_FIELD

	CString strConnect;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSViewTrafficScheduleBlocks)
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

#endif // !defined(AFX_RSVIEWTRAFFICSCHEDULEBLOCKS_H__A4DE1846_F1F3_4D42_8E0D_29295A4565A0__INCLUDED_)
