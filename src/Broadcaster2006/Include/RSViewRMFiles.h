#if !defined(AFX_RSVIEWRMFILES_H__9695DD2D_5666_42EF_B7C3_506D3D381CEC__INCLUDED_)
#define AFX_RSVIEWRMFILES_H__9695DD2D_5666_42EF_B7C3_506D3D381CEC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSViewRMFiles.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSViewRMFiles recordset

class CRSViewRMFiles : public CRecordset
{
public:
	CRSViewRMFiles(CString str);
	DECLARE_DYNAMIC(CRSViewRMFiles)

// Field/Param Data
	//{{AFX_FIELD(CRSViewRMFiles, CRecordset)
	long	m_ID;
	CString	m_FileName;
	//}}AFX_FIELD

	CString strConnect;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSViewRMFiles)
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

#endif // !defined(AFX_RSVIEWRMFILES_H__9695DD2D_5666_42EF_B7C3_506D3D381CEC__INCLUDED_)
