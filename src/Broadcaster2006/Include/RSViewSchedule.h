#if !defined(AFX_RSVIEWSCHEDULE_H__A61B300F_DF4B_47A7_9005_B131258C7DE2__INCLUDED_)
#define AFX_RSVIEWSCHEDULE_H__A61B300F_DF4B_47A7_9005_B131258C7DE2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSViewSchedule.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSViewSchedule recordset

class CRSViewSchedule : public CRecordset
{
public:
	CRSViewSchedule(CString str,CDatabase *pdb=NULL);
	DECLARE_DYNAMIC(CRSViewSchedule)

// Field/Param Data
	//{{AFX_FIELD(CRSViewSchedule, CRecordset)
	COleDateTime	m_Date;
	long	m_ItemOrder;
	long	m_ItemType;
	long	m_ItemID;
	long	m_ScheduleID;
	CString	m_Type;
	CString	m_Name;
	long	m_TemplateID;
	CString	m_TemplateName;
	long	m_Intro;
	long	m_Mix;
	long	m_Start;
	long	m_TypeID;
	long	m_Priority;
	long	m_Rythm;
	//}}AFX_FIELD

	CString strConnect;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSViewSchedule)
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

#endif // !defined(AFX_RSVIEWSCHEDULE_H__A61B300F_DF4B_47A7_9005_B131258C7DE2__INCLUDED_)
