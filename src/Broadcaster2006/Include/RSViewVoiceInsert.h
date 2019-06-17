#if !defined(AFX_RSVIEWVOICEINSERT_H__02C008BE_2D8E_4B02_9314_09F1A03AAE46__INCLUDED_)
#define AFX_RSVIEWVOICEINSERT_H__02C008BE_2D8E_4B02_9314_09F1A03AAE46__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSViewVoiceInsert.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSViewVoiceInsert recordset

class CRSViewVoiceInsert : public CRecordset
{
public:
	CRSViewVoiceInsert(CString str);
	DECLARE_DYNAMIC(CRSViewVoiceInsert)

// Field/Param Data
	//{{AFX_FIELD(CRSViewVoiceInsert, CRecordset)
	CString	m_User;
	long	m_ID;
	CString	m_Name;
	CString	m_FileName;
	long	m_Path;
	long	m_Start;
	long	m_Finish;
	long	m_TalentID;
	long	m_Activ;
	CString	m_PathName;
	//}}AFX_FIELD

	CString strConnect;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSViewVoiceInsert)
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

#endif // !defined(AFX_RSVIEWVOICEINSERT_H__02C008BE_2D8E_4B02_9314_09F1A03AAE46__INCLUDED_)
