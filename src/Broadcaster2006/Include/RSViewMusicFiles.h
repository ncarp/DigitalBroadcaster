#if !defined(AFX_RSVIEWMUSICFILES_H__20782D1E_9021_43CA_90AD_B343F86158F2__INCLUDED_)
#define AFX_RSVIEWMUSICFILES_H__20782D1E_9021_43CA_90AD_B343F86158F2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSViewMusicFiles.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSViewMusicFiles recordset

class CRSViewMusicFiles : public CRecordset
{
public:
	CRSViewMusicFiles(CString str);
	DECLARE_DYNAMIC(CRSViewMusicFiles)

// Field/Param Data
	//{{AFX_FIELD(CRSViewMusicFiles, CRecordset)
	CString	m_FileName;
	long	m_Activ;
	//}}AFX_FIELD

	CString m_strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSViewMusicFiles)
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

#endif // !defined(AFX_RSVIEWMUSICFILES_H__20782D1E_9021_43CA_90AD_B343F86158F2__INCLUDED_)
