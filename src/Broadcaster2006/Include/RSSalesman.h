#if !defined(AFX_RSSALESMAN_H__7FF823E2_079D_4ABB_B1FB_215DED895BB3__INCLUDED_)
#define AFX_RSSALESMAN_H__7FF823E2_079D_4ABB_B1FB_215DED895BB3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSSalesman.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSSalesman recordset

class CRSSalesman : public CRecordset
{
public:
	CRSSalesman(CString str);
	DECLARE_DYNAMIC(CRSSalesman)

// Field/Param Data
	//{{AFX_FIELD(CRSSalesman, CRecordset)
	long	m_ID;
	CString	m_Name;
	CString	m_Adress;
	CString	m_ZIP;
	CString	m_NC;
	CString	m_Phone;
	CString	m_Fax;
	CString	m_eMail;
	double	m_Comission;
	CString	m_Remarks;
	long	m_Activ;
	CString	m_DRM35;
	//}}AFX_FIELD

	CString strConnect;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSSalesman)
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

#endif // !defined(AFX_RSSALESMAN_H__7FF823E2_079D_4ABB_B1FB_215DED895BB3__INCLUDED_)
