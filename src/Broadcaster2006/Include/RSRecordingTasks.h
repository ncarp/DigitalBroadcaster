#if !defined(AFX_RSRECORDINGTASKS_H__A9BC65B7_EA02_4B52_A60E_59D831C7B3D2__INCLUDED_)
#define AFX_RSRECORDINGTASKS_H__A9BC65B7_EA02_4B52_A60E_59D831C7B3D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSRecordingTasks.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSRecordingTasks recordset

class CRSRecordingTasks : public CRecordset
{
public:
	CRSRecordingTasks(CString str);
	DECLARE_DYNAMIC(CRSRecordingTasks)

// Field/Param Data
	//{{AFX_FIELD(CRSRecordingTasks, CRecordset)
	long	m_ID;
	CString	m_Name;
	long	m_TalentID;
	CTime	m_Deadline;
	CString	m_Todo;
	long	m_Completed;
	//}}AFX_FIELD

	CString m_strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSRecordingTasks)
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

#endif // !defined(AFX_RSRECORDINGTASKS_H__A9BC65B7_EA02_4B52_A60E_59D831C7B3D2__INCLUDED_)
