#if !defined(AFX_RSVIEWTIMESIGNAL_H__362AB009_15C2_46F6_BDAF_DE5EB6AE1687__INCLUDED_)
#define AFX_RSVIEWTIMESIGNAL_H__362AB009_15C2_46F6_BDAF_DE5EB6AE1687__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSViewTimeSignal.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSViewTimeSignal recordset

class CRSViewTimeSignal : public CRecordset
{
public:
	CRSViewTimeSignal(CString str);
	DECLARE_DYNAMIC(CRSViewTimeSignal)

// Field/Param Data
	//{{AFX_FIELD(CRSViewTimeSignal, CRecordset)
	long	m_ID;
	CString	m_Name;
	CString	m_FolderName;
	CString	m_Path;
	//}}AFX_FIELD

	CString strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSViewTimeSignal)
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

#endif // !defined(AFX_RSVIEWTIMESIGNAL_H__362AB009_15C2_46F6_BDAF_DE5EB6AE1687__INCLUDED_)
