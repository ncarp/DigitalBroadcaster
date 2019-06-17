#if !defined(AFX_RSVIEWVOICEINSERTONAIR_H__648B0B76_F8A5_4F0C_A40B_5B609C6352E1__INCLUDED_)
#define AFX_RSVIEWVOICEINSERTONAIR_H__648B0B76_F8A5_4F0C_A40B_5B609C6352E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSViewVoiceInsertOnAir.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSViewVoiceInsertOnAir recordset

class CRSViewVoiceInsertOnAir : public CRecordset
{
public:
	CRSViewVoiceInsertOnAir(CString str);
	DECLARE_DYNAMIC(CRSViewVoiceInsertOnAir)

// Field/Param Data
	//{{AFX_FIELD(CRSViewVoiceInsertOnAir, CRecordset)
	long	m_ID;
	CString	m_Name;
	CString	m_FileName;
	CString	m_Path;
	long	m_Start;
	long	m_Finish;
	//}}AFX_FIELD

	CString m_strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSViewVoiceInsertOnAir)
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

#endif // !defined(AFX_RSVIEWVOICEINSERTONAIR_H__648B0B76_F8A5_4F0C_A40B_5B609C6352E1__INCLUDED_)
