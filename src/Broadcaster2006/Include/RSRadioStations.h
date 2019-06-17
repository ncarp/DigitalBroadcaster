#if !defined(AFX_RSRADIOSTATIONS_H__593156A6_8A61_4501_9397_27AB04AF8BC1__INCLUDED_)
#define AFX_RSRADIOSTATIONS_H__593156A6_8A61_4501_9397_27AB04AF8BC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSRadioStations.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSRadioStations recordset

class CRSRadioStations : public CRecordset
{
public:
	CRSRadioStations(CString str);
	DECLARE_DYNAMIC(CRSRadioStations)

// Field/Param Data
	//{{AFX_FIELD(CRSRadioStations, CRecordset)
	long	m_ID;
	CString	m_Name;
	CString	m_Adress;
	CString	m_LogoURL;
	CString	m_DSN;
	CString	m_DB;
	//}}AFX_FIELD

	CString m_strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSRadioStations)
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

#endif // !defined(AFX_RSRADIOSTATIONS_H__593156A6_8A61_4501_9397_27AB04AF8BC1__INCLUDED_)
