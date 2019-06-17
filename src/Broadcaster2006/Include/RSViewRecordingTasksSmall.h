#if !defined(AFX_RSVIEWRECORDINGTASKSSMALL_H__67591131_75F6_4BFA_A8C1_AC1521991102__INCLUDED_)
#define AFX_RSVIEWRECORDINGTASKSSMALL_H__67591131_75F6_4BFA_A8C1_AC1521991102__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSViewRecordingTasksSmall.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSViewRecordingTasksSmall recordset

class CRSViewRecordingTasksSmall : public CRecordset
{
public:
	CRSViewRecordingTasksSmall( CString str );
	DECLARE_DYNAMIC(CRSViewRecordingTasksSmall)

// Field/Param Data
	//{{AFX_FIELD(CRSViewRecordingTasksSmall, CRecordset)
	long	m_ID;
	CString	m_Name;
	long	m_TalentID;
	long	m_Completed;
	CString	m_UserName;
	//}}AFX_FIELD

	CString strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSViewRecordingTasksSmall)
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

#endif // !defined(AFX_RSVIEWRECORDINGTASKSSMALL_H__67591131_75F6_4BFA_A8C1_AC1521991102__INCLUDED_)
