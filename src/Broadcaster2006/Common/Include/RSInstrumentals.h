#if !defined(AFX_RSINSTRUMENTALS_H__84F300A3_20E3_48D8_9CEF_952121B9ABCE__INCLUDED_)
#define AFX_RSINSTRUMENTALS_H__84F300A3_20E3_48D8_9CEF_952121B9ABCE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSInstrumentals.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSInstrumentals recordset

class CRSInstrumentals : public CRecordset
{
public:
	CRSInstrumentals(CString str="DigitalRM-OnAir");
	DECLARE_DYNAMIC(CRSInstrumentals)

// Field/Param Data
	//{{AFX_FIELD(CRSInstrumentals, CRecordset)
	long	m_ID;
	long	m_TypeID;
	long	m_ElementID;
	COleDateTime m_LastDate;
	//}}AFX_FIELD

	CString m_strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSInstrumentals)
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

#endif // !defined(AFX_RSINSTRUMENTALS_H__84F300A3_20E3_48D8_9CEF_952121B9ABCE__INCLUDED_)
