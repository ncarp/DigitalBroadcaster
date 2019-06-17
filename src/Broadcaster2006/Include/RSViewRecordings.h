#if !defined(AFX_RSVIEWRECORDINGS_H__E16FB7F3_B21C_4601_96DA_20532D145D5E__INCLUDED_)
#define AFX_RSVIEWRECORDINGS_H__E16FB7F3_B21C_4601_96DA_20532D145D5E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSViewRecordings.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSViewRecordings recordset

class CRSViewRecordings : public CRecordset
{
public:
	CRSViewRecordings(CString str);
	DECLARE_DYNAMIC(CRSViewRecordings)

// Field/Param Data
	//{{AFX_FIELD(CRSViewRecordings, CRecordset)
	long	m_ID;
	CString	m_Name;
	long	m_TalentID;
	TIMESTAMP_STRUCT	m_Deadline;
	CString	m_Todo;
	long	m_Completed;
	long	m_VersionID;
	CString	m_FileName;
	long	m_PathID;
	CString	m_Remarks;
	long	m_Deleted;
	CString	m_Path;
	CString	m_VersionName;
	//}}AFX_FIELD

	CString	m_strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSViewRecordings)
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

#endif // !defined(AFX_RSVIEWRECORDINGS_H__E16FB7F3_B21C_4601_96DA_20532D145D5E__INCLUDED_)
