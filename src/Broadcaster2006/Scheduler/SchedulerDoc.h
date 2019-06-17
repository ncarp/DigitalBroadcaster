// SchedulerDoc.h : interface of the CSchedulerDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCHEDULERDOC_H__A1CE070A_C87F_4D1D_9BA1_F6B7E352926C__INCLUDED_)
#define AFX_SCHEDULERDOC_H__A1CE070A_C87F_4D1D_9BA1_F6B7E352926C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSchedulerDoc : public CDocument
{
protected: // create from serialization only
	CSchedulerDoc();
	DECLARE_DYNCREATE(CSchedulerDoc)

// Attributes
public:
	long	m_ScheduleID;
	CString	m_strConnect,
			m_strRadio,
			m_strDB;
	COleDateTime	m_ScheduleDate,
					m_EndingDate;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSchedulerDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSchedulerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSchedulerDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCHEDULERDOC_H__A1CE070A_C87F_4D1D_9BA1_F6B7E352926C__INCLUDED_)
