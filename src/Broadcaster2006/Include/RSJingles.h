#if !defined(AFX_RSJINGLES_H__B19B68AD_FA1B_4128_AA6E_1CD5B93199E0__INCLUDED_)
#define AFX_RSJINGLES_H__B19B68AD_FA1B_4128_AA6E_1CD5B93199E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSJingles.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSJingles recordset

class CRSJingles : public CRecordset
{
public:
	CRSJingles(CString str);
	DECLARE_DYNAMIC(CRSJingles)

// Field/Param Data
	//{{AFX_FIELD(CRSJingles, CRecordset)
	long	m_ID;
	long	m_TypeID;
	CString	m_Name;
	long	m_Rythm;
	long	m_LoopA;
	long	m_LoopB;
	long	m_Start;
	long	m_Intro;
	long	m_Mix;
	long	m_Finish;
	long	m_Activ;
	long	m_Ready;
	long	m_PathID;
	CString	m_FileName;
	CString	m_DRM35;
	//}}AFX_FIELD

	CString strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSJingles)
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

#endif // !defined(AFX_RSJINGLES_H__B19B68AD_FA1B_4128_AA6E_1CD5B93199E0__INCLUDED_)
