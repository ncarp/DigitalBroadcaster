#if !defined(AFX_RSVIEWNEWSLINEUPTITLES_H__898D05FD_99AD_42A0_8445_66384F245135__INCLUDED_)
#define AFX_RSVIEWNEWSLINEUPTITLES_H__898D05FD_99AD_42A0_8445_66384F245135__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSViewNewsLineUpTitles.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSViewNewsLineUpTitles recordset

class CRSViewNewsLineUpTitles : public CRecordset
{
public:
	CRSViewNewsLineUpTitles(CString str);
	DECLARE_DYNAMIC(CRSViewNewsLineUpTitles)

// Field/Param Data
	//{{AFX_FIELD(CRSViewNewsLineUpTitles, CRecordset)
	long	m_LineUpID;
	long	m_Position;
	CString	m_News;
	long	m_NewsID;
	//}}AFX_FIELD

	CString strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSViewNewsLineUpTitles)
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

#endif // !defined(AFX_RSVIEWNEWSLINEUPTITLES_H__898D05FD_99AD_42A0_8445_66384F245135__INCLUDED_)
