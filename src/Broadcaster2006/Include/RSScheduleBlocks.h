#if !defined(AFX_RSSCHEDULEBLOCKS_H__7B822A48_A9CF_422F_B827_5945D924A0F3__INCLUDED_)
#define AFX_RSSCHEDULEBLOCKS_H__7B822A48_A9CF_422F_B827_5945D924A0F3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSScheduleBlocks.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSScheduleBlocks recordset

class CRSScheduleBlocks : public CRecordset
{
public:
	CRSScheduleBlocks(CString str);
	DECLARE_DYNAMIC(CRSScheduleBlocks)

// Field/Param Data
	//{{AFX_FIELD(CRSScheduleBlocks, CRecordset)
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
	//}}AFX_FIELD

	CString strConnect;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSScheduleBlocks)
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

#endif // !defined(AFX_RSSCHEDULEBLOCKS_H__7B822A48_A9CF_422F_B827_5945D924A0F3__INCLUDED_)
