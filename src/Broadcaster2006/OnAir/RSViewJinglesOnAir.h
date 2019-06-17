#if !defined(AFX_RSVIEWJINGLESONAIR_H__75E48F80_C8D6_4E82_872A_62133CF25638__INCLUDED_)
#define AFX_RSVIEWJINGLESONAIR_H__75E48F80_C8D6_4E82_872A_62133CF25638__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSViewJinglesOnAir.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSViewJinglesOnAir recordset

class CRSViewJinglesOnAir : public CRecordset
{
public:
	CRSViewJinglesOnAir(CString);
	DECLARE_DYNAMIC(CRSViewJinglesOnAir)

// Field/Param Data
	//{{AFX_FIELD(CRSViewJinglesOnAir, CRecordset)
	long	m_JingleID;
	CString	m_Name;
	long	m_Rythm;
	CString	m_JingleType;
	long	m_Length;
	long	m_Intro;
	COleDateTime m_StartingTime;
	COleDateTime m_EndingTime;
	//}}AFX_FIELD
	CString	m_strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSViewJinglesOnAir)
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

#endif // !defined(AFX_RSVIEWJINGLESONAIR_H__75E48F80_C8D6_4E82_872A_62133CF25638__INCLUDED_)
