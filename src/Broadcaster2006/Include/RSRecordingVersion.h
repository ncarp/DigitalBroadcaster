#if !defined(AFX_RSRECORDINGVERSION_H__54E3ECFC_0E13_4768_B3A8_90CD59F6AE78__INCLUDED_)
#define AFX_RSRECORDINGVERSION_H__54E3ECFC_0E13_4768_B3A8_90CD59F6AE78__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSRecordingVersion.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSRecordingVersion recordset

class CRSRecordingVersion : public CRecordset
{
public:
	CRSRecordingVersion(CString str);
	DECLARE_DYNAMIC(CRSRecordingVersion)

// Field/Param Data
	//{{AFX_FIELD(CRSRecordingVersion, CRecordset)
	long	m_ID;
	long	m_RecordingID;
	CString	m_Name;
	CString	m_FileName;
	long	m_PathID;
	CString	m_Remarks;
	long	m_Deleted;
	//}}AFX_FIELD

	CString strConnect;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSRecordingVersion)
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

#endif // !defined(AFX_RSRECORDINGVERSION_H__54E3ECFC_0E13_4768_B3A8_90CD59F6AE78__INCLUDED_)
