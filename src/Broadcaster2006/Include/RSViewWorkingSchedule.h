#if !defined(AFX_RSVIEWWORKINGSCHEDULE_H__DDD2068E_ADD0_451C_9D14_40317D704D4D__INCLUDED_)
#define AFX_RSVIEWWORKINGSCHEDULE_H__DDD2068E_ADD0_451C_9D14_40317D704D4D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSViewWorkingSchedule.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSViewWorkingSchedule recordset

class CRSViewWorkingSchedule : public CRecordset
{
public:
	CRSViewWorkingSchedule(CString str,CDatabase *pdb=NULL);
	DECLARE_DYNAMIC(CRSViewWorkingSchedule)

// Field/Param Data
	//{{AFX_FIELD(CRSViewWorkingSchedule, CRecordset)
	long	m_ID;
	long	m_ItemType;
	long	m_ItemID;
	long	m_ScheduleID;
	long	m_Priority;
	long	m_TemplateID;
	CString	m_strSQL;
	long	m_ItemOrder;
	long	m_ItemParentID;
	long	m_ArtistQuarantine;
	CString	m_Name;
	long	m_RandomFactor;
	long	m_SongQuarantine;
	long	m_LastPos;
	//}}AFX_FIELD

	CString strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSViewWorkingSchedule)
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

#endif // !defined(AFX_RSVIEWWORKINGSCHEDULE_H__DDD2068E_ADD0_451C_9D14_40317D704D4D__INCLUDED_)
