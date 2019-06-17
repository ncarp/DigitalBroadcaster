#if !defined(AFX_RSVIEWSPOTFILES_H__9AA76722_9FE5_4F85_98B6_270181FA9F7B__INCLUDED_)
#define AFX_RSVIEWSPOTFILES_H__9AA76722_9FE5_4F85_98B6_270181FA9F7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSViewSpotFiles.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSViewSpotFiles recordset

class CRSViewSpotFiles : public CRecordset
{
public:
	CRSViewSpotFiles(CString str);
	DECLARE_DYNAMIC(CRSViewSpotFiles)

// Field/Param Data
	//{{AFX_FIELD(CRSViewSpotFiles, CRecordset)
	long	m_ID;
	CString	m_FileName;
	//}}AFX_FIELD

	CString m_strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSViewSpotFiles)
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

#endif // !defined(AFX_RSVIEWSPOTFILES_H__9AA76722_9FE5_4F85_98B6_270181FA9F7B__INCLUDED_)
