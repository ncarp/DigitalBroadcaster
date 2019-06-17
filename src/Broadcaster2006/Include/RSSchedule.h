#if !defined(AFX_RSSCHEDULE_H__72EE1D43_34F0_4144_9681_237E0D95AA74__INCLUDED_)
#define AFX_RSSCHEDULE_H__72EE1D43_34F0_4144_9681_237E0D95AA74__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSSchedule.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSSchedule recordset

class CRSSchedule : public CRecordset
{
public:
	CRSSchedule(CString str="",CDatabase *pdb=NULL);
	DECLARE_DYNAMIC(CRSSchedule)

// Field/Param Data
	//{{AFX_FIELD(CRSSchedule, CRecordset)
	long	m_ID;
	TIMESTAMP_STRUCT	m_Date;
	long	m_ItemOrder;
	long	m_ItemType;
	long	m_ItemID;
	long	m_ScheduleID;
	long	m_Start;
	long	m_End;
	long	m_Priority;
	long	m_Aired;
	long	m_TemplateID;
	long	m_ItemParentID;
	long	m_Mix;
	//}}AFX_FIELD

	CString strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSSchedule)
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

#endif // !defined(AFX_RSSCHEDULE_H__72EE1D43_34F0_4144_9681_237E0D95AA74__INCLUDED_)
