#if !defined(AFX_RSRMS_H__EC4B816B_54F9_4107_B5D3_997D2134FAB7__INCLUDED_)
#define AFX_RSRMS_H__EC4B816B_54F9_4107_B5D3_997D2134FAB7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSRms.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSRms recordset

class CRSRms : public CRecordset
{
public:
	CRSRms(CString str);
	DECLARE_DYNAMIC(CRSRms)

// Field/Param Data
	//{{AFX_FIELD(CRSRms, CRecordset)
	long	m_ID;
	CString	m_Name;
	long	m_TypeID;
	CString	m_KeyWords;
	CString	m_Obs;
	long	m_Activ;
	COleDateTime	m_Date;
	long	m_PathID;
	CString	m_FileName;
	long	m_Start;
	long	m_Mix;
	long	m_Finish;
	CString	m_DRM35;
	long	m_ArchiveID;
	//}}AFX_FIELD

	CString strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSRms)
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

#endif // !defined(AFX_RSRMS_H__EC4B816B_54F9_4107_B5D3_997D2134FAB7__INCLUDED_)
