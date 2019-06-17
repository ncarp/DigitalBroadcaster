#if !defined(AFX_RSRECORDINGTASK_H__2C17B0B0_3A88_4B13_8263_1E35CDB0A18B__INCLUDED_)
#define AFX_RSRECORDINGTASK_H__2C17B0B0_3A88_4B13_8263_1E35CDB0A18B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSRecordingTask.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSRecordingTask recordset

class CRSRecordingTask : public CRecordset
{
public:
	CRSRecordingTask(CString str);
	DECLARE_DYNAMIC(CRSRecordingTask)

// Field/Param Data
	//{{AFX_FIELD(CRSRecordingTask, CRecordset)
	long	m_ID;
	CString	m_Name;
	long	m_TalentID;
	COleDateTime m_Deadline;
	CString	m_Todo;
	long	m_Completed;
	//}}AFX_FIELD

	CString strConnect;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSRecordingTask)
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

#endif // !defined(AFX_RSRECORDINGTASK_H__2C17B0B0_3A88_4B13_8263_1E35CDB0A18B__INCLUDED_)
