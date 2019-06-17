#if !defined(AFX_RSVIEWJINGLESDATAONAIR_H__EA7264F9_C8B0_4217_BB17_5C655D501D0A__INCLUDED_)
#define AFX_RSVIEWJINGLESDATAONAIR_H__EA7264F9_C8B0_4217_BB17_5C655D501D0A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSViewJinglesDataOnAir.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSViewJinglesDataOnAir recordset

class CRSViewJinglesDataOnAir : public CRecordset
{
public:
	CRSViewJinglesDataOnAir(CString str);
	DECLARE_DYNAMIC(CRSViewJinglesDataOnAir)

// Field/Param Data
	//{{AFX_FIELD(CRSViewJinglesDataOnAir, CRecordset)
	long	m_ID;
	long	m_TypeID;
	CString	m_Name;
	long	m_Rythm;
	long	m_Start;
	long	m_Intro;
	long	m_Mix;
	long	m_Finish;
	long	m_LoopA;
	long	m_LoopB;
	CString	m_FileName;
	CString	m_TypeName;
	CString	m_Path;
	//}}AFX_FIELD

	CString m_strConnect;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSViewJinglesDataOnAir)
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

#endif // !defined(AFX_RSVIEWJINGLESDATAONAIR_H__EA7264F9_C8B0_4217_BB17_5C655D501D0A__INCLUDED_)
