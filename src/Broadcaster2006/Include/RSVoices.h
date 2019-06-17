#if !defined(AFX_RSVOICES_H__D400F07C_1758_4E3A_A47C_1CCADA5906DB__INCLUDED_)
#define AFX_RSVOICES_H__D400F07C_1758_4E3A_A47C_1CCADA5906DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSVoices.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSVoices recordset

class CRSVoices : public CRecordset
{
public:
	CRSVoices(CString str);
	DECLARE_DYNAMIC(CRSVoices)

// Field/Param Data
	//{{AFX_FIELD(CRSVoices, CRecordset)
	long	m_ID;
	CString	m_Name;
	long	m_Activ;
	//}}AFX_FIELD

	CString strConnect;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSVoices)
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

#endif // !defined(AFX_RSVOICES_H__D400F07C_1758_4E3A_A47C_1CCADA5906DB__INCLUDED_)
