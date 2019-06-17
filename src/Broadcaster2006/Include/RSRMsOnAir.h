#if !defined(AFX_RSRMSONAIR_H__B7DE8AF5_DEC7_44FB_852B_CF8A01C57277__INCLUDED_)
#define AFX_RSRMSONAIR_H__B7DE8AF5_DEC7_44FB_852B_CF8A01C57277__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSRMsOnAir.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSRMsOnAir recordset

class CRSRMsOnAir : public CRecordset
{
public:
	CRSRMsOnAir(CString str);
	DECLARE_DYNAMIC(CRSRMsOnAir)

// Field/Param Data
	//{{AFX_FIELD(CRSRMsOnAir, CRecordset)
	long	m_RMID;
	COleDateTime	m_StartingDate;
	COleDateTime	m_EndingDate;
	long	m_ID;
	//}}AFX_FIELD

	CString strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSRMsOnAir)
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

#endif // !defined(AFX_RSRMSONAIR_H__B7DE8AF5_DEC7_44FB_852B_CF8A01C57277__INCLUDED_)
