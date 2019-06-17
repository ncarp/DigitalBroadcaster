#if !defined(AFX_RSVIEWNEWSONAIR_H__541D929D_D70B_4EEF_803E_4747AEDDA728__INCLUDED_)
#define AFX_RSVIEWNEWSONAIR_H__541D929D_D70B_4EEF_803E_4747AEDDA728__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSViewNewsOnAir.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSViewNewsOnAir recordset

class CRSViewNewsOnAir : public CRecordset
{
public:
	CRSViewNewsOnAir(CString str);
	DECLARE_DYNAMIC(CRSViewNewsOnAir)

// Field/Param Data
	//{{AFX_FIELD(CRSViewNewsOnAir, CRecordset)
	long	m_ID;
	long	m_NewsID;
	COleDateTime	m_StartingDate;
	COleDateTime	m_EndingDate;
	CString	m_Name;
	long	m_TypeID;
	CString	m_Type;
	//}}AFX_FIELD

	CString strConnect;
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSViewNewsOnAir)
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

#endif // !defined(AFX_RSVIEWNEWSONAIR_H__541D929D_D70B_4EEF_803E_4747AEDDA728__INCLUDED_)
