#if !defined(AFX_RSRECORD_H__0F4F4F47_C418_4EB8_8C26_F1CA380C2E4A__INCLUDED_)
#define AFX_RSRECORD_H__0F4F4F47_C418_4EB8_8C26_F1CA380C2E4A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSRecord.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSRecord recordset

class CRSRecord : public CRecordset
{
public:
	CRSRecord(CString str);
	DECLARE_DYNAMIC(CRSRecord)

	CString strConnect;
// Field/Param Data
	//{{AFX_FIELD(CRSRecord, CRecordset)
	long	m_ID;
	CString	m_Title;
	long	m_ArtistID;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSRecord)
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

#endif // !defined(AFX_RSRECORD_H__0F4F4F47_C418_4EB8_8C26_F1CA380C2E4A__INCLUDED_)
