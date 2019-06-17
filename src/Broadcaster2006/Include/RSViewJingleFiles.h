#if !defined(AFX_RSVIEWJINGLEFILES_H__21261C7D_614C_4C8C_8776_8801F3C244F8__INCLUDED_)
#define AFX_RSVIEWJINGLEFILES_H__21261C7D_614C_4C8C_8776_8801F3C244F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSViewJingleFiles.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSViewJingleFiles recordset

class CRSViewJingleFiles : public CRecordset
{
public:
	CRSViewJingleFiles(CString str);
	DECLARE_DYNAMIC(CRSViewJingleFiles)

// Field/Param Data
	//{{AFX_FIELD(CRSViewJingleFiles, CRecordset)
	long	m_ID;
	CString	m_FileName;
	//}}AFX_FIELD

	CString strConnect;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSViewJingleFiles)
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

#endif // !defined(AFX_RSVIEWJINGLEFILES_H__21261C7D_614C_4C8C_8776_8801F3C244F8__INCLUDED_)
