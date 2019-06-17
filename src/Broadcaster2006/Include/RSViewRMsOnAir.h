#if !defined(AFX_RSVIEWRMSONAIR_H__C46477A7_76D6_4491_B259_F544F02E9A4B__INCLUDED_)
#define AFX_RSVIEWRMSONAIR_H__C46477A7_76D6_4491_B259_F544F02E9A4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSViewRMsOnAir.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSViewRMsOnAir recordset

class CRSViewRMsOnAir : public CRecordset
{
public:
	CRSViewRMsOnAir(CString str);
	DECLARE_DYNAMIC(CRSViewRMsOnAir)

// Field/Param Data
	//{{AFX_FIELD(CRSViewRMsOnAir, CRecordset)
	long	m_ID;
	COleDateTime	m_EndingDate;
	COleDateTime	m_StartingDate;
	long	m_RMID;
	CString	m_Name;
	CString	m_Type;
	long	m_Length;
	long	m_TypeID;
	//}}AFX_FIELD

	CString strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSViewRMsOnAir)
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

#endif // !defined(AFX_RSVIEWRMSONAIR_H__C46477A7_76D6_4491_B259_F544F02E9A4B__INCLUDED_)
