#if !defined(AFX_RSVIEWSCHEDULEJINGLETEMPLATE_H__B8846570_2C00_40A2_8022_6802AFB3BEC4__INCLUDED_)
#define AFX_RSVIEWSCHEDULEJINGLETEMPLATE_H__B8846570_2C00_40A2_8022_6802AFB3BEC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSViewScheduleJingleTemplate.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSViewScheduleJingleTemplate recordset

class CRSViewScheduleJingleTemplate : public CRecordset
{
public:
	CRSViewScheduleJingleTemplate(CString str);
	DECLARE_DYNAMIC(CRSViewScheduleJingleTemplate)

// Field/Param Data
	//{{AFX_FIELD(CRSViewScheduleJingleTemplate, CRecordset)
	long	m_ID;
	CString	m_Name;
	long	m_TypeID;
	long	m_MinRythm;
	long	m_MaxRythm;
	long	m_MinLen;
	long	m_MaxLen;
	CString	m_TypeName;
	//}}AFX_FIELD

	CString strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSViewScheduleJingleTemplate)
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

#endif // !defined(AFX_RSVIEWSCHEDULEJINGLETEMPLATE_H__B8846570_2C00_40A2_8022_6802AFB3BEC4__INCLUDED_)
