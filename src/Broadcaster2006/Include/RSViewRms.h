#if !defined(AFX_RSVIEWRMS_H__9E8DF48D_FFAC_4EAA_A689_0C71DB9F45D4__INCLUDED_)
#define AFX_RSVIEWRMS_H__9E8DF48D_FFAC_4EAA_A689_0C71DB9F45D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSViewRms.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSViewRms recordset

class CRSViewRms : public CRecordset
{
public:
	CRSViewRms(CString str);
	DECLARE_DYNAMIC(CRSViewRms)

// Field/Param Data
	//{{AFX_FIELD(CRSViewRms, CRecordset)
	long	m_ID;
	CString	m_Name;
	long	m_TypeID;
	CString	m_KeyWords;
	CString	m_Obs;
	long	m_Activ;
	COleDateTime	m_Date;
	long	m_PathID;
	CString	m_FileName;
	long	m_Start;
	long	m_Mix;
	long	m_Finish;
	CString	m_DRM35;
	long	m_ArchiveID;
	CString	m_Type;
	CString	m_Path;
	//}}AFX_FIELD

	CString strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSViewRms)
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

#endif // !defined(AFX_RSVIEWRMS_H__9E8DF48D_FFAC_4EAA_A689_0C71DB9F45D4__INCLUDED_)
