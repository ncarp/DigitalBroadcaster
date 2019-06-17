#if !defined(AFX_RSVIEWINSTRUMENTALS_H__CF384828_CE3F_4EF9_A5CE_BAF97A92BA66__INCLUDED_)
#define AFX_RSVIEWINSTRUMENTALS_H__CF384828_CE3F_4EF9_A5CE_BAF97A92BA66__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// rsviewinstrumentals.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSViewInstrumentals recordset

class CRSViewInstrumentals : public CRecordset
{
public:
	CRSViewInstrumentals(CString str="DigitalRM-OnAir");
	DECLARE_DYNAMIC(CRSViewInstrumentals)

// Field/Param Data
	//{{AFX_FIELD(CRSViewInstrumentals, CRecordset)
	long	m_ID;
	long	m_TypeID;
	long	m_ElementID;
	COleDateTime	m_LastDate;
	CString	m_Title;
	CString	m_Artist;
	long	m_Length;
	//}}AFX_FIELD
	
	CString m_strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSViewInstrumentals)
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

#endif // !defined(AFX_RSVIEWINSTRUMENTALS_H__CF384828_CE3F_4EF9_A5CE_BAF97A92BA66__INCLUDED_)
