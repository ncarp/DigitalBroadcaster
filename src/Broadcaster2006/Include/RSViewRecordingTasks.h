#if !defined(AFX_RSVIEWRECORDINGTASKS_H__A09A084A_49A0_40F7_B8CD_BE4CC212AEA5__INCLUDED_)
#define AFX_RSVIEWRECORDINGTASKS_H__A09A084A_49A0_40F7_B8CD_BE4CC212AEA5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSViewRecordingTasks.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSViewRecordingTasks recordset

class CRSViewRecordingTasks : public CRecordset
{
public:
	CRSViewRecordingTasks(CString str);
	DECLARE_DYNAMIC(CRSViewRecordingTasks)

// Field/Param Data
	//{{AFX_FIELD(CRSViewRecordingTasks, CRecordset)
	long	m_ID;
	CString	m_Name;
	long	m_TalentID;
	COleDateTime	m_Deadline;
	CString	m_Todo;
	long	m_Completed;
	CString	m_UserName;
	//}}AFX_FIELD

	CString strConnect;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSViewRecordingTasks)
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

#endif // !defined(AFX_RSVIEWRECORDINGTASKS_H__A09A084A_49A0_40F7_B8CD_BE4CC212AEA5__INCLUDED_)
