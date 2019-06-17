#if !defined(AFX_RSONAIRLOG_H__95970F18_3411_4B91_96DA_DF29C361F9C5__INCLUDED_)
#define AFX_RSONAIRLOG_H__95970F18_3411_4B91_96DA_DF29C361F9C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSOnAirLog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSOnAirLog recordset

class CRSOnAirLog : public CRecordset
{
public:
	CRSOnAirLog(CString str);
	DECLARE_DYNAMIC(CRSOnAirLog)

// Field/Param Data
	//{{AFX_FIELD(CRSOnAirLog, CRecordset)
	COleDateTime	m_Date;
	long	m_ComputerID;
	long	m_UserID;
	long	m_ItemType;
	long	m_ItemID;
	//}}AFX_FIELD

	CString strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSOnAirLog)
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

#endif // !defined(AFX_RSONAIRLOG_H__95970F18_3411_4B91_96DA_DF29C361F9C5__INCLUDED_)
