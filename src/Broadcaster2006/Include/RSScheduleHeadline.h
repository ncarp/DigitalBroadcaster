#if !defined(AFX_RSSCHEDULEHEADLINE_H__9E183554_163B_4BE3_BE1F_5088C5D8C9B8__INCLUDED_)
#define AFX_RSSCHEDULEHEADLINE_H__9E183554_163B_4BE3_BE1F_5088C5D8C9B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSScheduleHeadline.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSScheduleHeadline recordset

class CRSScheduleHeadline : public CRecordset
{
public:
	CRSScheduleHeadline(CString str,CDatabase *pdb=NULL);
	DECLARE_DYNAMIC(CRSScheduleHeadline)

// Field/Param Data
	//{{AFX_FIELD(CRSScheduleHeadline, CRecordset)
	long	m_ID;
	COleDateTime m_Date;
	COleDateTime m_EndingDate;
	long	m_Priority;
	CString	m_Name;
	long	m_TemplateID;
	//}}AFX_FIELD
	
	CString strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSScheduleHeadline)
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

#endif // !defined(AFX_RSSCHEDULEHEADLINE_H__9E183554_163B_4BE3_BE1F_5088C5D8C9B8__INCLUDED_)
